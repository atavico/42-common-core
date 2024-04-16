
from rest_framework import serializers
from .models import GamesHistory, Tournament

class GamesHistorySerializer(serializers.ModelSerializer):

	class Meta:
		model = GamesHistory
		fields = [
			'date', 'won_by', 'lost_by', 'player1_score', 'player2_score',
			'tournament_game', 'tournament_stage'
			]


class TournamentSerializer(serializers.ModelSerializer):

	class Meta:
		model = Tournament
		fields = [
			'id', 'tournament_name', 'max_partecipants',
			'creator', 'friends_only', 'status',
			'players_id', 'placements', 'is_active',
			'game_type', 'score_to_win', 'password',
			'started', 'end_timestamp'
			]

class GetTournamentSerializer(serializers.ModelSerializer):

	class Meta:
		model = Tournament
		fields = [
			'id', 'tournament_name', 'max_partecipants',
			'creator', 'friends_only', 'status',
			'players_id', 'placements', 'is_active',
			'game_type', 'score_to_win', 'started',
			'end_timestamp'
			]
