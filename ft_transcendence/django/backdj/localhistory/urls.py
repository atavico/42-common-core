
from django.urls import path
from .views import LocalMatchesHistoryApiView, LocalTournamentsHistoryApiView

urlpatterns = [
	
]

api_urls = [
	path('matches/', LocalMatchesHistoryApiView.as_view()),
	path('matches/<int:player_id>', LocalMatchesHistoryApiView.as_view()),

	path('tournaments/', LocalTournamentsHistoryApiView.as_view()),
	path('tournaments/<int:player_id>', LocalTournamentsHistoryApiView.as_view()),
	]