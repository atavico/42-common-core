# from django.shortcuts import render
from rest_framework.views import APIView
# from rest_framework.decorators import api_view, renderer_classes
# from rest_framework.renderers import JSONRenderer, TemplateHTMLRenderer
from rest_framework.authentication import SessionAuthentication, BasicAuthentication
from rest_framework.decorators import api_view, renderer_classes

from users.models import Player
from users.views import user_does_not_exist, get_user_by_tkn
from blockchain.blockchain import get_match 


from .models import *
from .serializers import *


from utilities.decorators import login_required, login_required_in_class
from utilities.response import JSONResponse
from utilities.logger import printd, printe, printi, printw
from utilities.hash import hash_pwd

# Create your views here.
class GamesHistoryApiView(APIView):
	# permission_classes = [permissions.IsAuthenticated]
	authentication_classes = [SessionAuthentication, BasicAuthentication]
	http_method_names = ["get"]

	#TODO: get player games
	def get_games(self, user_id:int):
		try:
			data = GamesHistory.objects.filter(won_by=user_id) | GamesHistory.objects.filter(lost_by=user_id)
			return data
		except:
			return None

	def related_games_empty(self, user_id:int) -> JSONResponse:
		return JSONResponse(
			error_code = 200,
			message = f"Player with user id <{user_id}> does not have played games",
			data = {"games": [], "empty": True}
		)

	@login_required_in_class
	def get(self, request:any, player_id:int = None, *args, **kwargs) -> JSONResponse:
		if player_id == None:
			player_id = request.user.id

		if player_id == None:
			return user_does_not_exist(player_id)

		games = self.get_games(player_id)
		if not games:
			return self.related_games_empty(player_id)

		serialized = GamesHistorySerializer(games, many=True)
		return JSONResponse(data={"games": serialized.data , "empty": False})

class TournamentApiView(APIView):
	# authentication_classes = [SessionAuthentication, BasicAuthentication]
	http_method_names = ["post", "get"]

	@login_required_in_class
	def post(self, request:any) -> JSONResponse:
		# printd(request)
		user = request.user
		if not user:
			return JSONResponse(error_code=401, message="Unauthorized action, relog")

		user_id:int = user.id
		tournament = Tournament.objects.create()
		
		try:
			Player.objects.get(player_id=user_id)
		except Player.DoesNotExist:
			return user_does_not_exist(user_id)

		data = request.body
		data['players_id'] = str([user_id])
		data['creator'] = user_id
		data['password'] = ""
		# if 'password' in data and not data['password'] in ["...", ""]:
		# 	printw(f"password before: {data['password']}")
		# 	data['password'] = hash_pwd(data['password']).decode("utf-8")
		# 	printw(f"password after: {data['password']}")
		serialized:TournamentSerializer = TournamentSerializer(instance=tournament, data=data, many=False)

		# printd(f"Tournament POST ser: {serialized.initial_data}")
		if not serialized.is_valid():
			printw(f"serialized errors: {serialized.errors}")
			return JSONResponse(error=True, error_code=400,
				message="Input field is invalid", data={"error": serialized.errors})

		# tor_inst = serialized.create(serialized.validated_data)
		serialized.save()
		ndict = dict(serialized.validated_data)
		ndict.update({'password': '', 'id': tournament.id})
		printd(f"returning dict: {ndict}")
		return JSONResponse(data=ndict, error_code=201)
	
	# in-game request
	@login_required_in_class
	def put(self, request:any) -> JSONResponse:
		pass


	def transform_pwd(self, serialized) -> list:
		ll = []
		for e in serialized.data:
			n = dict(e)
			n["password"] = True if n["password"] != "" else False
			ll.append(n)
		return ll

	# TODO: do not send pwd
	#@login_required_in_class
	def get(self, request:any, tournament_id:int = None) -> JSONResponse:
		if tournament_id == None:
			tournaments = Tournament.objects.all()
			serialized = TournamentSerializer(tournaments, many=True)
			return JSONResponse(
					error_code=200,
					message="All tournaments",
					data=self.transform_pwd(serialized)
				)
		
		try:
			tournament = Tournament.objects.get(tournament_id=tournament_id)
		except Tournament.DoesNotExist:
			tournament = None

		serialized = TournamentSerializer(tournament, many=False)
		return JSONResponse(error_code=200,
				message="Your tournament",
				data=self.transform_pwd(serialized)
			)

"""	
POST game:
	curl -X POST -k https://localhost:8000/api/tournaments/ \
	-H "Authorization: Bearer 58c14775e870245165f5f4bf4289dc1407264e6c" \
	-H "withCredentials: true" -H "Referer: https://localhost:4343" \
	# -d "postdata=toFillWithModelOptions" 

GET list:
	curl -X POST/GET -k https://localhost:8000/api/tournaments/
"""

@login_required
@api_view(("GET", ))
def get_tournaments_played(request, player_id:int=None) -> JSONResponse:
	played_tournaments:list = []
	try:
		tournaments = Tournament.objects.filter(status="finished", game_type="Tournament")
		for t in tournaments:
			if (player_id in json.loads(t.players_id)): 
				t.password = ""
				played_tournaments.append(t)
		# printw(f"played tournaments: {played_tournaments}")
		ser_ts = TournamentSerializer(instance=played_tournaments, many=True)
	except Exception as e:
		printe(f"Exception in retrieving played tournaments --> {e}")
		return JSONResponse(
			error_code=400,
			message="Cannot retrieve played tournaments",
			data={"tournaments": [], "empty": True},
			)

	return JSONResponse(
			message="Played tournaments retrieved successfully",
			data={"tournaments": ser_ts.data, "empty": False},
		)
