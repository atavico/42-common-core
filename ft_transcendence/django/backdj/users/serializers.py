from rest_framework import serializers
from .models import Player

class PlayerSerializer(serializers.ModelSerializer):

	player_id = serializers.IntegerField()

	# def update(self, instance, data) -> Player:
	# 	instance.avatar = data.get('avatar', instance.avatar)
	# 	return instance

	class Meta:
		model = Player
		fields = [
			'player_id', 'username', 'games_played', 
			'games_won', 'games_lost', 'language', 
			'friend_list', 'avatar', 'in_game',
			'tournament_id', 'tournaments_played',
			'tournaments_placements'
			]

