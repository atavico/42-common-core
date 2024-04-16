
from django.db import models

class LocalTournamentsHistory(models.Model):
	user_id = models.BigIntegerField(default=-1)
	username = models.CharField(max_length=8, default="") # nome dell'account in quel momento
	players = models.TextField(default="[]")
	winner = models.CharField(max_length=8, default="")
	second = models.CharField(max_length=8, default="")
	date = models.DateTimeField(auto_now_add=True)


class LocalMatchesHistory(models.Model):
	user_id = models.BigIntegerField(default=-1)
	username = models.CharField(max_length=8, default="")
	winner = models.CharField(max_length=8, default="")
	player1 = models.CharField(max_length=8, default="")
	player2 = models.CharField(max_length=8, default="")
	p1_score = models.PositiveSmallIntegerField(default=0)
	p2_score = models.PositiveSmallIntegerField(default=0)
	date = models.DateTimeField(auto_now_add=True)
	tournament_game = models.BooleanField(default=False)
	tournament_stage = models.TextField(default="", blank=True)
