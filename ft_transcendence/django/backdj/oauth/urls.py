from django.urls import path
from .views import oauth42_authentication
# from django.views.decorators.csrf import csrf_exempt

# localhost:8000/users/
urlpatterns = [
    path('', oauth42_authentication),
]