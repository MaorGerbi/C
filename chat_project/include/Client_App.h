#ifndef __CLIENT_APP_H__
#define __CLIENT_APP_H__

typedef struct Client Client;

typedef enum Client_Status
{
	CLIENT_APP_SUCCESS,
	CLIENT_APP_ALLOC_FAIL,
	CLIENT_APP_CONNECT_FAIL,
	CLIENT_APP_NOT_INIT
	
}Client_Status;

/*
description - create new Client
input       - none
output      - pointer to new struct / NULL for ERR
error       - NULL  */
Client* Client_Create();

/*
description - Run the client App
input       - pointer to client
output      - CLIENT_APP_SUCCESS, ERR
error       - CLIENT_APP_ALLOC_FAIL, CLIENT_APP_CONNECT_FAIL, CLIENT_APP_NOT_INIT  */
Client_Status Client_Run(Client* _client);

/*
description - Destroy client (create by Creat_Client)
input       - client to distroy
output      - none
error       - none 
 */
void Client_Destroy(Client** _client);


#endif /* __CLIENT_APP_H__ */
