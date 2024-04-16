
import json

from django import forms
from django.db import models
from django.contrib.auth.models import AbstractUser, PermissionsMixin
from django.core.validators import RegexValidator
from django.utils.translation import gettext_lazy as _
from utilities.logger import printd, printe, printi


from django.conf import settings
from django.db.models.signals import post_save
from django.dispatch import receiver
from rest_framework.authtoken.models import Token
from utilities.enums import PERMITTED_LANGUAGES

# Unusued imports that may be needed
# from django.core.exceptions import ValidationError
from utilities.logger import log


class User(AbstractUser, PermissionsMixin):
	oauth_42 		= models.BooleanField(default=False)
	token 			= models.TextField(default=None, null=True)

	username = models.CharField(_('username'), unique=False, max_length=30, null=True,
			help_text=_('Required. 30 characters or fewer. Letters, digits and ''@/./+/-/_ only.'),
		validators=[RegexValidator(r'^[\w.@+-]+$', _('Enter a valid username.'), 'invalid')
		])

	email = models.EmailField(unique=True, null=False,
			help_text=_('Required. Letters, digits and ''@/./+/-/_ only.'),
		validators=[RegexValidator(r'^[\w.@+-]+$', _('Enter a valid email address.'), 'invalid')
		])

	password2 = forms.CharField(
		label=_("Password confirmation"),
		widget=forms.PasswordInput,
		help_text=_("Enter the same password as above, for verification."))

	USERNAME_FIELD = 'email'
	REQUIRED_FIELDS = ['password']

	def generate_random_psw(self):
		return "Passw@rdFi11&r"

	@classmethod
	def create(cls, username:str="", email:str="", oauth:bool=False):
		user = cls(
			username	= username,
			email		= email,
			password	= "Passw@rdFi11&r",
			oauth_42	= oauth,
			)
		return user


# create Token on User Save into DB (signal)
@receiver(post_save, sender=settings.AUTH_USER_MODEL)
def create_auth_token(sender, instance=None, created=False, **kwargs):
	if created:
		log.info("Creating Token for user")
		Token.objects.create(user=instance)


class User42(models.Model):
	player_id	= models.BigIntegerField(unique=True)
	id42 		= models.BigIntegerField(null=False, unique=True)
	email		= models.EmailField(unique=True, null=False)
	username 	= models.CharField(null=False, unique=True, max_length=9)
	avatar_url	= models.URLField(
		blank=True,
		default="users/avatars/default.png"
		)

	token 				= models.TextField(default="")
	refresh_token 		= models.TextField(default="")
	token_created_at 	= models.BigIntegerField(null=False, default=0)
	token_valid_until 	= models.BigIntegerField(null=False, default=0)

	#TODO: look if token expired
	def token_is_valid(self) -> bool:
		return True

	@classmethod
	def create(cls, user:dict, player_id:int, tokens_data:dict):
		user42 = cls(
			player_id	= player_id,
			id42 		= user.get('id'),
			email 		= user.get('email'),
			username 	= user.get('login'),
			avatar_url 	= user.get('image', {}).get(
				"link",
				"users/avatars/default.png"),

			token				= tokens_data.get("access_token", "empty"),
			refresh_token 		= tokens_data.get("refresh_token", "empty"),
			token_created_at 	= tokens_data.get("created_at", 0),
			token_valid_until 	= tokens_data.get("secret_valid_until", 0),
			)
		return user42


class Player(models.Model):
	player_id 		= models.BigIntegerField(unique=True)
	username		= models.CharField(max_length=12)
	games_played	= models.BigIntegerField(default=0)
	games_lost		= models.BigIntegerField(default=0)
	games_won		= models.BigIntegerField(default=0)
	language		= models.CharField(max_length=2, default="en")
	friend_list		= models.TextField(default="[]")
	tournament_id	= models.BigIntegerField(unique=False, default=-1)
	in_game			= models.BooleanField(default=False)
	avatar			= models.TextField(default="")
	tournaments_played	= models.BigIntegerField(default=0)
	tournaments_placements 	= models.TextField(default="[0, 0, 0]")

	@classmethod
	def create(cls, username:str, pid:int):
		player = cls(username=username, player_id=pid)
		return player

	def set_language(self, lang) -> None:
		if lang in PERMITTED_LANGUAGES:
			self.language = lang
		else:
			log.error("Unpermitted language choice <unchanged>")

	# remove friend from player friend list
	def remove_friend(self, friend_id:int) -> list:
		jf:list = json.loads(self.friend_list)
		if friend_id in jf:
			jf.remove(friend_id)
			self.friend_list = json.dumps(jf)
			self.save()
		return self.friend_list

	def __str__(self) -> str:
		return self.username

	def to_game_dict(self) -> dict:
		return {
			"id": self.player_id,
			"username": self.username,
			"ready": False,
			"ingame": -1,
			"disconnected": False,
			"avatar": self.avatar
		}

	def leave_game(self) -> None:
		self.in_game = False
		self.tournament_id = -1
		self.save()

	def match_played(self) -> None:
		self.games_played += 1

	def match_won(self) -> None:
		self.games_won += 1
		self.match_played()
		self.save()

	def match_lost(self) -> None:
		self.games_lost += 1
		self.match_played()
		self.save()

	def save_placement(self, position:int=8) -> None:
		try:
			printi(f"Save player placement -> {position}")
			if position < 3:
				placed = json.loads(self.tournaments_placements)
				placed[position] += 1
				self.tournaments_placements = json.dumps(placed)
			self.tournaments_played += 1
			self.save()
		except Exception as e:
			printe(f"Failed to save player placement: {e}")


class FriendRequest(models.Model):
	# s_enum = {"0": "pending", "1": "accepted", "-1": "rejected"} 

	creator = models.BigIntegerField(unique=False, null=False, default=0)
	receiver = models.BigIntegerField(unique=False, null=False, default=0)
	status = models.TextField(default="pending") # status -> pending, completed | facoltativo rejected, accepted
	
	@classmethod
	def create(cls, creator_id:int = -1, receiver_id:int = -1):
		req = cls(creator=creator_id, receiver=receiver_id)
		return req
	
	def dict(self) -> dict:
		return {
			"creator": self.creator,
			"receiver": self.receiver,
			"status": self.status
		}

	def __str__(self) -> str:
		return f"Creator <{self.creator}> sent a friend request to <{self.receiver}>, status: {self.status}"
