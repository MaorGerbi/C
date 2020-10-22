#include <stdio.h>        /*print, scan*/ 
#include <stdlib.h>       /*calloc, free*/
#include <string.h>       /*strcpy*/
#include <sys/select.h>   /*select*/
#include "Protocol.h"
#include "Client_Net.h"
#include "Multicast.h"
#include "Client_App.h"
#include "GenDLL.h"
#include "list_itr.h"
#include "list_functions.h"
#include "UI_Manager.h"

#define PORT 9000
#define PACK_SIZE 4096
#define BUFFER_SIZE 4096
#define GROUP_NAME_SIZE 30

struct Client{
	char     m_name[20];
	ClientN* m_clientN;
	List*    m_listGroups;
	char     m_login;
};

typedef struct Stream
{
	char m_groupsNames[MAX_BUFFER_SIZE];
	size_t m_index;
}Stream;

static ClientN_Status Response_Handling(Client* _client);
static void Request_Handling(Client* _client);
static void GroupNames_Res(char* _buffer, Client* _client);
static int ClientApp_GroupsStream(void* _element, void* _context);

		         		 	
Client_Status Client_Run(Client* _client)
{  
    /*for Client_Net*/
	int port = PORT;
	char* ipDest = "127.0.0.1";
	ClientN_Status status;
	
    /*for select func*/
    int activity, serverSock, IO_sock = 0;
    fd_set readfd;
    FD_ZERO(&readfd);
    
	_client->m_clientN = ClientN_Create(ipDest,port);
	if(NULL == _client->m_clientN)
	{
		return CLIENT_APP_ALLOC_FAIL;
	}
	
	status = ClientN_Connect(_client->m_clientN);
	if(status != CLIENT_NET_SUCCESS)
	{
		return CLIENT_APP_CONNECT_FAIL;
	}
	serverSock = ClientN_GetSock(_client->m_clientN);

	UI_OpenScreen();
    UI_StartMenu();
	while(1)
	{
	    FD_SET(serverSock, &readfd);
	    FD_SET(IO_sock, &readfd);
	    
		activity = select(serverSock+1, &readfd, NULL, NULL, NULL);
		
		if(activity < 0 )
		{
			return 
			CLIENT_APP_CONNECT_FAIL;
		}
			
		if(FD_ISSET(serverSock, &readfd))
		{
			if(CLIENT_NET_SUCCESS != Response_Handling(_client))
			{
				break;
			}
	
		} 
				
		if(FD_ISSET(IO_sock, &readfd))
		{
			Request_Handling(_client);
		}
	}	
	return 1;	
}




Client* Client_Create()
{
	Client* client = NULL;
	
	client = (Client*)calloc(1,sizeof(Client));
	if(NULL == client)
	{
		return NULL;
	}
	
	return client;
}

void Client_Destroy(Client** _client)
{
	if(NULL == _client)
	{
		return;
	}
	
	free(*_client);
	*_client = NULL;
}
 
/*
Iner functions for Client_Run - Response_Handling
                                Request_Handling  
                                */

/* helper functions for Response_Handling */


static char* NameAlloc(size_t _size)
{
	char* name = (char*)malloc(sizeof(char) * _size); 

	return name;
}


int Predicate(void * _element, void* _context)
{
	return !strcmp((char*)_element, (char*)_context);
}


static void OpenGroup_Res(char* _buffer, Client *_client)
{
	Group_Response openGroupResponse;
	int port;
	char* groupName;
	Multicast_Result status = MULTICAST_GENERAL_ERR;
	 
	Protocol_Unpack(_buffer, (void*)&openGroupResponse);
	 
	port = atoi(openGroupResponse.m_port);
	if(openGroupResponse.m_status)
	{  
		groupName = NameAlloc(strlen(openGroupResponse.m_groupName) + 1);
		if(NULL == groupName)
		{
			printf("There is an allocation error\n");
			return;
		}

		strcpy(groupName, openGroupResponse.m_groupName);
			
		List_PushHead(_client -> m_listGroups, groupName);
			
		status = MulticastCreate(openGroupResponse.m_ipAddress, port, groupName, _client->m_name);
	}

		if(status == MULTICAST_SUCESS)
		{
	 		UI_OK();
	 		UI_GroupMenu();
		}
		else
		{
	 		UI_Err();
			if(List_IsEmpty(_client->m_listGroups))
			{
		    	UI_LoginMenu();
			}
			else
			{
		    	UI_GroupMenu();
			}
		}	
}



static void LeaveGroup_Res(char* _buffer,Client* _client)
{
	Leave_Group_Response leaveGroupResponse;
	
	Protocol_Unpack(_buffer, (void*)&leaveGroupResponse);
	
	if(leaveGroupResponse.m_status)
	{
		UI_OK();
	}
	else
	{
		UI_Err();
	}
	
	if(List_IsEmpty(_client->m_listGroups))
	{
		UI_LoginMenu();
	}
	else
	{
		UI_GroupMenu();
	}
}

static void GroupNames_Res(char* _buffer, Client* _client)
{
    Group_Request groupRequest;
	Group_Names_Response groupNamesResponse;
	int i,j = 2;
	char* groups, pack[PACK_SIZE];
	size_t size;
	ListItr begin;
	ListItr end;

	Protocol_Unpack(_buffer, (void*)&groupNamesResponse);
	groups = groupNamesResponse.m_allGroups;

	if( *groups )
	{
		printf("Please choose a group name from the list below:\n");
		i = *groups;
	
		for (; i > 0; --i)
		{
			j += printf("%s\n", &groups[j]);
		}
		scanf("%s", groupRequest.m_groupName);

		begin = ListItr_Begin(_client -> m_listGroups);
		end = ListItr_End(_client -> m_listGroups);
		if(end == ListItr_FindFirst(begin, end, Predicate, groupRequest.m_groupName))
		{
			groupRequest.m_tag = JOIN_GROUP_REQUEST;

			Protocol_Pack((void*)&groupRequest, pack, &size);
			ClientN_Send(_client->m_clientN, pack, size); 
		}
		else
		{
			UI_Err();
		}
	}
	else
	{
		printf("There is no exist groups to join !\n");
	}

	UI_LoginMenu();

	return;
}
	
		
static void Login_Res(char* _buffer, Client *_client)
{
	Register_Response loginResponse;
	Protocol_Unpack(_buffer, (void*)&loginResponse);
	/*UI add*/
	if(loginResponse.m_status == 1)
	{
	    UI_OK();
		_client -> m_listGroups = List_Create();
		if(NULL == _client -> m_listGroups)
		{
			ClientN_Destroy(&_client->m_clientN);
			return;
		}
		_client->m_login = 1;
		UI_LoginMenu();
	}
	else
	{
	    UI_Err();
        UI_StartMenu();
	}
}

static int DestroyChats (void *_element, void *_context)
{
	MulticastDestroy((char*)_element, (char*)_context);
	return 1;
}


void FreeGroups (void* groupName)
{
	free(groupName);
}


static void LogOut_Res(char* _buffer, Client *_client, int _flag)
{
	Register_Response logOutResponse;
	ListItr begin;
	ListItr end;
	
	Protocol_Unpack(_buffer, (void*)&logOutResponse);
	
	if(logOutResponse.m_status)
	{
		UI_OK();
		begin = ListItr_Begin(_client -> m_listGroups);
		end = ListItr_End(_client -> m_listGroups);
		ListItr_ForEach(begin, end, DestroyChats, _client->m_name);
		List_Destroy(&_client->m_listGroups, FreeGroups);
	}

	else
	{
		UI_Err();
	}
	_client->m_login = 0;

	if(_flag)
	{
		UI_StartMenu();
	}
	return;
}

static void Register_Res(char* _buffer)
{
    Register_Response registerResponse;

	Protocol_Unpack(_buffer , (void*)&registerResponse);		

	if(registerResponse.m_status == 1)
	{
		UI_OK();
		UI_StartMenu();
	}
	else
	{
		UI_Err();
		UI_StartMenu();
    }
}

/*END helper functions for Response_Handling*/

static ClientN_Status Response_Handling(Client* _client)
{
    char buffer[BUFFER_SIZE];
    char tag;

	if(CLIENT_NET_SUCCESS != ClientN_Recieve(_client->m_clientN, buffer, BUFFER_SIZE))
	{
		return CLIENT_NET_RECIEVE_FAIL;
	}
 
	Protocol_CheckTag(buffer, &tag);

  	switch(tag)
  	{
  		case REGISTER_RESPONSE:
			Register_Res(buffer);
  			break;
  			
  		case LOG_IN_RESPONSE:
  			Login_Res(buffer, _client);
  			break;
  			
  		case LOG_OUT_RESPONSE:
  		    LogOut_Res(buffer, _client, 1);
  		    break;
  		    	
  		case OPEN_GROUP_RESPONSE:
  			OpenGroup_Res(buffer, _client);
  			break;
  		
  		case GROUPS_NAMES_RESPONSE:
  			GroupNames_Res(buffer, _client);
  			break;

  		case JOIN_GROUP_RESPONSE:
  			OpenGroup_Res(buffer, _client);
  			break;

  		case LEAVE_GROUP_RESPONSE:
  			LeaveGroup_Res(buffer, _client);
  			break;
  	}

	return CLIENT_NET_SUCCESS;
}

/*END response handling*/

/*helper functions for Request_Handling*/

static void OpenGroup_Req(Client* _client)
{
	Group_Request openGroupRequest;
	size_t size;
	char pack[PACK_SIZE];
    
	openGroupRequest.m_tag = OPEN_GROUP_REQUEST;
	printf("\nPlease insert group name\n");
	scanf("%s",openGroupRequest.m_groupName);
	
	Protocol_Pack((void*)&openGroupRequest, pack, &size);
 	ClientN_Send(_client->m_clientN, pack, size);
}



static void GroupNames_Req(Client* _client)
{
	Groups_Names_Request groupNameRequest;
	size_t size;
	char pack[PACK_SIZE];
	
	groupNameRequest.m_tag = GROUPS_NAMES_REQUEST;
	Protocol_Pack((void*)&groupNameRequest, pack, &size);
	ClientN_Send(_client->m_clientN, pack, size);
}	
	

static void LogIn_Req(Client* _client)
{
	Register_Request logInRequest;
	size_t size;
	char pack[PACK_SIZE];

    UI_Login(logInRequest.m_name,logInRequest.m_password);

	strcpy(_client->m_name , logInRequest.m_name);

    logInRequest.m_tag = LOG_IN_REQUEST;
    
 	Protocol_Pack((void*)&logInRequest, pack, &size);
 	ClientN_Send(_client->m_clientN, pack, size);
}

static void Register_Req(Client* _client)
{
	Register_Request registerRequest;
    size_t size;
    char pack[PACK_SIZE];
    
    UI_Register(registerRequest.m_name,registerRequest.m_password);
    registerRequest.m_tag = REGISTER_REQUEST;

 	Protocol_Pack((void*)&registerRequest, pack, &size);
 	ClientN_Send(_client->m_clientN, pack, size);
}


static void LogOut_Req(Client* _client)
{
	Logout_Request logOutRequest;
	char pack[PACK_SIZE];
	Stream stream;
	size_t i, size;
	ListItr begin;
	ListItr end;

	logOutRequest.m_tag = LOG_OUT_REQUEST;
    strcpy(logOutRequest.m_name, _client->m_name);

	begin = ListItr_Begin(_client->m_listGroups);
	end = ListItr_End(_client->m_listGroups);

	stream.m_groupsNames[0] = List_Size(_client->m_listGroups);
	stream.m_groupsNames[1] = '\0';
	stream.m_index = 2;

	ListItr_ForEach(begin, end, ClientApp_GroupsStream, &stream);

	for(i = 0 ; i < stream.m_index + 1 ; ++i)
	{
		logOutRequest.m_groupsNames[i] = stream.m_groupsNames[i];
	}

    Protocol_Pack((void*)&logOutRequest, pack, &size);
    ClientN_Send(_client->m_clientN, pack, size);

}



int PrintAction(void* _element, void* _context)/*for ListItr_ForEach*/
{
	printf("%s\n",(char*)_element);
	return 1;
}

static void LeaveGroup_req(Client* _client)
{
	Group_Request leaveGroupRequest;
	char groupName[GROUP_NAME_SIZE];
	char pack[PACK_SIZE];
	size_t size;
	ListItr begin;
	ListItr end;
	ListItr returnVal;

	begin = ListItr_Begin(_client -> m_listGroups);
	end = ListItr_End(_client -> m_listGroups);
	if(begin == end)
	{
		printf("You have not joined to any group!\n");
		return;
	}
	ListItr_ForEach(begin, end, PrintAction, NULL);

	printf("Please enter the name of the group that you want to leave\n");
	scanf("%s", groupName);

	begin = ListItr_Begin(_client -> m_listGroups);
	end = ListItr_End(_client -> m_listGroups);
	returnVal = ListItr_FindFirst(begin, end, Predicate, groupName);
	if(returnVal == end)
	{
		printf("You entered incorrect name\n");
		UI_Err();
		UI_GroupMenu();
		return;
	}

	ListItr_Remove(returnVal);

	if(MULTICAST_SUCESS != MulticastDestroy(groupName, _client ->  m_name))
	{
		printf("There as been a problem in closing the multicast window\n");
		return;
	}
		
	leaveGroupRequest.m_tag = LEAVE_GROUP_REQUEST;
	strcpy(leaveGroupRequest.m_groupName, groupName);

    Protocol_Pack((void*)&leaveGroupRequest, pack, &size);
    ClientN_Send(_client->m_clientN, pack, size);	
}



/*END helper functions for request_Handling*/

static void Request_Handling(Client* _client)
{
	int userChoice;
    char buffer[BUFFER_SIZE];

	scanf("%d",&userChoice);
	
	if(!_client->m_login)
	{
		switch(userChoice)
		{
			case 0:
				Register_Req(_client);
         		break;

         	case 1:
         		LogIn_Req(_client);
         		break;

			case 9:
				exit(0);
				break;

			default:
				printf("The number %d is not one of the options !\nPlease enter again.\n", userChoice);
				break;
    	}
	}
		
	else
	{
		switch(userChoice)
		{
         	case 2:
         		LogOut_Req(_client);
         		break;

     		case 3:
     			OpenGroup_Req(_client);
     			break;

     		case 4:
     			GroupNames_Req(_client);
     			break;

			case 5:
				LeaveGroup_req(_client);
				break;

			case 9:
         		LogOut_Req(_client);
				ClientN_Recieve(_client->m_clientN, buffer, BUFFER_SIZE);
         		LogOut_Res(buffer, _client, 0);
				Client_Destroy(&_client);
				exit(0);
				break;

			default:
				printf("The number %d is not one of the options !\nPlease enter again.\n", userChoice);
				break;
     	}
	}
}

/*END request handling*/

/*END infer functions fo Client_Run*/
	

static int ClientApp_GroupsStream(void* _element, void* _context)
{
	char *name = (char*)_element, *groupsNames = ((Stream*)_context)->m_groupsNames;
	size_t index = ((Stream*)_context)->m_index;

	strcpy(&groupsNames[index] , name);

	((Stream*)_context)->m_index += strlen(name) + 1;

	return 1;
}




