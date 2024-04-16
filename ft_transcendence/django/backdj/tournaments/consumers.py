import json, time
import asyncio
from random import uniform, shuffle, choice
from math import cos, sin, radians

from channels.generic.websocket import AsyncWebsocketConsumer
from rest_framework.authtoken.models import Token
from asgiref.sync import sync_to_async

from django.conf import settings

from users.models import *
from utilities.utils import * 
from tournaments.models import *
from blockchain.blockchain import tournament_transaction
from utilities.logger import printe, printd, printi, printw


START_TOURNAMENT_TX = settings.BLOCKCHAIN_ID
ASYNC_SLEEP_TIME = 0.03
BALL_MAX_SPEED = 90
PADDLE_SPEED = 52
PADDLE_H = 24
PADDLE_W = 2
PADDLE_O = 3


class TournamentStructure():

	def __init__(self, players:list=[]) -> None:
		self.match_index:int = -1
		self.turn:str = "quarters"
		self.players_number = len(players)
		self.structure = self.generate_structure(players)
		self.placements = [None for x in range(8)]
		self.winners = {
			"finals": [None, None],
			"semifinals": [None, None],
			"quarters": [None, None, None, None],
		}
		self.next_match:list = [-1, -1] # self.calculate_match()
	
	def generate_structure(self, players:list=[]) -> dict:
		temp_dict = {
			"finals": [[None, None], [None, None]],
			"semifinals": [[None, None], [None, None]],
			"quarters": [[None, None], [None, None], [None, None], [None, None]]
		}

		if self.players_number < 3:
			self.turn = "finals"
			temp_dict["finals"] = [[players[0], players[1]]]
			return temp_dict
		
		pl = players.copy()
		shuffle(pl)
		
		if self.players_number < 5:
			self.turn = "semifinals"
			temp_dict["semifinals"] = [[pl[0], pl[1]], [pl[2], None]]
			if self.players_number == 4:
				temp_dict["semifinals"][1][1] = pl[3]
			return temp_dict
		
		# if players > 4
		self.turn = "quarters"
		y = 0
		while len(pl) > 0 and y < 4:
			temp_dict["quarters"][y][0] = pl.pop(0)
			y += 1
		y = 0
		while len(pl) > 0 and y < 4:
			temp_dict["quarters"][y][1] = pl.pop(0)
			y += 1

		return temp_dict
	
	def calculate_next_match(self) -> list:
		self.next_match = self.calculate_match()
		return self.next_match
	
	def calculate_match(self) -> list:
		# set tournament to finished status
		if self.turn == "finals" and self.winners["finals"][1] != None:
			self.turn == "finished"
			return [None, None]

		# Quarters
		if self.turn == "quarters":
			idx = 0
			while idx < 4 and self.winners["quarters"][idx] != None:
				idx += 1

			if idx == 4:
				self.turn = "semifinals"
			else:
				self.match_index = idx
				return self.structure["quarters"][idx].copy()

		# Semi Finals
		if self.turn == "semifinals":
			idx = 0
			while idx < 2 and self.winners["semifinals"][idx] != None :
				idx += 1
			if idx == 2:
				self.turn = "finals"
			else:
				self.match_index = idx
				return self.structure["semifinals"][idx].copy()

		# Finals
		if self.players_number == 2:
			if self.winners["finals"][0] == None:
				return self.structure["finals"][0].copy()
			self.turn = "end"
			return None

		idx = 0
		while self.winners["finals"][idx] != None and idx < 2:
			idx += 1
		if idx != 2:
			self.match_index = idx
			return self.structure["finals"][idx].copy()
		
		self.turn = "end"
		return None
	
	def save_game_db(self, match, pwinner, plooser, turn) -> None:
		if plooser == None: return
		game = GamesHistory.create(match, pwinner.player_id, plooser.player_id, turn)
		game.save()
		printi(f"Saving Game stats -> {turn} {pwinner.player_id} ~ {plooser.player_id}")
		pwinner.match_won()
		plooser.match_lost()
	
	def save_placements(self, players:dict) -> None:
		pos:int = 0
		for p_id in self.placements:
			if p_id == None: break
			players[p_id].save_placement(pos)
			pos += 1
	
	def set_placement(self, idx:int, player:Player) -> None:
		if player == None: return
		self.placements[idx] = player.player_id
		# player.save_placement(idx)
	
	def game_won_by(self, pwinner:Player, plooser:Player, match) -> None:
		idx:int = self.match_index
		player_won:int = pwinner.player_id
		player_lost:int = None
		if plooser != None:
			player_lost = plooser.player_id
		self.winners[self.turn][idx] = player_won

		if self.turn == "quarters":
			self.save_game_db(match, pwinner, plooser, self.turn)
			if plooser != None:
				self.set_placement(4 + idx, plooser)
			self.structure["semifinals"][int(idx / 2)][idx % 2] = player_won

		if self.turn == "semifinals":
			self.save_game_db(match, pwinner, plooser, "semi final")
			if idx == 0:
				self.structure["finals"][1][idx % 2] = player_won
				self.structure["finals"][0][idx % 2] = player_lost
			elif idx == 1:
				self.structure["finals"][1][idx % 2] = player_won
				self.structure["finals"][0][idx % 2] = player_lost

		if self.turn == "finals":
			if self.players_number == 2 or idx == 1:
				if self.players_number == 2:
					self.save_game_db(match, pwinner, plooser, "")
				else:
					self.save_game_db(match, pwinner, plooser, "final")

				self.set_placement(0, pwinner)
				self.set_placement(1, plooser)
			else: #idx == 0 (3rd or 4th place)
				self.save_game_db(match, pwinner, plooser, "3rd/4th place")
				self.set_placement(2, pwinner)
				self.set_placement(3, plooser)
	
	def dict(self) -> dict:
		return {
			"structure": self.structure,
			"winners": self.winners,
			"turn": self.turn,
			"next_match": self.next_match,
			"placements": self.placements,
		}


class MMatch():

	def __init__(self, score_to_win:int=0, *args, **kwargs) -> None:
		self.score_to_win:int = score_to_win
		self.game_speed:float = 11
		self.max_ball_speed:float = BALL_MAX_SPEED
		self.paddle_speed:float = PADDLE_SPEED
		self.score:list = [0, 0]
		self.ball_speed:float = 10.0
		self.paddles_y:list = [50, 50]
		self.ball_pos:list = [50, 50]
		self.ball_dir:float = self.init_angle()
		self.timestamp:float = 0
		self.key_up_pressed:list = [False, False]
		self.key_down_pressed:list = [False, False]

	def init_angle(self) -> float:
		self.ball_dir = uniform(-50, 50) + choice([180, 0])
		# self.ball_dir = uniform(305, 360)
		self.reset_ball_direction()
		return self.ball_dir

	def reinit(self) -> None:
		self.ball_pos 	= [50, 50]
		self.init_angle()
		self.ball_speed = 11
		self.timestamp 	= 0
		# TODO: Set pause, wait a second for the new game

	def raise_ball_speed(self, dt:float) -> None:
		if self.ball_speed < self.max_ball_speed:
			self.ball_speed += self.game_speed * dt
		if self.ball_speed > self.max_ball_speed:
			self.ball_speed = self.max_ball_speed

	def move_ball_and_collide(self) -> list:
		dt:float = time.time() - self.timestamp
		if self.timestamp == 0: dt = 0
		self.timestamp = time.time()

		self.move_paddles(dt)
		self.raise_ball_speed(dt)

		self.horizontal_axe_collisions()
		self.vertical_axe_collisions()
		self.paddles_collisions()

		dx = (self.ball_speed * cos(radians(self.ball_dir))) * dt
		dy = (self.ball_speed * sin(radians(self.ball_dir))) * dt
		self.ball_pos[0] += dx
		self.ball_pos[1] += dy

		return self.ball_pos

	def move_paddles(self, dt:float) -> None:
		for i in range(2):
			if self.key_up_pressed[i]:
				self.paddles_y[i] -= self.paddle_speed * dt
			elif self.key_down_pressed[i]:
				self.paddles_y[i] += self.paddle_speed * dt
			if self.paddles_y[i] < PADDLE_H / 2:
				self.paddles_y[i] = PADDLE_H / 2
			elif self.paddles_y[i] > 100 - (PADDLE_H / 2):
				self.paddles_y[i] = 100 - (PADDLE_H / 2)

	async def key_pressed(self, pid:int, key:str, pressed:bool) -> None:
		# printd(f"Player <{pid}> pressed {key} -> {pressed}")
		if key == "ArrowDown":
			self.key_down_pressed[pid] = pressed
			if self.key_up_pressed[pid]:
				self.key_up_pressed[pid] = not pressed
		elif key == "ArrowUp":
			self.key_up_pressed[pid] = pressed
			if self.key_down_pressed[pid]:
				self.key_down_pressed[pid] = not pressed

	def reset_ball_direction(self) -> None:
		self.ball_dir %= 360

	def horizontal_axe_collisions(self) -> None:
		y = self.ball_pos[1]
		if y > 98 and ( 0 < self.ball_dir < 180):
			self.ball_dir = (180 - self.ball_dir) + 180
		if y < 2 and ( 180 < self.ball_dir < 360):
			self.ball_dir = (180 - self.ball_dir) - 180
		self.reset_ball_direction()

	def vertical_axe_collisions(self) -> None:
		x = self.ball_pos[0]
		if x < 1:
			self.raise_score(1)
		elif x > 99:
			self.raise_score(0)
		if x < 1 or x > 99:
			self.reinit()

	def raise_score(self, idx:int) -> None:
		self.score[idx] += 1

	def paddles_collisions(self) -> None:
		bx = self.ball_pos[0]
		by = self.ball_pos[1]
		if PADDLE_O - 1 <= bx <= PADDLE_O + PADDLE_W + 1:
			if self.paddles_y[0] - PADDLE_H / 2 < by < self.paddles_y[0] + PADDLE_H / 2:
				if 90 <= self.ball_dir < 270:
					self.ball_dir = (90 - self.ball_dir) + 90
					dx = self.paddles_y[0] - by
					self.ball_dir -= dx * 2.5
		elif (100 - PADDLE_O - PADDLE_W - 1) <= bx <= (100 - PADDLE_O + 1):
			if self.paddles_y[1] - PADDLE_H / 2 < by < self.paddles_y[1] + PADDLE_H / 2:
				if 0 <= self.ball_dir <= 90 or 270 < self.ball_dir <= 360:
					self.ball_dir = (90 - self.ball_dir) + 90
					dx = self.paddles_y[1] - by
					self.ball_dir += dx * 2.5
		self.reset_ball_direction()

	async def game_end(self) -> int:
		for i in range(2):
			if self.score[i] >= self.score_to_win:
				return i
		return -1

	def start(self) -> None:
		#TODO: Timer to begin (send that to all users too)
		pass

	def set_winner(self, idx:int) -> None:
		self.score[idx] = self.score_to_win

	def dict(self) -> dict:
		return {
			"score": self.score,
			"paddles_y": self.paddles_y,
			"ball_pos": self.ball_pos,
			"ball_speed": self.ball_speed,
			"ball_dir": self.ball_dir
		}


class Game():

	def __init__(self, tournament:Tournament, *args, **kwargs) -> None:
		self.tournament = tournament
		self.game_id:int = tournament.id
		self.max_players:int = tournament.max_partecipants
		self.score_to_win:int = tournament.score_to_win
		self.players:dict = {}
		self.players_obj:dict = {}
		self.tournament_structure:TournamentStructure = None
		self.match:MMatch = None
		self.players_in_game:list = [-1, -1]
		self.status = "queue" # "started" | "match" | "match_end" | "end"
		self.game_turn:int = 0 # 0: Final, 1: Semi-Final, 2: Quarters
		self.group_name:str = ""
		self.tx_hash = None
		self.blockchain_tournament = None
		self.observers:dict = {}

	def get_player(self, player:Player) -> dict:
		return self.players[player.player_id]

	async def add_player(self, player:Player) -> None:
		if len(self.players) < self.max_players:
			self.players[player.player_id] = player.to_game_dict()
			self.players_obj[player.player_id] = player
			# printd(f"Added players: {self.players}")
		else:
			printw("Max players reached in tournament, time to play..")

	async def reached_max_size(self) -> bool:
		if len(self.players.keys()) >= self.max_players:
			return True
		return False

	async def add_observer(self, player:Player) -> None:
		self.observers[player.player_id] = player.to_game_dict()
		printi("New observer logged")

	async def remove_observer(self, player:Player) -> None:
		#del self.observers[player.player_id]
		pass

	async def player_ready(self, player:Player, ready:bool=True) -> None:
		self.get_player(player)["ready"] = ready

		count = 0
		for pl in self.players.values():
			printd(f"player_ready: {pl['id']}")
			if pl["ready"]: count += 1

		if self.status == "queue":
			if self.max_players == count:
				self.status = "started"
		else: # self.status == "started":
			if count > 1:
				self.status = "match"
			# self.tournament_begin()

	async def user_disconnected(self, player:Player) -> None:
		self.get_player(player)["disconnected"] = True
		if player.player_id in self.players_in_game:
			i = 0
			if self.players_in_game[i] == player.player_id:
				i = 1
			self.match.set_winner(i)

	async def remove_player(self, player:Player) -> None:
		try:
			if not player.player_id in self.players:
				return
			del self.players[player.player_id]
			del self.players_obj[player.player_id]
		except Exception as e:
			printe(f"Removing player exception: {e}")
		await sync_to_async(self.tournament.remove_player)(player.player_id)

	async def reconnect_player(self, player:Player) -> None:
		if not player.player_id in self.players: return
		self.get_player(player)["disconnected"] = False

	def user_relogged(self, player:Player) -> None:
		self.get_player(player)["disconnected"] = False	

	async def next_match_data(self) -> None:
		self.players_in_game[1] = None	
		while self.players_in_game[1] == None:
			self.players_in_game = await sync_to_async(self.tournament_structure.calculate_next_match)()	
			if self.players_in_game[0] == None:
				printi("Setting tournament status to finished")
				self.status = "finished"
				break
			if self.players_in_game[1] == None:
				await sync_to_async(self.match_end)(0)
				continue 

			if await self.not_active_user():
				printi("A player will auto won a game due to a disconnected player")
				self.players_in_game[1] = None

		await self.save_tournament_data(tournament=False)
		if not self.tournament_structure.turn == "finished":
			self.match = MMatch(self.score_to_win)

	async def not_active_user(self) -> bool:
		p1 = self.players_obj[self.players_in_game[0]]
		
		p2 = self.players_in_game[1]
		if p2 != None:
			p2 = self.players_obj[p2]

		if self.players[p1.player_id].get("disconnected", False) and p2 == None:
			await sync_to_async(self.tournament_structure.game_won_by)(p2, p1, self.match)
			return True
		elif self.players[p1.player_id].get("disconnected", False):
			await sync_to_async(self.tournament_structure.game_won_by)(p1, p2, self.match)
			return True
		elif p2 != None and self.players[p2.player_id].get("disconnected", False):
			await sync_to_async(self.tournament_structure.game_won_by)(p1, p2, self.match)
			return True

		return False
		# for i in range(len(self.players_in_game)):
		# 	if self.players[self.players_in_game[i]]["disconnected"] == False: 
		# 		continue
		# 	await sync_to_async(self.tournament_structure.game_won_by)(self.players_in_game[(i + 1) % 2])
		# 	return True

	async def tournament_begin(self) -> bool:
		if self.status == "queue": return False
		printi("Randomizing tournaments matches")
		self.tournament_structure = TournamentStructure(list(self.players.keys()))
		await self.next_match_data()

		self.tournament.status = "started"
		await sync_to_async(self.tournament.save)()
		return True

	async def match_begin(self, data:dict={}) -> bool:
		if not self.status == "match": 
			return False
		# self.match.start()
		return True

	async def revert_ready(self) -> None:
		for player in self.players.values():
			player["ready"] = False

	async def save_player_stats(self) -> None:
		await sync_to_async(self.tournament_structure.save_placements)(self.players_obj)

	async def save_tournament_data(self, tournament=True) -> None:
		await sync_to_async(self.tournament.set_finished)(self.tournament_structure)
		if tournament: 
			await sync_to_async(self.tournament_structure.save_placements)(self.players_obj)

	async def players_in_game_off(self) -> None:
		for player in self.players_obj.values():
			await sync_to_async(player.leave_game)()

	def match_end(self, won_idx:int) -> None:
		self.status = "match_end"
		lost_idx = (won_idx + 1) % 2
		pwinner = self.players_obj[self.players_in_game[won_idx]]
		plooser = self.players_in_game[lost_idx]
		if plooser != None:
			plooser = self.players_obj[plooser]
		self.tournament_structure.game_won_by(
				pwinner,
				plooser,
				self.match
			)

	async def save_into_blockchain(self) -> None:
		printi("Saving tournament data into blockchain")
		ts = self.tournament_structure.dict()
		self.tournament.structure = json.dumps(ts)
		self.tx_hash = await sync_to_async(tournament_transaction)({
					"winners": self.transform_for_block(ts["winners"]),
					"structure": self.transform_for_block(ts["structure"]),
					"timestamp": 1,
					"id": self.game_id + START_TOURNAMENT_TX,
				})
		self.tx_hash = self.tx_hash.hex()
		self.tournament.tx_hash = self.tx_hash

	def transform_for_block(self, dt:dict) -> dict:
		ls:list = []
		for val in dt.values():
			ls.append(json.dumps(val))
		return ls


class TournamentConsumer(AsyncWebsocketConsumer):
	tournaments:dict = {}
	games:dict = {}
	update_lock = [asyncio.Lock()]
	loop:bool = False
	tasks:list = [None]

	def __init__(self, *args, **kwargs) -> None:
		super().__init__(*args, **kwargs)
		self.user:Player = None
		self.id:int = None
		self.name:str = None
		#self.players:dict = {}
		self.group_name:str = "tournament_"
		self.observer:bool = False

	async def set_usr_by_tkn(self, token:str) -> bool:
		tok = None
		try:
			tok = await sync_to_async(Token.objects.get)(key=token)
			self.user = await sync_to_async(Player.objects.get)(player_id=tok.user_id)
			# printi(f"retrieved user id -> {self.user}")
			return True
		except Token.DoesNotExist:
			printe("Token does not exist...")
		except Exception as e:
			printe(f"Another error while checking token -> {e}")
		return False

	async def init_data(self) -> None:
		try:
			tournament_object = await sync_to_async(Tournament.objects.get)(id=self.id)
			self.tournaments[self.id] = tournament_object
			self.games[self.id] = Game(tournament_object)
		except Exception as e:
			printe(f"Error while picking Tournament: {e}")
			self.games[self.id] = None

	# ---------------------------------------------------------------------------- #
	# --- Default Methods

	async def get_querydict(self, query) -> dict:
		if not query: return None
		voices = query.split("&")
		queryset:dict = {
			key: value for x in voices for key, value in [x.split("=", 1)]
		}
		return queryset

	async def connect(self) -> None:
		queryset = await self.get_querydict(self.scope['query_string'].decode('utf-8'))
		if not queryset or not await self.set_usr_by_tkn(queryset.get("tok", "")):
			printe("Missing token at connection or invalid token")
			return

		self.id = self.scope['url_route']['kwargs'].get("tournament_id", "None")
		
		if not self.id in self.games:
			await self.init_data()
			self.loop = True

		if self.tasks[0] == None or (self.tasks[0] != None and self.tasks[0].done()):
			self.tasks[0] = asyncio.create_task(self.game_loop())
			printi("Initialized games loop")
		
		printi(f"New user is connecting to match/tournament {self.id} | {self.user.username} #{self.user.player_id}")
		self.group_name += str(self.id)
		self.games[self.id].group_name = self.group_name

		# password check
		await self.accept()

		if not await self.check_tournament_password(queryset):
			await self.send(json.dumps({"action": "wrong_password"}))
			self.observer = True
			await self.close()
			return

		await self.add_user(queryset)

	async def disconnect(self, conn) -> None:
		if self.id in self.games:
			
			if self.observer:
				await self.send_json({
					"action": "observer_left",
					"id": self.user.id
				}, self.games[self.id].group_name)
				if self.id in self.games:
					await self.games[self.id].remove_observer(self.user)
				await self.close()
				return

			if self.games[self.id].status == "queue":
				await self.send_json({
						"action": "queue_user_disconnection",
						"id": self.user.player_id,
					}, self.games[self.id].group_name)
				if self.id in self.games:
					await self.games[self.id].remove_player(self.user)
				await self.not_active_players(self.games[self.id])
			else:
				if self.id in self.games:
					await self.games[self.id].user_disconnected(self.user)
				await self.send_json({
						"action": "user_disconnection",
						"id": self.user.player_id,
						"username": self.user.username
					}, self.games[self.id].group_name)

	async def add_user(self, queryset:dict) -> None:
		# check if its an observer
		# printe(f"query: {queryset}")
		if queryset.get("observer", False):
			await self.add_observer()
			return

		# check maximum users
		if await self.games[self.id].reached_max_size():
			# check if user is in game_list
			if not await self.user_reconnection(self.games[self.id], self.user):
				await self.send(json.dumps({"action": "to_lobby"}))
				await self.close()
				return

		await self.channel_layer.group_add(
				self.group_name,
				self.channel_name,
			)
		await self.send_json({
				"action": "new_connection",
				"id": self.user.player_id,
				"username": self.user.username,
				"avatar": self.user.avatar,
			}, self.games[self.id].group_name)

		await self.send(json.dumps({
				"action": "users_connected",
				"players_list": self.games[self.id].players,
			}))

		async with self.update_lock[0]: #TOCHECK
			# fill player list in the tournament
			await sync_to_async(self.tournaments[self.id].add_player)(self.user.player_id)

			# player in tournament
			if not self.user.in_game or self.user.tournament_id != self.id:
				self.user.in_game = True
				self.user.tournament_id = self.id
				await sync_to_async(self.user.save)()

			# add player to the game
			await self.games[self.id].add_player(self.user)

	async def user_reconnection(self, game:Game, player:Player) -> bool:
		if not player.player_id in game.players.keys(): 
			return False


		#TODO: reconnection flags
		await game.reconnect_player(player)
		await self.send_json({
				"action": "reconnection",
				"id": self.user.player_id,
				"username": self.user.username,
				"avatar": self.user.avatar,
			}, game.group_name)

		await self.send(json.dumps({
				"action": "users_connected",
				"players_list": self.games[self.id].players,
			}))

		# redirect user to correct page
		data:dict = {}
		if game.status == "started":
			data = {
					"action": "to_tournament",
					"tournament": game.tournament_structure.dict(),
				}
		elif game.status == "match":
			data = {
					"action": "to_game",
					"player_1": game.players_in_game[0],
					"player_2": game.players_in_game[1],
					"tournament": game.tournament_structure.dict(),
				}
		self.send(json.dumps(data))

		return True

	async def send_json(self, json:dict, group_name:str=None) -> None:
		if json['action'] != "game_refresh":
			printd(f"Sending action: {json['action']}")
		await self.channel_layer.group_send(
				self.group_name if group_name == None else group_name,
				{
					"type": "new_event",
					"json": json
			})

	async def new_event(self, event:dict) -> None:
		await self.send(json.dumps(event["json"]))

	async def receive(self, text_data="") -> None:
		if self.observer: return

		data = {}
		try:
			data = json.loads(text_data)
		except Exception as e:
			printe(f"data is not JSON: {text_data} with error {e}")
			await self.send(json.dumps({"error": True, "message": "data received is not a valid JSON data"}))
			return

		action = data.get("action", "")
		if action == "tournament_ready":
			printi(f"client {self.id}: {data}")
			await self.action_tournament_ready(data)
		elif action == "game_ready":
			printi(f"client {self.id}: {data}")
			await self.action_match_ready(data)
		elif action == "key_event":
			# printi(f"key event {self.id}: {data}")
			await self.action_move_paddles(data)

	# ---------------------------------------------------------------------------- #
	# --- Actions

	async def check_tournament_password(self, queryset) -> bool:
		return True
		tournament = self.games[self.id].tournament
		if tournament.password != "":
			pwd = queryset.get("pwd", "")
			pwd_hash = hash_pwd(pwd)
			printd(f"pwd_s: {pwd}")
			printd(f"pwd_d: {tournament.password}")
			if pwd_hash == tournament.password:
				return True
			return False
		return True

	async def add_observer(self) -> None:
		await self.channel_layer.group_add(
				self.group_name,
				self.channel_name,
			)
		self.observer = True
		game = self.games[self.id]
		game.add_observer(self.user)

		await self.send_json({
			"action": "new_observer",
			"id": self.user.id,
			"avatar": self.user.avatar,
			}, game.group_name)

		await self.send(json.dumps({
				"action": "users_connected",
				"players_list": self.games[self.id].players,
			}))

		# redirect user to correct page
		data:dict = {}
		if game.status == "started":
			data = {
					"action": "to_tournament",
					"tournament": game.tournament_structure.dict(),
				}
		elif game.status == "match":
			data = {
					"action": "to_game",
					"player_1": game.players_in_game[0],
					"player_2": game.players_in_game[1],
					"tournament": game.tournament_structure.dict(),
				}
		await self.send(json.dumps(data))

	async def action_tournament_ready(self, data:dict) -> None:
		await self.games[self.id].player_ready(self.user, data.get("ready", True))

		# send to all the user is ready
		await self.send_json({
				"action": "user_tournament_ready",
				"ready": data.get("ready", True),
				"id": self.user.player_id
			}, self.games[self.id].group_name)

		if await self.games[self.id].tournament_begin():
			printi("Tournament is starting...")
			self.tournaments[self.id].status = "started"
			await sync_to_async(self.tournaments[self.id].save)()

			# if it's a single match send game directly
			if len(self.games[self.id].players) == 2:
				self.games[self.id].status = "match"
				await self.send_json({
					"action": "to_game",
					"player_1": self.games[self.id].players_in_game[0],
					"player_2": self.games[self.id].players_in_game[1],
					"tournament": self.games[self.id].tournament_structure.dict(),
				}, self.games[self.id].group_name)
				return
			else:
				await self.games[self.id].revert_ready()
				await self.send_json({
					"action": "to_tournament",
					"tournament": self.games[self.id].tournament_structure.dict(),
				}, self.games[self.id].group_name)

			# set started in tournament status

	async def action_match_ready(self, data:dict) -> None:
		await self.games[self.id].player_ready(self.user, data.get("ready", True))

		await self.send_json({
				"action": "user_game_ready",
				"ready": data.get("ready", True),
				"id": self.user.player_id
			}, self.games[self.id].group_name)

		if await self.games[self.id].match_begin():
			printi("Send current match to all")
			await self.send_json({
					"action": "to_game",
					"player_1": self.games[self.id].players_in_game[0],
					"player_2": self.games[self.id].players_in_game[1],
					"tournament": self.games[self.id].tournament_structure.dict(),
				}, self.games[self.id].group_name)
			await self.games[self.id].revert_ready()

	async def action_move_paddles(self, data:dict) -> None:
		# async with self.update_lock[0]:
		game = self.games[self.id]
		match = game.match
		for i in range(len(game.players_in_game)):
			if game.players_in_game[i] == self.user.id:
				await match.key_pressed(i, data.get("key", "ArrowDown"), data.get("pressed", False))

	# ---------------------------------------------------------------------------- #
	# --- Match Loop ()

	async def match_1vs1(self, game:Game, pl_won:int) -> bool:
		if not len(game.players) == 2: return False
		await self.send_json({
				"action": "game_end",
				"winner": game.players_in_game[pl_won]
			}, game.group_name)
		await sync_to_async(game.match_end)(pl_won)
		await game.save_tournament_data(tournament=False) #TODO: set finished status in tournament
		await game.players_in_game_off()
		del self.games[game.game_id]
		return True

	async def not_active_players(self, game:Game) -> bool:
		for player in game.players.values():
			if player['disconnected'] == False:
				return False
		printi("All players left the game, deleting the record")
		await sync_to_async(game.tournament.delete)()
		for player in game.players_obj.values():
			await sync_to_async(player.leave_game)()
		self.send_json({
				"action": "to_main_menu"
			}, game.group_name)
		del self.games[game.game_id]
		return True

	async def tournament_match_finished(self, game:Game, pl_won:int) -> None:
		await sync_to_async(game.match_end)(pl_won)
		await game.next_match_data()
		
		printd("after next match data")
		if len(game.players) != 2:
			# match = game.match
			# await self.send_json({
			# 		"action": "game_refresh",
			# 		"match": await sync_to_async(match.dict)()
			# 	}, game.group_name)
			if game.tournament_structure.next_match[0] == None:
				await game.save_into_blockchain()
				await game.save_tournament_data()
				game.tournament_structure.status = "finished"
			await self.send_json({
				"action": "to_tournament",
				"tournament": await sync_to_async(game.tournament_structure.dict)(),
				"tx_hash": game.tx_hash,
			}, game.group_name)
			if game.tournament_structure.next_match[0] == None:
				await self.send_json({
						"action": "tournament_end",
					}, game.group_name)
				# await self.send_json({
				# 		"action": "tournament_end",
				# 	})
				await game.players_in_game_off()
				del self.games[game.game_id]

	# Main Game Loop
	async def game_loop(self) -> None:
		while 1:
			for game in self.games.copy().values():
				if game.status == "match":

					async with self.update_lock[0]:
						if await self.not_active_players(game):
							continue ;
						match = game.match
						await sync_to_async(match.move_ball_and_collide)()
						pl_won = await match.game_end()

						if pl_won != -1:
							if not await self.match_1vs1(game, pl_won):
								await self.tournament_match_finished(game, pl_won)
						else:
							await self.send_json({
									"action": "game_refresh",
									"match": await sync_to_async(match.dict)()
								}, game.group_name)

			await asyncio.sleep(ASYNC_SLEEP_TIME)

