
from rest_framework.views import APIView
from rest_framework.authentication import SessionAuthentication, BasicAuthentication

from users.views import user_does_not_exist
from utilities.decorators import login_required_in_class
from utilities.response import JSONResponse
from utilities.logger import printi, printe
from utilities.utils import get_player

from .models import *
from .serializers import *


class LocalMatchesHistoryApiView(APIView):
	authentication_classes = [SessionAuthentication, BasicAuthentication]
	http_method_names = ["get", "post"]

	def get_games(self, user_id:int):
		try:
			data = LocalMatchesHistory.objects.filter(user_id=user_id)
			return data
		except:
			return None

	def related_games_empty(self, user_id:int) -> JSONResponse:
		return JSONResponse(
			error_code = 200,
			message = f"Player with user id <{user_id}> does not have local played games",
			data = {"games": [], "empty": True}
		)

	@login_required_in_class
	def get(self, request:any, player_id:int = None, *args, **kwargs) -> JSONResponse:
		if player_id == None: player_id = request.user.id
		if player_id == None: return user_does_not_exist(player_id)

		games = self.get_games(player_id)
		if not games: return self.related_games_empty(player_id)

		serialized = LocalMatchesHistorySerializer(games, many=True)
		return JSONResponse(data={"games": serialized.data , "empty": False})

	@login_required_in_class
	def post(self, request:any, *args, **kwargs) -> JSONResponse:
		player_id = request.user.id
		if player_id == None: return user_does_not_exist(player_id)

		data = request.body
		local_match = LocalMatchesHistory.objects.create()
		serialized = LocalMatchesHistorySerializer(
			instance=local_match,
			data=data, 
			partial=True
			)

		if not serialized.is_valid():
			printe(f"Error while saving local match to history: {serialized.errors}")
			return JSONResponse(error=True, error_code=400,
				message=f"Invalid input fields..")

		local_match.user_id = request.user.id
		pl = get_player(request.user.id)
		if pl:
			local_match.username = pl.username
		else:
			return JSONResponse(message="error while retrieving player", error_code=400)
		serialized.update(local_match, serialized.validated_data)
		serialized.save()
		printi(f"Local Match recorded successfully")
		return JSONResponse(data=serialized.data, error_code=200)


class LocalTournamentsHistoryApiView(APIView):
	authentication_classes = [SessionAuthentication, BasicAuthentication]
	http_method_names = ["get", "post"]

	def get_games(self, user_id:int):
		try:
			data = LocalTournamentsHistory.objects.filter(user_id=user_id)
			return data
		except:
			return None

	def related_games_empty(self, user_id:int) -> JSONResponse:
		return JSONResponse(
			error_code = 200,
			message = f"Player with user id <{user_id}> does not have local played tournaments",
			data = {"tournaments": [], "empty": True}
		)

	@login_required_in_class
	def get(self, request:any, player_id:int = None, *args, **kwargs) -> JSONResponse:
		if player_id == None: player_id = request.user.id
		if player_id == None: return user_does_not_exist(player_id)

		games = self.get_games(player_id)
		if not games: return self.related_games_empty(player_id)

		serialized = LocalTournamentsHistorySerializer(games, many=True)
		return JSONResponse(data={"tournaments": serialized.data , "empty": False})

	@login_required_in_class
	def post(self, request:any, *args, **kwargs) -> JSONResponse:
		player_id = request.user.id
		if player_id == None: return user_does_not_exist(player_id)

		data = request.body
		local_tournament = LocalTournamentsHistory.objects.create()
		serialized = LocalTournamentsHistorySerializer(
			instance=local_tournament,
			data=data, 
			partial=True
			)

		if not serialized.is_valid():
			printe(f"Error while saving local tournament to history: {serialized.errors}")
			return JSONResponse(error=True, error_code=400,
				message=f"Invalid input fields..")

		local_tournament.user_id = request.user.id
		pl = get_player(request.user.id)
		if pl:
			local_tournament.username = pl.username
		else:
			return JSONResponse(message="error while retrieving player", error_code=400)
		serialized.update(local_tournament, serialized.validated_data)
		serialized.save()
		printi(f"Local Tournament recorded successfully")
		return JSONResponse(data=serialized.data, error_code=200)
