"""
ASGI config for backdj project.

It exposes the ASGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/4.2/howto/deployment/asgi/
"""

import os, django
from django.core.asgi import get_asgi_application
from django.conf import settings
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'backdj.settings')
settings.APP = "Daphne"
django.setup()

from channels.auth import AuthMiddlewareStack
from channels.routing import ProtocolTypeRouter, URLRouter
# from django.core.asgi import get_asgi_application
# from activity.routing import websocket_urlpatterns
from .routing import websocket_urlpatterns

#django.setup()

django_asgi_app = get_asgi_application()

application = ProtocolTypeRouter({
    "websocket": AuthMiddlewareStack(URLRouter(websocket_urlpatterns)),
})
