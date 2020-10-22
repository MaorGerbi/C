#include <stdio.h> /* perror */
#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* close */
#include <string.h> /* strcpy, memset */
#include <sys/types.h> /* ssize_t, select */
#include <sys/select.h> /* fd_set */
#include <netinet/in.h> /* struct sockadder_in */
#include <arpa/inet.h> /* inet_addr */
#include <errno.h> /* errno */
#include <fcntl.h> /* fcntl */
#include <sys/select.h> /* select */
#include "GenDLL.h" /* List_Create, List_Destroy, List_PushHead */
#include "list_itr.h" /* List, List_Itr */
#include "ServerNet.h"


#define QUEUE_SIZE 100
#define SERVER_CAPACITY 1000
#define MAX_PACKAGE_SIZE 4096
#define PORT 9000
#define FAIL -1
#define OK 1
#define MAX_SD 1024
#define ACCEPT_IN_ROW 4
#define STDIN_SOCKET 0
#define PAUSE_SIZE 6

struct ServerNet
{
	List *m_list;
	int m_sock;
	struct sockaddr_in m_sin;
	int m_optval;
	fd_set m_readfds;
	int m_counter;
	char m_flag;
	New_Client m_newClient;
	Got_Message m_gotMsg;
	Close_Client m_closeClient;
	Fail m_fail;
};



static int Server_Init(ServerNet *_server);
static int* Client_New(ServerNet *_server, void* _context);
static void Client_Exist(ServerNet *_server, ListItr **_element, int *_sock_client, void* _buffer, void* _context);
void Client_AddNumber(char *_workS, char *_buffer, char *_output);
static void Socket_Remove (int *_sock_list, ListItr **_element);
static void Socket_Close (void* _item);



ServerNet* ServerNet_Create(New_Client _newC, Got_Message _gotM, Close_Client _closeC, Fail _fail)
{
	ServerNet *server = NULL;

	if(NULL == (server = (ServerNet*)calloc(1 , sizeof(ServerNet))))
	{
		return NULL;
	}

	server->m_newClient = _newC;
	server->m_gotMsg = _gotM;
	server->m_closeClient = _closeC;
	server->m_fail = _fail;
	server->m_optval = 1;

	if(FAIL == Server_Init(server))
	{
		free(server);
		return NULL;
	}

	if(NULL == (server->m_list = List_Create()))
	{
		free(server);
		return NULL;
	}

	return server;	
}




ServerN_Result ServerNet_Run( ServerNet* _server, void* _context)
{
	fd_set read_current;
	ListItr *element = NULL, *lastElement = NULL;
	int i, *sock_list = NULL, activity;
	char* buffer[MAX_PACKAGE_SIZE], pause[PAUSE_SIZE];

	_server->m_flag = 1;

	printf("\nTo pause the server - write \"pause\"\n");

	while(_server->m_flag)
	{
		read_current = _server->m_readfds;
		activity = select(MAX_SD, &read_current, NULL, NULL, NULL);
		if(activity < 0 && errno != EINTR)
		{
			return SERVER_SELECT_FAILED;
		}

		if(FD_ISSET(STDIN_SOCKET, &read_current))
		{
			scanf("%s",pause);
			if( !strcmp("pause" , pause) )
			{
				_server->m_flag = 0;
			}
			else
			{
				printf("\nTo pause the server - write \"pause\"\n");
			}
		}


		if(FD_ISSET(_server->m_sock, &read_current))
		{
			for(i = 0 ; i < ACCEPT_IN_ROW ; ++i)
			{
				sock_list = Client_New(_server, _context);
				if(NULL != sock_list)
				{
					if(LIST_SUCCESS != List_PushHead(_server->m_list, sock_list))
					{
						return SERVER_ALLOCATION_ERROR;
					}
				}
				else
				{
					break;
				}
			}
			--activity;
		}

		lastElement = ListItr_End(_server->m_list);
		element = ListItr_Begin(_server->m_list);

		while(activity && element != lastElement)
		{
			sock_list = ListItr_Get(element);

			if(FD_ISSET(*sock_list, &read_current))
			{
				Client_Exist (_server, &element, sock_list, buffer, _context);
				--activity;
			}
			element = ListItr_Next(element);
		}
	}
	return SERVER_SUCCESS;
}




ServerN_Result ServerNet_Send (int _sock_client, void* _message, size_t _msgSize)
{
	if( send(_sock_client, _message, _msgSize, 0) < 0)
	{
		if(errno != EAGAIN && errno != EWOULDBLOCK)
		{
			return SERVER_SEND_FAILED;
		}
	}
	return SERVER_SUCCESS;
}




size_t ServerNet_Pause (ServerNet *_server)
{
	if(NULL == _server)
	{
		return 0;
	}
	_server->m_flag = 0;
	return List_Size(_server->m_list);
}




void ServerNet_Destroy (ServerNet **_server)
{
	if(NULL == _server || NULL == *_server)
	{
		return;
	}
	List_Destroy(&(*_server)->m_list, Socket_Close);
	close((*_server)->m_sock);
	free(*_server);
	*_server = NULL;
	return;
}




/* ---------- Local Functions ---------- */

static int* Client_New(ServerNet *_server, void* _context)
{
	socklen_t sin_len = sizeof(_server->m_sin);
	int sock_client, *sock_list = NULL;

	sock_client = accept(_server->m_sock, (struct sockaddr*)&_server->m_sin, &sin_len);

	if( sock_client < 0 )
	{
		if(errno != EAGAIN && errno != EWOULDBLOCK)
		{
			_server->m_flag = 0;
		}
	}
	else
	{
		sock_list = (int*)malloc(sizeof(int));
		*sock_list = sock_client;
		if(_server->m_counter == SERVER_CAPACITY)
		{
			close(*sock_list);
			free(sock_list);
			sock_list =  NULL;
		}
		else
		{
			++_server->m_counter;
			FD_SET(*sock_list, &_server->m_readfds);
			if(NULL != _server->m_newClient)
			{
				_server->m_newClient(sock_client, _context);
			}
		}
	}

	return sock_list;
}




static void Client_Exist(ServerNet *_server, ListItr **_element, int *_sock_client, void* _buffer, void* _context)
{
	ssize_t receive = recv(*_sock_client, _buffer, BUFFER_SIZE, 0);

	if(0 >= receive)
	{
		FD_CLR(*_sock_client, &_server->m_readfds);
		Socket_Remove (_sock_client, _element);
		--_server->m_counter;

		if(0 == receive)
		{
			if(NULL != _server->m_closeClient)
			{
				_server->m_closeClient(*_sock_client, _context);
			}
		}

		else
		{
			if(NULL != _server->m_fail)
			{
				_server->m_fail(*_sock_client, _context);
			}			
		}
	}

	else
	{
		if(NULL != _server->m_gotMsg)
		{
			_server->m_gotMsg(*_sock_client, _buffer, _context);
		}
	}
	return;
}




/* ---------- Static Function For Local Function ---------- */

static int Server_Init(ServerNet *_server)
{
	int flags;

	_server->m_sin.sin_family = AF_INET;
	_server->m_sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	_server->m_sin.sin_port = htons(PORT);

	if((_server->m_sock = socket(AF_INET , SOCK_STREAM, 0)) < 0)
	{
		return FAIL;
	}

	FD_SET(_server->m_sock, &_server->m_readfds);
	FD_SET(STDIN_SOCKET, &_server->m_readfds);

	if(setsockopt(_server->m_sock, SOL_SOCKET, SO_REUSEADDR, &_server->m_optval, sizeof(_server->m_optval)) < 0)
	{
		return FAIL;
	}

	if( FAIL == (flags = fcntl(_server->m_sock , F_GETFL)) )
	{
		return FAIL;
	}
	if( FAIL == fcntl(_server->m_sock , F_SETFL, flags | O_NONBLOCK) )
	{
		return FAIL;
	}

	if( bind(_server->m_sock, (struct sockaddr*)&_server->m_sin, sizeof(_server->m_sin)) < 0 )
	{
		return FAIL;
	}

	if(listen(_server->m_sock, QUEUE_SIZE) < 0)
	{
		return FAIL;
	}

	return OK;	
}


static void Socket_Remove (int *_sock_list, ListItr **_element)
{
	close(*_sock_list);
	*_element = ListItr_Next(*_element);
	ListItr_Remove(ListItr_Prev(*_element));
	*_element = ListItr_Prev(*_element);
	free(_sock_list);
	return;
}


static void Socket_Close (void* _item)
{
	close(*((int*)_item));
	free(_item);
	return;
}


