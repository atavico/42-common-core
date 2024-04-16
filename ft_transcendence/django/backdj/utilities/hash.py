import bcrypt

def hash_pwd(pwd:str=""):

	salt = bcrypt.gensalt()
	pbytes = pwd.encode('utf-8')
	hashed_pwd:str = bcrypt.hashpw(pbytes, salt)
	return hashed_pwd
