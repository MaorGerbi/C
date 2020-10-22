#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

typedef struct UserM UserM;

typedef enum ERR_Manager
{
	ERR_M_SUCCESS = 0,
	ERR_M_USER_NOT_FOUND,
	ERR_M_ALLOCATION_FAILED,
	ERR_M_UNINITIALIZED,
	ERR_M_USER_ALLREADY_EXISTS,
	ERR_M_USER_ALLREDY_LOG_IN,
	ERR_M_USER_NOT_LOG_IN,
	ERR_M_FILE_NOT_OPEN,
	ERR_M_FILE_FULL,
	ERR_M_WRONG_PASSWORD,
	ERR_M_GENERAL
	
}ERR_Manager;


/*description - this function get a file of all the users and create the UserM struct.
input - _users(a file that contain all the user and there passwords).
	_capacity(the max number of users(name and passowrd that can be registerd).
output- a pointer the the UserM struct that was created.
ERROR - NULL(if allocation failed).*/
UserM* UserM_Create(char _fileUsers[], size_t _capacity);

/*description - this function free the _userM struct that was created by UserM_Create.
input - _userM(a struct that was created by UserM_Create).
output - none.
ERROR - none.*/
void UserM_Destroy(UserM** _userM);

/*description - this function get a user name and password and if it not allready registerd it register him.
input - _userM(a struct that was created by UserM_Create).
	_name(the name of the user you want to register).
	_password(the password of the user).
output -  ERR_M_SUCCESS, ERR_M_UNINITIALIZED, ERR_M_USER_ALLREADY_EXISTS
ERROR - ERR_M_SUCCESS(no problems).
	ERR_M_UNINITIALIZED(_userM, _name or _password is not initilized)
	ERR_M_USER_ALLREDY_EXISTS(this user allready registered).*/
ERR_Manager UserM_Register(UserM* _userM, char* _name, char* _password);

/*description - this function get a user name a password and check if the user name and passaword is exists.
input - _userM(a struct that was created by UserM_Create).
	_name(the name of the user you want to log with it).
	_password(the password of the user).
output - ERR_M_SUCCESS, ERR_M_USER_NOT_FOUND, ERR_M_UNINITIALIZED, ERR_M_USER_ALLREDY_LOG_IN, 			ERR_M_WRONG_PASSWORD.
ERROR - ERR_M_SUCCESS(you can log in the user).
	ERR_M_USER_NOT_FOUND(the user isn't register,try again or register).
	ERR_M_UNINITIALIZED(_userM, _name or _password is not initilized).
	ERR_M_USER_ALLREDY_LOG_IN(the user you entered allredy log in).
	ERR_M_WRONG_PASSWORD(the user is exsits but the password is wrong).*/
ERR_Manager UserM_Login(UserM* _userM, char* _name, char* _password);

/*description - this function check if the _name is registered right now and if yes disconnect it.
input - _userM(a struct that was created by UserM_Create).
	_name(the name you want to discconect).
output - ERR_M_SUCCESS, ERR_M_USER_NOT_FOUND, ERR_M_UNINITIALIZED, ERR_M_USER_NOT_LOG_IN.
ERROR - ERR_M_SUCCESS(the user was found and was disconnected).
	ERR_M_USER_NOT_FOUND(the user isn't in the system and there for didn't found).
	ERR_M_UNINITIALIZED(_userM, _name or _password is not initilized).
	ERR_M_USER_NOT_LOG_IN(the user isn't log in and there for couldn't be disconnected).
*/
ERR_Manager UserM_Disconnect(UserM* _userM, char* _name);


/*for debugging*/
void PrintUsers(UserM* _userM);


#endif /* __USER_MANAGER_H__ */
