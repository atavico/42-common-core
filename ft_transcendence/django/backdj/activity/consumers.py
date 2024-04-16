
import json
from channels.generic.websocket import AsyncWebsocketConsumer
from rest_framework.authentication import SessionAuthentication, BasicAuthentication
from rest_framework.authtoken.models import Token
from asgiref.sync import sync_to_async

from users.models import *
from utilities.utils import * 
from utilities.logger import printe, printd, printi, printw

testing:bool = False
id_count:list = [0]

# WebSocket that enable an active users list
class ActivityConsumer(AsyncWebsocketConsumer):
	authentication_classes = [SessionAuthentication, BasicAuthentication]
	player_list:set = set()

	def __init__(self, *args, **kwargs) -> None:
		super().__init__(*args, **kwargs)
		self.my_id:int = -1
		self.username:str = ""
		self.to_remove:bool = True
		self.player:Player = None
		self.group_name:str = "active_users"

	async def connect(self) -> None:
		# printd(self.scope)
		# printd(f"data: {self.scope['query_string']}")
		
		token = self.scope['query_string'].decode('utf-8')
		await self.accept()
		if token and await self.set_id_by_token(token.split("=")[1]):
			await self.set_user_data()
			await self.add_user_to_list()
		else:
			await self.close()

	async def disconnect(self, conn) -> None:
		if not self.to_remove:
			await self.close()
			return
		if self.my_id != -1: 
			await self.remove_user_from_list()
		await self.close()

	async def set_id_by_token(self, token:str) -> bool:
		tok = None
		try:
			# printd(f"token: {token}")
			tok = await sync_to_async(Token.objects.get)(key=token)
			# printi(f"retrieved user id -> {tok.user_id}")
			self.my_id = tok.user_id
			return True
		except Token.DoesNotExist:
			printe("Token does not exist...")
		except Exception as e:
			printe(f"Another error while checking token -> {e}")
		return False

	async def set_user_data(self) -> None:
		try:
			self.player = await sync_to_async(Player.objects.get)(player_id=self.my_id)
			self.username = self.player.username
			printi(f"New player is connecting -> {self.username} #{self.player.player_id}")
		except Exception as e:
			printe(f"Cannot retrieve player data! {e}")

	async def get_user_id(self) -> int:
		if not testing: return self.my_id #self.scope["user"].id
		if self.my_id == -1: self.my_id = id_count[0]; id_count[0] += 1
		return self.my_id

	async def get_active_users(self) -> set:
		return self.player_list

	async def add_user_to_list(self) -> None:
		if await self.get_user_id() in self.player_list:
			printw("player already logged with another client")
			await self.send(json.dumps({
					"action": "already_logged",
					"status": True,
				}))
			self.to_remove = False
			await self.close()
			return

		await sync_to_async(self.player_list.add)(await self.get_user_id())
		
		await self.channel_layer.group_add(
			self.group_name,
			self.channel_name
		)
		await self.send_active_list(await self.get_user_id())

	async def remove_user_from_list(self) -> None:
		await self.channel_layer.group_discard(
			self.group_name,
			self.channel_name
		)
		await sync_to_async(self.player_list.remove)(await self.get_user_id())
		await self.send_active_list(await self.get_user_id(), left=True)

	async def send_active_list(self, user_id:int, left:bool=False) -> None:
		active_users:set = await self.get_active_users()
		data:dict = {
			"action": "join_leave",
			"active_users": list(active_users),
			"left": left,
			"event_user_id": user_id, 
		}
		
		await self.channel_layer.group_send(
			self.group_name, 
			{
				"type": "new_event",
				"json": data
			})

	async def receive(self, text_data):
		data = json.loads(text_data)
		action:str = data.get("action", "")
		if action == "change_name":
			printd(f"Change name data: {data}")
			await self.send_to_all(data)
		elif action == "friend_deleted":
			printd(f"Deleted friend: {data}")
			await self.send_to_all({
					"action": "friend_deleted",
					"player_id": data.get("friend_id")
				})
		elif action == "friend_added":
			printd(f"Friend added: {data}")
			await self.send_to_all({
					"action": "friend_added",
					"player_id": data.get("friend_id")
				})
		elif action == "new_friend_request":
			printd(f"New Friend Request added: {data}")
			await self.send_to_all({
					"action": "new_friend_request",
					"player_id": data.get("friend_id")
					})
		elif action == "player_deleted":
			printd(f"player_deleted {data}")
			await self.send_to_all({
					"action": "player_deleted",
					"player_id": self.my_id,
				})

	async def send_to_all(self, json) -> None:
		await self.channel_layer.group_send(
				self.group_name,
				{
					"type": "new_event",
					"json": json
				})

	async def new_event(self, event:dict) -> None:
		await self.send(json.dumps(event["json"]))

