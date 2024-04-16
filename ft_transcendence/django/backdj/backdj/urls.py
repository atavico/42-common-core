"""
URL configuration for backdj project.

The `urlpatterns` list routes URLs to views. For more information please see:
	https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
	1. Add an import:  from my_app import views
	2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
	1. Add an import:  from other_app.views import Home
	2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
	1. Import the include() function: from django.urls import include, path
	2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import include, path
from . import views
from users.urls import urlpatterns as users_urls
from users.urls import api_urls as users_api_urls
from localhistory.urls import api_urls as history_api_urls
from oauth import urls as oauth_urls

from tournaments.urls import api_urls as t_api_urls, urlpatterns as t_urls

from django.conf.urls.static import static
from django.conf import settings

# https://localhost:8000/
urlpatterns = [
	path('admin/', admin.site.urls),
	path('test/', views.send_some_data),

	path('api-auth/', include('rest_framework.urls')),

	path('users/', include(users_urls)),
	path('api/users/', include(users_api_urls)),

	path('tournanments/', include(t_urls)),
    path('api/tournaments/', include(t_api_urls)),
	
	path('oauth/', include(oauth_urls)),
    
	path('api/blockchain/', include('blockchain.urls')),

	path('api/local_history/', include(history_api_urls)),
]

urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)