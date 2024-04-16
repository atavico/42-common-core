
from random import choice
import json
from users.models import *
from .enums import ANIMALS
from .response import JSONResponse
from .logger import printd, printi, printe, printw
from users.serializers import *
from tournaments.serializers import *


def user_does_not_exist(user_id:int) -> JSONResponse:
	return JSONResponse(
		error = True, error_code = 400,
		message = f"Player with id <{user_id}> does not exists",
	)


def is_a_42_user(email:str) -> bool:
	try:
		user = User.objects.get(email=email)
		if user.oauth_42:
			return True
	except Exception:
		pass
	return False


def generate_name() -> str:
	return f"{choice(ANIMALS)}"


def get_player_info(p_instance=None, u_instance=None, tokenize=False) -> dict:
	data = {"message": "Something went wrong...", "error": True}
	if p_instance:
		data = PlayerSerializer(instance=p_instance, many=False).data
		if tokenize and u_instance: 
			token, created = Token.objects.get_or_create(user=u_instance)
			data["Token"] = str(token)
	return data


def get_player(id:int) -> Player:
	try:
		return Player.objects.get(player_id=id)
	except Exception as e:
		printe(f"Cannot retrieve Player <{id}>, {e}")
	return None


def get_token_from_request(request) -> str:
	# printd(f"request method is: {request.method}")
	if request.method == "POST":
		request.body = json.loads(request.body)
	try:
		tkn:str = request.META.get('HTTP_AUTHORIZATION')
		# printd(tkn)
		tkn_split:str = tkn.split(" ")
		if not tkn_split[0] == "Bearer": return None
		return tkn_split[1]
	except Exception as e:
		printw(f"Error while retrieving token from request: {e}")
	return None


def get_user_by_tkn(request):
	token:str = get_token_from_request(request)
	# printd(f"request.post: {request}\ntoken: {token}")
	# printd(f"HTTP: {request.META.get('HTTP_AUTHORIZATION')}")
	if not token:
		return None # JSONResponse(error_code=400, message="Invalid Token, relog")
	try:
		tkn = Token.objects.get(key=token)
		user = tkn.user
		return user
	except Exception:
		pass
	printd("Invalid Token, relog")
	return None
	# JSONResponse(error_code=400, message="Invalid Token, relog")


def add_id_to_friend_list(user:Player, new_friend_id:int) -> list:
	friend_list = json.loads(user.friend_list)
	friend_list.append(new_friend_id)
	user.friend_list = json.dumps(friend_list)
	user.save()

