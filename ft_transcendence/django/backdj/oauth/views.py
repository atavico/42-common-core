
import requests, base64

# from django.shortcuts import render

from django.contrib.auth import login

from rest_framework.decorators import api_view, renderer_classes
from rest_framework.renderers import JSONRenderer, TemplateHTMLRenderer
from utilities.response import JSONResponse
from rest_framework.response import Response
from rest_framework import status
from users.models import User, User42, Player
from utilities.utils import get_player_info
from utilities.logger import log, printi, printd, printe
from django.conf import settings

TOKEN_URL = "https://api.intra.42.fr/oauth/token"
USER_API_URL = "https://api.intra.42.fr/v2/me"
REDIRECT_URI = f"https://{settings.IP_ADDR}:4343/"

import os
from hvac import Client

def get_api_credentials():
	vault_client = Client(url='https://vault:8200', verify=False)
	APPROLE_ROLE = os.environ.get('APPROLE_ROLE')
	APPROLE_SECRET = os.environ.get('APPROLE_SECRET')
	response = vault_client.auth.approle.login(
		role_id=APPROLE_ROLE,
		secret_id=APPROLE_SECRET,
	)

	response = vault_client.read('secret/django/oauth_api')

	if response and 'data' in response:
		credentials_data = response['data']
		if 'client_id' in credentials_data and 'client_secret' in credentials_data:
			return credentials_data
		else:
			raise Exception("Missing expected keys in the credentials data")
	else:
		raise Exception("Failed to retrieve oauth_api credentials from Vault")
	
api_credentials = get_api_credentials()

def code_to_access_token(code:str, redirect_uri) -> dict:
	payload = {

		'client_id' : api_credentials['client_id'],
		'client_secret': api_credentials['client_secret'],
		'code': code,
		'redirect_uri': redirect_uri,
		'grant_type': "authorization_code",
	}
	headers = {
		'Content-Type': 'application/x-www-form-urlencoded',
	}
	response = requests.post(TOKEN_URL, data=payload, headers=headers)
	if response.status_code == 200:
		return response.json()
	log.error(f"(OAuth 42) Cannot retrieve access token. Error code <{response.status_code}> <{response.detail}>")
	return None


def get_user_data(access_token:str, api_uri:str) -> dict:
	headers = {"Authorization": f'Bearer {access_token}'}
	response = requests.get(api_uri, headers=headers)
	return response


def get_base64_img(data, ) -> str:
	base = ""
	link = data.get("image").get("versions").get("medium")
	printi(link)
	response = requests.get(link)
	if response.status_code == 200:
		img = response.content
		base = "data:image/jpeg;base64,"
		base += base64.b64encode(img).decode('utf-8')
	else:
		printe(f"<{response.status_code}> error")
	return base


@api_view(('GET', 'POST', 'OPTIONS', ))
@renderer_classes((JSONRenderer, ))
def oauth42_authentication(request):
	if request.method == 'GET':
		code = request.GET.get('code', '')
	else:
		code = request.data['code']

	tokens_data = code_to_access_token(code, REDIRECT_URI)
	
	if tokens_data == None:
		return JSONResponse(
			error_code = 400, message = "cannot retrieve access token")
	log.info(tokens_data)
	
	# if actual time is > than time stored then refresh it
	user_data = get_user_data(tokens_data['access_token'], USER_API_URL)
	if user_data == None:
		return JSONResponse(
			error_code = 400, message = "cannot retrieve user data from 42 api")
	
	data = user_data.json()

	try:
		user42 = User42.objects.get(id42=data.get('id'))
		if user42.email != data.get('email', user42.email):
			user42.email = data.get('email', user42.email)
			user42.save()
	except User42.DoesNotExist:
		user42 = None
		
		user, created = User.objects.get_or_create(
			email=data.get('email'),
			defaults={
				'email': data.get('email'),
				'username': data.get('login'),
				'oauth_42': True,
				'password': "Passw@rdFi11&r"
			})
		if created: user.save()

		avatar = get_base64_img(data)

		player, created = Player.objects.get_or_create(
			player_id=user.id,
			defaults={
				"player_id": user.id,
				"username": user.username,
				"language": "en",
				"avatar": avatar,
			})
		if created: player.save()
		
		user42 = User42.create(
			user			= data,
			player_id		= user.id,
			tokens_data		= tokens_data,
			)
		user42.save()

		log.info("42User created successfully")
		data = get_player_info(p_instance=player, u_instance=user, tokenize=True)

		try:
			# login(request._request, user)
			login(request, user)
		except Exception as e:
			log.error("Login denied (?) -> ", e)

		return JSONResponse(
			data = data,
			message = f"OAuth signed up successfully",
			error_code = 201
		)
	except:
		log.error("Something else went wrong...")
		return JSONResponse(
			error_code = 403,
			message = "42User retrieved, but something went wrong gettin' Player stuff",
			data = user_data,
			)

	try:
		log.info(f"Loggin in 42user ({user42.id42} -> {user42.player_id}).. retrieving User and Player")
		user = User.objects.get(id=user42.player_id)
		if user.email != user42.email:
			user.email = user42.email
			user.save()
		
		player = Player.objects.get(player_id=user42.player_id)

		data = get_player_info(p_instance=player, u_instance=user, tokenize=True)

		# login(request._request, user)
		login(request, user)
		return JSONResponse(
			data = data,
			message = f"OAuth signed in successfully",
			error_code = 200
		)
	except Exception as e:
		log.error(f"What went wrong??? {e}")

	return JSONResponse(
		error_code = 403,
		message = "42User retrieved, but something went wrong gettin' Player stuff",
		data = user_data,
		)
