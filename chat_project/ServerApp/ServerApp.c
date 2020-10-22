#include <stdio.h> /*printf*/
#include <stdlib.h>/*malloc,free*/
#include <string.h>/*strlen*/
#include "ServerApp.h"
#include <assert.h>

struct ServerApp
{
	UserM* m_userM;
	ServerNet* m_serverNet;
	GroupM* m_groupM;
};

#define MAX_STRING_SIZE 50
#define BUFFER_SIZE 4096
#define NUM_OF_GROUPS 100

void NewClientFunc(int _client_sock, void* _context);
void CloseClientFunc(int _client_sock, void* _context);
void FailFunc(int _client_sock, void* _context);
void GotMessageFunc(int _client_sock, void* _inMsg, void*_context);
static void HandleRegisterRequest(ServerApp* _serverApp,void* _inMsg, int _client_sock);
static void HandleLogInRequest(ServerApp* _serverApp,void* _inMsg, int _client_sock);
static void HandleOpenGroupRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock);
static void HandleLogOutRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock);
static void HandleGroupNameRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock);
static void HandleGroupAddRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock);
static void HandleLeaveGroupRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock);
static void DestroyAllGroups(GroupM *_groupM,char* _groupString);


ServerApp* ServertApp_Create(char _fileUsers[], size_t _capacity)
{
	ServerApp* serverApp = (ServerApp*)malloc(sizeof(ServerApp));
	if(NULL == serverApp)
	{
		return NULL;
	}
	
	serverApp -> m_serverNet = ServerNet_Create(NewClientFunc, GotMessageFunc, CloseClientFunc , FailFunc);
	if(NULL == serverApp -> m_serverNet)
	{
		free(serverApp);
		return NULL;
	}

	serverApp -> m_userM = UserM_Create(_fileUsers, _capacity);
	if(NULL == serverApp -> m_userM)
	{
		ServerNet_Destroy (&(serverApp -> m_serverNet));
		free(serverApp);
		return NULL;
	}

	serverApp -> m_groupM = GroupM_Create (NUM_OF_GROUPS);
	if(NULL == serverApp -> m_groupM)
	{
		GroupM_Destroy(&(serverApp -> m_groupM));
		ServerNet_Destroy (&(serverApp -> m_serverNet));
		free(serverApp);
		return NULL;
	}
		
	return serverApp;
}

ERR_SERVER ServerApp_Run(ServerApp* _ServerApp)
{
	ServerN_Result status;

	status = ServerNet_Run(_ServerApp -> m_serverNet, _ServerApp);
	switch(status)
	{
		case SERVER_SUCCESS:
			return ERR_S_SUCCESS;

		case SERVER_ALLOCATION_ERROR:
			return ERR_S_ALLOCATION_FAILED;

		default:
			return ERR_S_GENERAL;
	}
}

void ServerApp_Destory(ServerApp** _serverApp)
{
	if(NULL != _serverApp && NULL != *_serverApp)
	{
		GroupM_Destroy(&((*_serverApp) -> m_groupM));
		UserM_Destroy(&((*_serverApp) -> m_userM));
		ServerNet_Destroy (&((*_serverApp) -> m_serverNet));
		free(*_serverApp);
		*_serverApp = NULL;
	}

}

void NewClientFunc(int _client_sock, void* _context)
{
	char message[] = "welcome to the serever of asaf,maor and ziv\n";
	int msgSize = strlen(message);
	ServerNet_Send (_client_sock, message, msgSize);
}

 void CloseClientFunc(int _client_sock, void* _context)
{
	printf("one of the client has been disconnected\n");
}

void FailFunc(int _client_sock, void* _context)
{
	char message[] = "there was a problem with the server,sorry about this\n";
	int msgSize = strlen(message);
	ServerNet_Send (_client_sock, message, msgSize);
}

void GotMessageFunc(int _client_sock, void* _inMsg, void*_context)
{
	ServerApp* serverApp = (ServerApp*)_context;
	char tag;

	Protocol_CheckTag((char*)_inMsg, &tag);
	switch(tag)
	{
		case REGISTER_REQUEST:
			HandleRegisterRequest(serverApp, _inMsg, _client_sock);
			break;
	
		case LOG_IN_REQUEST:
			HandleLogInRequest(serverApp, _inMsg, _client_sock);
			break;
	
		case OPEN_GROUP_REQUEST:
			HandleOpenGroupRequest(serverApp, _inMsg, _client_sock);
			break;

		case LOG_OUT_REQUEST:
			HandleLogOutRequest(serverApp, _inMsg, _client_sock);
			break;

		case GROUPS_NAMES_REQUEST:
			HandleGroupNameRequest(serverApp, _inMsg, _client_sock);
			break;

		case JOIN_GROUP_REQUEST:
			HandleGroupAddRequest(serverApp, _inMsg, _client_sock);
			break;

		case LEAVE_GROUP_REQUEST:
			HandleLeaveGroupRequest(serverApp, _inMsg, _client_sock);
			break;		

		default:
			break;
	}
}

static void HandleLogOutRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock)
{
	Logout_Request pack_recived;
	Register_Response pack_to_send;
	char buffer[BUFFER_SIZE];
	size_t msgSize;

	Protocol_Unpack((char*)_inMsg, &pack_recived);
	if(ERR_M_SUCCESS == UserM_Disconnect(_serverApp -> m_userM, pack_recived.m_name))
	{
		pack_to_send.m_status = 1;
		DestroyAllGroups(_serverApp -> m_groupM, pack_recived.m_groupsNames);
	}
	else
	{
		pack_to_send.m_status = 0;
	}

	pack_to_send.m_tag = LOG_OUT_RESPONSE;
	Protocol_Pack(&pack_to_send, buffer, &msgSize);
	ServerNet_Send(_client_sock, buffer, msgSize);

}

static void DestroyAllGroups(GroupM *_groupM,char* _groupString)
{
	int i = 0, numofStr = _groupString[0];
	int startIndex = 2;
	char str[MAX_STRING_SIZE];
	GroupM_Result status;
	
	while(i < numofStr)
	{
		strcpy(str, &_groupString[startIndex]);
		status = GroupM_RemoveUser (_groupM, str);

		assert(status == GROUPM_SUCCESS);
	
		startIndex += strlen(str) + 1;

		++i;
	}

}

static void HandleLeaveGroupRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock)
{
	Group_Request pack_recived;
	Leave_Group_Response pack_to_send;
	char buffer[BUFFER_SIZE];
	size_t msgSize;

	Protocol_Unpack((char*)_inMsg, &pack_recived);

	if(GROUPM_SUCCESS == GroupM_RemoveUser(_serverApp -> m_groupM, pack_recived.m_groupName))
	{
		pack_to_send.m_status = 1;	
	}
	else
	{
		pack_to_send.m_status = 0;
	}

	pack_to_send.m_tag = LEAVE_GROUP_RESPONSE;
	strcpy(pack_to_send.m_groupName, pack_recived.m_groupName);

	Protocol_Pack(&pack_to_send, buffer, &msgSize);
	ServerNet_Send(_client_sock, buffer, msgSize);
}

static void HandleGroupAddRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock)
{
	Group_Request pack_recived;
	Group_Response pack_to_send;
	char buffer[BUFFER_SIZE];
	size_t msgSize;

	Protocol_Unpack((char*)_inMsg, &pack_recived);
	if(GROUPM_SUCCESS == GroupM_AddUser(_serverApp -> m_groupM, pack_recived.m_groupName, pack_to_send.m_ipAddress, pack_to_send.m_port))
	{
		pack_to_send.m_status = 1;	
	}
	else
	{
		pack_to_send.m_status = 0;
	}

	strcpy(pack_to_send.m_groupName, pack_recived.m_groupName);

	pack_to_send.m_tag = JOIN_GROUP_RESPONSE;

	Protocol_Pack(&pack_to_send, buffer, &msgSize);
	ServerNet_Send(_client_sock, buffer, msgSize);
}

static void HandleGroupNameRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock)
{
	Groups_Names_Request pack_recived;
	Group_Names_Response pack_to_send;
	char buffer[BUFFER_SIZE];
	size_t msgSize;

	Protocol_Unpack((char*)_inMsg, &pack_recived);
	GroupM_GetAllGroups(_serverApp -> m_groupM,pack_to_send.m_allGroups);
	pack_to_send.m_tag = GROUPS_NAMES_RESPONSE;

	Protocol_Pack(&pack_to_send, buffer, &msgSize);
	ServerNet_Send(_client_sock, buffer, msgSize);
}

static void HandleOpenGroupRequest(ServerApp* _serverApp,void* _inMsg,int _client_sock)
{
	Group_Request pack_recived;
	Group_Response pack_to_send;
	char buffer[BUFFER_SIZE];
	size_t msgSize;
	GroupM_Result status;

	Protocol_Unpack((char*)_inMsg, &pack_recived);

	status = GroupM_OpenGroup(_serverApp -> m_groupM, pack_recived.m_groupName, pack_to_send.m_ipAddress, pack_to_send.m_port);
	switch(status)
	{
		case GROUPM_SUCCESS:
			pack_to_send.m_status = 1;
			break;
		default:
			pack_to_send.m_status = 0;
	}
	pack_to_send.m_tag = OPEN_GROUP_RESPONSE;
	strcpy(pack_to_send.m_groupName, pack_recived.m_groupName);
	Protocol_Pack(&pack_to_send, buffer, &msgSize);
	ServerNet_Send(_client_sock, buffer, msgSize);
}

static void HandleRegisterRequest(ServerApp* _serverApp,void* _inMsg, int _client_sock)
{
	Register_Request pack_recived;
	Register_Response pack_to_send;
	char buffer[BUFFER_SIZE];
	size_t msgSize;
	ERR_Manager status;

	Protocol_Unpack((char*)_inMsg, &pack_recived);

	status = UserM_Register(_serverApp -> m_userM, pack_recived.m_name, pack_recived.m_password);
	switch(status)
	{
		case ERR_M_SUCCESS:
			pack_to_send.m_status = 1;
			break;
		default:
			pack_to_send.m_status = 0;
	}
	pack_to_send.m_tag = REGISTER_RESPONSE;
	Protocol_Pack(&pack_to_send, buffer, &msgSize);
	ServerNet_Send(_client_sock, buffer, msgSize);
}


static void HandleLogInRequest(ServerApp* _serverApp,void* _inMsg, int _client_sock)
{
	Register_Request pack_recived;
	Register_Response pack_to_send;
	char buffer[BUFFER_SIZE];
	size_t msgSize;
	ERR_Manager status;

	Protocol_Unpack((char*)_inMsg, &pack_recived);
	status = UserM_Login(_serverApp -> m_userM, pack_recived.m_name, pack_recived.m_password);
	switch(status)
	{
		case ERR_M_SUCCESS:
			pack_to_send.m_status = 1;
			break;
		default:
			pack_to_send.m_status = 0;
	}
	pack_to_send.m_tag = LOG_IN_RESPONSE;
	Protocol_Pack(&pack_to_send, buffer, &msgSize);
	ServerNet_Send(_client_sock, buffer, msgSize);	
}

