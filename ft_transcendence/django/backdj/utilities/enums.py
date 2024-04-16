
from rest_framework import status

ERR_CODES = {
	200: status.HTTP_200_OK,
	201: status.HTTP_201_CREATED,
	204: status.HTTP_204_NO_CONTENT,
	
	400: status.HTTP_400_BAD_REQUEST, 
	401: status.HTTP_401_UNAUTHORIZED, 
	403: status.HTTP_403_FORBIDDEN,
	
	500: status.HTTP_500_INTERNAL_SERVER_ERROR
}

ANIMALS = ['cat', 'dog', 'cow', 'pig', 'ant', 'bat', 'bee', 'fox', 'rat', 'hen', 'owl', 'elk', 'ape', 'boa', 'koi']

PERMITTED_LANGUAGES = [
	"en", "it", "pl",
]
