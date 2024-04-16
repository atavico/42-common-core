from django.urls import path
from channels.routing import URLRouter
from activity.routing import websocket_urlpatterns as a_routing
from tournaments.routing import websocket_urlpatterns as t_routing

websocket_urlpatterns = [
    path("ws/active_users/", URLRouter(a_routing)),
    path("ws/tournaments/", URLRouter(t_routing)),
]