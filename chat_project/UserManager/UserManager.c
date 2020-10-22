#include <string.h>/*strcmp,strlen,strcpy*/
#include <stdlib.h>/*malloc,free*/
#include <stdio.h> /*files*/
#include "UserManager.h"
#include "HashMap.h"


#define MAX_NAME_SIZE 30
#define MAX_PASSWORD_SIZE 30


struct UserM
{
	char* m_usersFile;/*file contain line of name,line of password,line of name,line of password...*/
	HashMap* m_hash;/*have User inside, the key is name*/
};

typedef struct User
{
	char m_name[MAX_NAME_SIZE];
	char m_password[MAX_PASSWORD_SIZE];
	int m_isLogIn;

}User;


size_t HashFuncName(const void* _key);
int PasswordEqualityFunc(const void* _savedUser, const void* _password);
void UserDestroy(void* _user);
static User* UserCreate(char* _name, char* _password);
static int StringToNumber(char* _str);
int PrintfAction(const void* _key, void* _value, void* _context);/*for test*/

UserM* UserM_Create(char _fileUsers[], size_t _capacity)
{
	FILE* file;
	UserM* userM;
	HashMap* hashUsers;/*i can insert it directly to the hash*/
	User* user;
	int len;
	
	if(NULL == _fileUsers || 0 == _capacity)
	{
		return NULL;
	}

	userM = (UserM*)malloc(sizeof(UserM));
	if(NULL == userM)
	{
		return NULL;
	}

	file = fopen(_fileUsers, "r");
	if(NULL == file)
	{
		free(userM);
		return NULL;
	}

	hashUsers = HashMap_Create(_capacity, HashFuncName, PasswordEqualityFunc);
	if(NULL == hashUsers)
	{
		free(userM);
		fclose(file);
		return NULL;	
	}
	
	while(!feof(file))/*TODO- ruing one more time then it should*/
	{
		user = (User*)malloc(sizeof(User));
		if(NULL == user)
		{
			free(userM);
			fclose(file);
			HashMap_Destroy(&hashUsers, NULL, UserDestroy);
			return NULL;	
		}

		if(!fgets(user -> m_name, MAX_NAME_SIZE, file))
		{
			free(user);
			break;
		}
		len = strlen(user -> m_name);
		user -> m_name[len - 1] = '\0';
		
		if(!fgets(user -> m_password, MAX_PASSWORD_SIZE, file))
		{
			free(user);
			break;
		}
		len = strlen(user -> m_password);
		user -> m_password[len - 1] = '\0';
		user -> m_isLogIn = 0;
		

		HashMap_Insert(hashUsers, user -> m_name, user);	
	}

	userM -> m_usersFile = (char*)malloc(strlen(_fileUsers) * sizeof(char));
	if(NULL == userM -> m_usersFile)
	{
			free(userM);
			fclose(file);
			HashMap_Destroy(&hashUsers, NULL, UserDestroy);
			return NULL;	
	}

	strcpy(userM -> m_usersFile, _fileUsers);

	userM -> m_hash = hashUsers;

	fclose(file);

	return userM;
}

ERR_Manager UserM_Disconnect(UserM* _userM, char* _name)
{
	Map_Result status;
	void* user;

	if(NULL == _userM || NULL == _name)
	{
		return ERR_M_UNINITIALIZED;
	}
	status = HashMap_Find(_userM -> m_hash, _name, &user);
	if(MAP_SUCCESS == status)
	{
		((User*)user) -> m_isLogIn = 0;	
		return ERR_M_SUCCESS;
	}
	else
	{
		switch(status)
		{
			case MAP_KEY_NOT_FOUND_ERROR:
				return ERR_M_USER_NOT_FOUND;

			default:
				return ERR_M_GENERAL;
		}
	}

	return ERR_M_GENERAL;	
}

ERR_Manager UserM_Register(UserM* _userM, char* _name, char* _password)
{
	User* user;
	FILE* file;
	Map_Result status;

	if(NULL == _userM || NULL == _name || NULL == _password)
	{
		return ERR_M_UNINITIALIZED;
	}

	user = UserCreate(_name, _password);
	if(NULL == user)
	{
		return ERR_M_ALLOCATION_FAILED;
	}

	status = HashMap_Insert(_userM -> m_hash, user->m_name, user);
	
	if(MAP_SUCCESS == status)
	{
		file = fopen(_userM -> m_usersFile, "a");
		if(NULL == file)
		{
			return ERR_M_FILE_NOT_OPEN;
		}
		
		fprintf(file,"%s\n", _name);
		fprintf(file,"%s\n", _password);
		fclose(file);
	}
	else
	{
		free(user);

		switch(status)
		{
			case MAP_KEY_DUPLICATE_ERROR:
				return ERR_M_USER_ALLREADY_EXISTS;

			case MAP_ALLOCATION_ERROR:
				return ERR_M_ALLOCATION_FAILED;

			case MAP_OVERFLOW_ERROR:
				return ERR_M_FILE_FULL;

			default:
				return ERR_M_GENERAL;
		}
	}

	return ERR_M_SUCCESS;	
}

ERR_Manager UserM_Login(UserM* _userM, char* _name, char* _password)
{
	Map_Result status;
	void* user;

	if(NULL == _userM || NULL == _name || NULL == _password)
	{
		return ERR_M_UNINITIALIZED;
	}

	status = HashMap_Find(_userM -> m_hash, _name, &user);

	if(MAP_SUCCESS == status)
	{
		if(1 == ((User*)user) -> m_isLogIn)
		{
			return ERR_M_USER_ALLREDY_LOG_IN;
		}

		if(!strcmp(((User*)user) -> m_password, _password))
		{
			((User*)user) -> m_isLogIn = 1;	
			return ERR_M_SUCCESS;
		}
		else
		{
			return ERR_M_WRONG_PASSWORD;
		}

	}
	else
	{
		switch(status)
		{
			case MAP_KEY_NOT_FOUND_ERROR:
				return ERR_M_USER_NOT_FOUND;

			default:
				return ERR_M_GENERAL;
		}
	}

	return ERR_M_GENERAL;	
}


static User* UserCreate(char* _name, char* _password)
{
	User* user = (User*)malloc(sizeof(User));
	if(NULL == user)
	{
		return NULL;	
	}
	
	strcpy(user -> m_name, _name);
	strcpy(user -> m_password, _password);
	user -> m_isLogIn = 0;

	return user;
}

void UserM_Destroy(UserM** _userM)
{
	if(NULL != _userM && NULL != *_userM)
	{
		free((*_userM) -> m_usersFile);
		HashMap_Destroy(&((*_userM) -> m_hash), NULL, UserDestroy);
		free(*_userM);
		*_userM = NULL;
	}
}

void UserDestroy(void* _user)
{
	free((User*)_user);
}

size_t HashFuncName(const void* _key)
{	
	int returnVal = StringToNumber((char*)_key);
	return returnVal;
}

static int StringToNumber(char* _str)
{
	int count = 0;
	int i = 0;

	while('\0' != _str[i])
	{
		count += (int)_str[i];
		++i;
	}

	return count;
}

int PasswordEqualityFunc(const void* _savedUser, const void* _name)
{
	char* savedName = (char*)_savedUser;

	return !strcmp(savedName, (char*)_name);
}

void PrintUsers(UserM* _userM)
{
	HashMap_ForEach(_userM -> m_hash, PrintfAction, NULL);
}


int PrintfAction(const void* _key, void* _value, void* _context)
{
	printf("the key is: %s\n", (char*)_key);
	printf("the value name is: %s\n", ((User*)_value) -> m_name); 
	printf("the value password is: %s\n", ((User*)_value) -> m_password); 
	return 1;
}








