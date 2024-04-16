
from django.urls import path#, include
from .views import GamesHistoryApiView, TournamentApiView, get_tournaments_played

urlpatterns = [
	
]

api_urls = [
	path('history/', get_tournaments_played),
	path('history/<int:player_id>', get_tournaments_played),


	path('match_history/', GamesHistoryApiView.as_view()),
    path('match_history/<int:player_id>', GamesHistoryApiView.as_view()),
	path('', TournamentApiView.as_view()),
	path('<int:tournament_id>', TournamentApiView.as_view()),
]
