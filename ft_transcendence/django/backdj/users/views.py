
import json#, functools

# from django.template.response import SimpleTemplateResponse
# from rest_framework import status, permissions
# from django.contrib import messages
# from django.conf import settings

from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.decorators import api_view, renderer_classes
from rest_framework.renderers import JSONRenderer, TemplateHTMLRenderer
from rest_framework.authentication import SessionAuthentication, BasicAuthentication
from rest_framework.authtoken.models import Token
from rest_framework.authtoken.views import ObtainAuthToken
from django.contrib.auth import authenticate, login
from utilities.utils import *
from django.conf import settings

from .users import RegisterForm #, LoginForm
from .models import *
from .serializers import *

from utilities.response import JSONResponse
from utilities.decorators import login_required, login_required_in_class

from utilities.logger import log, printd, printe, printi, printw
print = log.debug


class LoginView(ObtainAuthToken):

	def post(self, request):
		email = request.data.get('email', '')

		if is_a_42_user(email):
			return JSONResponse(
				error_code = 401,
				message = "This user cannot login with a password",
				data = {"message": "This user cannot login with a password"}
			)

		password = request.data.get('password', '')
		user = authenticate(email=email, password=password)
		
		if user:
			token, created = Token.objects.get_or_create(user=user)
			if settings.TOKEN_REFRESH_AT_EVERY_LOGIN:
				token.delete()
				token = Token.objects.create(user=user)
			player = Player.objects.get(player_id=user.id)
			login(request, user)

			response = JSONResponse(
				error_code = 200,
				message = "Login succeded",
				token=token.key,
				data = get_player_info(player, user, tokenize=False),
				cookie_gen=True
				)
			return response

		return JSONResponse(
			error_code = 401,
			message='invalid credentials',
			data={"message": 'invalid credentials'}
			)

class PlayerApiView(APIView):
	# permission_classes = [permissions.IsAuthenticated]
	authentication_classes = [SessionAuthentication, BasicAuthentication]
	http_method_names = ["get", "put"]

	def get_obj(self, user_id:int) -> Player:
		try:
			return Player.objects.get(player_id=user_id)
		except Player.DoesNotExist:
			return None

	@login_required_in_class
	def get(self, request:any, player_id:int = None, *args, **kwargs) -> Response:
		if player_id == None: player_id = request.user.id 
		player = self.get_obj(player_id)
		if not player: 
			return user_does_not_exist(player_id)
		serialized = PlayerSerializer(player, many=False)

		return JSONResponse(data=serialized.data)

	@login_required_in_class
	def put(self, request:any, *args, **kwargs) -> JSONResponse:
		# printd("Player PUT request")
		player = self.get_obj(request.user.id)
		if not player:
			return user_does_not_exist(request.user.id)

		# printd(f"body: {request.body}")
		data = json.loads(request.body.decode("utf-8"))
		serialized = PlayerSerializer(instance=player, data=data, partial=True)

		if not serialized.is_valid():
			printe(serialized.errors)
			return JSONResponse(error=True, error_code=400,
				message=f"Input field is invalid -> {serialized.errors}")

		serialized.update(player, serialized.validated_data)
		serialized.save()
		printd(f"Player <{request.user.id}> updated successfully!")
		return JSONResponse(data=serialized.data, error_code=201)


# --------------------------------------------------------------------------- #
# --- Registration Login Methods


@api_view(('POST',))
def sign_up(request):
	form = RegisterForm(request.data)
	print(form.data)
	if form.is_valid():

		user = form.save(commit=False)
		# print("(SignUp) ", form.cleaned_data['password1'])
		user.set_password(form.cleaned_data['password1'])
		user.save() # save to generate user id
		player = Player.create(generate_name(), user.id)
		player.save()
		
		# instantiate a dict object to send back, it will also contain the token!
		data = get_player_info(player, u_instance=user, tokenize=True)
		login(request, user)

		return JSONResponse(
				data = data,
				token = data.get("token"),
				cookie_gen = True,
				message = f"Signed up successfully",
				error_code = 201
			)

	return JSONResponse(
			data = form.errors.as_json(),
			error = True,
			message = f"Cannot sign up",
			error_code = 400,
		)

@api_view(('GET',))
@login_required
def player_names(request) -> JSONResponse:
	# printd(f"player_names: {request.user.id}")
	query = request.GET.dict()
	users:dict = {}
	if len(query) == 0:
		players = Player.objects.values()
		for p in players:
			users[p['player_id']] = p['username']
		return JSONResponse(
				error_code = 200,
				message = "User list retrieved successfully",
				data = users,
			)

	# printd("Player names query: ", query)
	user_list = query.values()
	for uid in user_list:
		try:
			player = Player.objects.get(player_id=int(uid))
			users[str(uid)] = player.username
		except Player.DoesNotExist:
			printd(f"Player <{uid}> does not exists in db")
		except Exception as e:
			printd(f"Another error while retrieving player <{uid}> name -> {e}")
	if len(users) > 0:
		return JSONResponse(
			error_code = 200,
			message = "User list retrieved successfully",
			data = users,
			)
	return JSONResponse(
			error_code = 400,
			message = "No usernames retrieved, check your list",
		)


@api_view(('GET',))
@renderer_classes((JSONRenderer, TemplateHTMLRenderer))
@login_required
def in_game(request):
	player_id = request.user.id
	try:
		player = Player.objects.get(player_id=player_id)
	except Player.DoesNotExist:
		return user_does_not_exist(player_id)
	except Exception as e:
		printe(f"Error retrieving in game status from player <{player_id}>, error: {e}")
		return JSONResponse(error_code=400, message="Error retrieving game status")

	return JSONResponse(
			data={
				"in_game": player.in_game,
				"tournament_id": player.tournament_id,
				},
			error_code = 200,
		)


@api_view(('POST', ))
@login_required
def user_avatar_update(request):
	# user = request.user
	pl = get_player(2) #user.id)
	new_player = PlayerSerializer(pl, data=request.data, partial=True)
	if new_player.is_valid():
		printd(new_player.instance)
		new_player.save()
		return JSONResponse(
			error_code = 201,
			message="Image uploaded correctly",
			data={"avatar": new_player.data['avatar']}
			)
	return JSONResponse(error_code=400, message="Cannot upload image", data=new_player.errors)


@api_view(('GET', ))
def get_user_by_token(request):
	token:str = get_token_from_request(request)
	if not token:
		return JSONResponse(error_code=400, message="Invalid Token, relog")
	try:
		tkn = Token.objects.get(key=token)
		user = tkn.user
		player = Player.objects.get(player_id=user.id)
		data = PlayerSerializer(instance=player, many=False).data
		login(request, user)
	except Token.DoesNotExist:
		printd("Invalid Token, relog")
		return JSONResponse(error_code=400, message="Invalid Token, relog")
	except User.DoesNotExist:
		printd("Invalid User")
		return JSONResponse(error_code=400, message="User got banned/deleted")
	except Exception as e:
		printe(f"Error retrieving user from token {e}")
		return JSONResponse(error_code=400, message=f"Another error occurred")

	printd("User by token retrieved")
	return JSONResponse(
		message='Token valid, retrieved user',
		data=data,
		)


@api_view(('POST', ))
@login_required
def add_friend_request(request):
	user = request.user
	printd(f"Sending friend request: {user.id}")
	player = get_player(user.id)
	if not player:
		return JSONResponse(
				error_code=400, message="Bad request: invalid user id"
			)
	pl_id = player.player_id
	friend_list:list = json.loads(player.friend_list)

	# esiste già l'amicizia?
	friend_id:int = request.body.get("receiver_id", -1)
	friend_player = get_player(friend_id)
	if not friend_player:
		return JSONResponse(error_code=400, message="Bad request: invalid friend id")
	elif friend_player.player_id in friend_list:
		return JSONResponse(error_code=400, message=f"Already friend with <{friend_id}>")

	# controllo richiesta già esistente
	try:
		fq2 = FriendRequest.objects.get(creator=friend_id, receiver=player.player_id)
	except FriendRequest.DoesNotExist:
		fq2 = None

	if fq2:
		return JSONResponse(error_code=400, message="The other user already requested the friendship")

	fq, created = FriendRequest.objects.get_or_create(
		creator=pl_id,
		receiver=friend_id,
		defaults={'creator': pl_id, 'receiver': friend_id})

	if not created:
		return JSONResponse(
			error_code=400,
			message="Request already exists",
			data={'request': str(fq)}
			)

	fq.save()
	return JSONResponse(error_code=201, message="Created request successfully", data={'friend_request': str(fq)})


# OBSOLETE
@api_view(('GET', ))
@login_required
def get_friend_requests(request):
	player:Player = get_player(request.user.id)
	if not player:
		return JSONResponse(
				error_code=400, message="Bad request: invalid user id"
			)
	pl_id:int = player.player_id

	fqs = FriendRequest.objects.filter(receiver=pl_id, status="pending")
	data:list = [f.dict() for f in fqs] # CHECK
	printd(data)
	return JSONResponse(
			message="successfully retrieved friend request list",
			data=data if data != [] else "empty"
		)


@api_view(('GET', ))
@login_required
def get_pending_friend(request) -> JSONResponse:
	player:Player = get_player(request.user.id)
	if not player:
		return JSONResponse(
				error_code=400, message="Bad request: invalid user id"
			)

	pl_id:int = player.player_id

	
	fq1 = FriendRequest.objects.filter(creator=pl_id, status="pending")
	fq2 = FriendRequest.objects.filter(receiver=pl_id, status="pending")
	
	data:list = []
	if fq1 != []: data += [f.dict() for f in fq1]
	if fq2 != []: data += [f.dict() for f in fq2]

	return JSONResponse(
			message="successfully retrieved user pending friend list",
			data=data if data != [] else "empty"
		)


ACCEPTED_STATUS = ['accepted', 'rejected']

@api_view(('PUT', )) # {"creator": int, "receiver": int, "status": str("accepted" | "rejected")}
@login_required
def friend_validate(request, user:User=None):
	user = request.user
	# data = request.body.decode("utf-8")
	data = json.loads(request.body.decode("utf-8"))

	status = data.get("status", "pending")
	if not status in ACCEPTED_STATUS:
		return JSONResponse(error_code=400, message=f"invalid friend status code <{status}>")

	creator = get_player(data.get("creator"))
	printi(f"creator: {creator.player_id}")
	if not creator:
		return JSONResponse(error_code=400, message="Bad request: invalid user id")
	
	try:
		fr = FriendRequest.objects.get(creator=creator.player_id, receiver=user.id)
		printi(fr)
	except Exception as err:
		printe(f"Error updating friend request {(err)}")
		return JSONResponse(error_code=400, message=err)

	printi(status)
	fr.status = status
	if fr.status == "rejected": # delete entry from db
		fr.delete()
		return JSONResponse(error_code=200, message="Friendship rejected successfully")

	# accepted
	player = get_player(user.id)
	add_id_to_friend_list(player, creator.player_id)
	add_id_to_friend_list(creator, user.id)
	data = PlayerSerializer(instance=player, many=False).data
	fr.delete()
	return JSONResponse(
		error_code=201,
		message="Friend added successfully",
		data=data
		)

@api_view(('PUT', ))
@login_required
def remove_friend(request):
	user = request.user
	data = json.loads(request.body.decode("utf-8"))
	friend_id = data.get("friend_id", -1)

	if friend_id == -1:
		return JSONResponse(
			error_code=200,
			message="No friend specified",
			data = data
			)

	get_player(user.id).remove_friend(friend_id)
	get_player(friend_id).remove_friend(user.id)

	return JSONResponse(
			error_code = 200,
			message=f"Remove friend <{friend_id}>",
			data = PlayerSerializer(instance=get_player(user.id), many=False).data
		)

@api_view(('DELETE', ))
@login_required
def delete_player(request):
	user = request.user

	for player in Player.objects.all():
		player.remove_friend(user.id)

	try:
		Token.objects.get(user=user).delete()
		Player.objects.get(player_id=user.id).delete()
		if user.oauth_42:
			User42.objects.get(player_id=user.id).delete()
		user.delete()
	except Exception as e:
		printe(f"Error while deleting user: {e}")
		return JSONResponse(
				error_code = 400,
				message=f"Cannot delete player, {e}",
			)

	return JSONResponse(
			error_code = 200,
			message=f"Deleted player",
		)
