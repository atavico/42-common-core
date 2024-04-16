
import json
from django.db import models
from datetime import datetime

# Played Games, won or lost
class GamesHistory(models.Model):
	date = models.DateTimeField(auto_now_add=True)
	won_by = models.PositiveIntegerField()
	lost_by = models.PositiveIntegerField()
	player1_score = models.PositiveIntegerField()
	player2_score = models.PositiveIntegerField()
	tournament_game = models.BooleanField(default=False)
	tournament_stage = models.TextField(default="")

	class Meta:
		ordering = ['date']

		def __unicode__(self):
			return (self.__str__())

	@classmethod
	def create(cls, match, p_won:int, p_lost:int, turn:str=""):
		history_game = cls(
			date = datetime.now(),
			won_by = p_won,
			lost_by = p_lost,
			player1_score = max(match.score),
			player2_score = min(match.score),
			tournament_game = True if turn != "" else False,
			tournament_stage = turn,
			)
		return history_game

	def __str__(self) -> str:
		return f"""
date: {self.date.strftime("%m/%d/%Y, %H:%M:%S")}
game: {self.won_by} vs {self.lost_by}
scores: {self.player1_score} | {self.player2_score}
{ "tournament stage -> " + str(self.tournament_stage) if self.tournament_game else ""}
winner: {self.won_by}
"""


class Tournament(models.Model):
	tournament_name = models.TextField(default='Tournament X')
	
	game_type = models.TextField(default="tournament") # "single match"
	friends_only = models.BooleanField(default=False)
	password = models.CharField(max_length=200, default="", blank=True)
	score_to_win = models.PositiveSmallIntegerField(default=3)
	max_partecipants = models.PositiveSmallIntegerField(default=8) #why not PositiveSmallIntegerField?
	
	creator = models.BigIntegerField(null=False, default=-1)
	status = models.TextField(default='pending')
	players_id = models.TextField(default="[]") # [id1, id2, ...]
	placements = models.TextField(default="[]") # array of players ids and their placement

	structure = models.TextField(default="")

	is_active = models.BooleanField(default=True)
	started = models.BooleanField(default=False)
	tx_hash = models.TextField(default="")

	end_timestamp = models.DateTimeField(auto_now_add=True)

	def set_finished(self, structure) -> None:
		self.structure = structure.dict()
		self.placements = json.dumps(structure.placements)
		self.status = "finished"
		self.end_timestamp = datetime.now()
		self.save()

	def add_player(self, player_id:int=-1) -> None:
		j = json.loads(self.players_id)
		if not player_id in j:
			j.append(player_id)
			j = list(dict.fromkeys(j))
			self.players_id = json.dumps(j)
			self.save()

	def remove_player(self, player_id:int=-1) -> None:
		j = json.loads(self.players_id)
		if not player_id in j: return
		j.remove(player_id)
		self.players_id = json.dumps(j)
		self.save()

	def __str__(self) -> str:
		return f"""
players: {self.players_id}
placements: {self.placements}
"""

"""
{
	"game_type": "tournament" # "single_match",
	"is_active": bool,
	"friends_only": bool,
	"password": string, # null or "password"
	"friends_list": [id1, id2...], # lista id consentiti
	"creator": host_id:int,
	"status": "queue", # | "started" | "ended"
	"score_to_win": int,
}
"""
	
	#curl -X POST https://localhost:8000/create_tournament/ -d "tournament_name=Test Tournament&max_participants=8&only_friends=False"
