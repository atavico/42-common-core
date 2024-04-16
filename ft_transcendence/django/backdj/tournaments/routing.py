from django.urls import path

from . import consumers

websocket_urlpatterns = [
    path("<int:tournament_id>", consumers.TournamentConsumer.as_asgi()),
]
