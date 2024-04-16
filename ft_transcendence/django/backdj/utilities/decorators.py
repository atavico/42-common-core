
from .response import JSONResponse
from .logger import printe, printd, printw
from .utils import *
from rest_framework.decorators import api_view, renderer_classes
from rest_framework.renderers import JSONRenderer, TemplateHTMLRenderer

@renderer_classes((JSONRenderer, TemplateHTMLRenderer))
def login_required(func, *args, **kwargs):
	def wrapper(request, *args, **kwargs):
		user = get_user_by_tkn(request)
		if not user:
			return JSONResponse(error_code=401, message="Unauthorized action, relog")
		request.user = user
		return func(request, *args, **kwargs)
	return wrapper

@renderer_classes((JSONRenderer, TemplateHTMLRenderer))
def login_required_in_class(func):
	def wrapper(self, request, **kwargs):
		user = get_user_by_tkn(request)
		if not user:
			return JSONResponse(error_code=401, message="Unauthorized action, relog")
		request.user = user
		return func(self, request, **kwargs)
	return wrapper

def debug(func, *args, **kwargs):
	def wrapper(func, *args, **kwargs):
		try:
			return func(*args, **kwargs)
		except Exception as e:
			printe(f"Mega exception in <{func.__name__}> -> {e}")
			exit(0)
	return wrapper