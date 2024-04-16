
from rest_framework import serializers
from .models import LocalMatchesHistory, LocalTournamentsHistory

class LocalMatchesHistorySerializer(serializers.ModelSerializer):

	class Meta:
		model = LocalMatchesHistory
		fields = [
			'date', 'username', 'winner', 'player1', 
			'player2', 'p1_score', 'p2_score',
			'tournament_game', 'tournament_stage'
			]

class LocalTournamentsHistorySerializer(serializers.ModelSerializer):

	class Meta:
		model = LocalTournamentsHistory
		fields = [
			'date', 'username', 'winner', 'player1', 
			'player2', 'p1_score', 'p2_score',
			'tournament_game', 'tournament_stage'
			]
