
# from .response import JSONResponse
# from utilities.logger import printe
# from utilities.utils import *
# from rest_framework.decorators import api_view, renderer_classes
# from rest_framework.renderers import JSONRenderer, TemplateHTMLRenderer

# def login_required_session(function):
# 	def wrapper(request, *args, **kw):
# 		user=request.user  
# 		if not (user.id and request.session.get('code_success')):
# 			printe("User not logged in, or not in an active session")
# 			return JSONResponse(
# 				error_code=401,
# 				message="User is not logged in"
# 			)
# 		else:
# 			return function(request, *args, **kw)
# 	return wrapper

