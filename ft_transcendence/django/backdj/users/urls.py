
from django.urls import path#, include

from .views import PlayerApiView, LoginView
from .views import sign_up, player_names, user_avatar_update, get_user_by_token, in_game
from .views import add_friend_request, get_friend_requests, friend_validate, get_pending_friend
from .views import remove_friend, delete_player

# users/...
urlpatterns = [
	path('register/', sign_up),
	path('login/', LoginView.as_view()),
	path('session/', get_user_by_token),
]

# api/users/...
api_urls = [
	path('player/', PlayerApiView.as_view()),
	path('player/<int:player_id>', PlayerApiView.as_view()),

	path('user_ingame/', in_game),
	path('avatar_upload/', user_avatar_update),
	path('player_names/', player_names),

	path('add_friend/', add_friend_request),
	path('friend_validate/', friend_validate),
	path('get_friend_requests/', get_friend_requests),
	path('get_pending_friends/', get_pending_friend),

	path('remove_friend/', remove_friend),
	path('player_delete/', delete_player),
]
