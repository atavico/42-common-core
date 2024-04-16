
from .enums import ERR_CODES
from rest_framework.response import Response
from django.contrib.sessions.backends.db import SessionStore

class JSONResponse(Response):
	content_type:str = 'application/json'
	data:dict = {}
	status = ERR_CODES[200]

	def __init__(self, data:dict=None, message:str=None, error:bool=False, error_code:int=200, token=None, cookie_gen=False, *args, **kwargs):
		self.data = {}
		self.status = ERR_CODES[error_code]
		self.data['error'] = error if error_code < 300 else True
		if message:	self.data['message'] = message
		if data: self.data['data'] = data
		if token != None: self.data['token'] = token
		super(Response, self).__init__(self.data, *args, status=self.status, **kwargs)
		if cookie_gen:
			session = SessionStore()
			session.save()
			self.set_cookie(
				'sessionid', session.session_key,
				secure=True, httponly=True
			)