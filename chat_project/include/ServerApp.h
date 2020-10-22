#ifndef __SERVER_APP_H__
#define __SERVER_APP_H__

#include "ServerNet.h"
#include "UserManager.h"
#include "Protocol.h"
#include "GroupM.h"

typedef struct ServerApp ServerApp;

typedef enum ERR_SERVER
{
	ERR_S_SUCCESS = 0,
	ERR_S_UNINITIALIZED,
	ERR_S_ALLOCATION_FAILED,
	ERR_S_GENERAL

}ERR_SERVER;

/*description - this function create the serverApp and return it.
input - none.
output - a pointer to the allocated ServerApp that was created.
ERROR - NULL(in case the allocation failed).*/
ServerApp* ServertApp_Create();

/*description - this function run the server that let you connect with ather clients and to open chat with them.
input - _ServerApp(the struct the was created by ServertApp_Create).
output - ERR_S_SUCCESS, ERR_S_UNINITIALIZED.
ERROR - ERR_S_SUCCESS(the server run with no problems).
	ERR_S_UNINITIALIZED(the _ServerApp is not initilized).
*/
ERR_SERVER ServerApp_Run(ServerApp* _ServerApp);

/*description - this function free the struct that was created by ServertApp_Create.
input - _ServerApp(the struct the was created by ServertApp_Create).
output - none.
ERROR - none. */
void ServerApp_Destory(ServerApp** _ServerApp);


#endif /* __SERVER_APP_H__ */
