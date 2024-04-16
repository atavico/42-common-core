from django.urls import path#, include

from .views import get_tournament_from_blockchain

# users/...
urlpatterns = [
	path('tournament/', get_tournament_from_blockchain)
]