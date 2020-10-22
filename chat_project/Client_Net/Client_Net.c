#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>     

#include "Client_Net.h"

#define FAIL -1
#define NOT_VALID_PORT(port) (0 > port || port > 64000)
 
struct ClientN{
	int   m_sock;
	int   m_port;
	char* m_ip;
};

static void InitAddr(ClientN* _clientN, struct sockaddr_in* _Sin);
static int Init_Socket();


ClientN* ClientN_Create(char* _destIp, int _port)
{
	ClientN* clientN = NULL;
	int ipLength = 0;
		
    if(NULL == _destIp || NOT_VALID_PORT(_port))
    {
    	return NULL;
    }
    
	clientN = (ClientN*)malloc(sizeof(ClientN));
	if(NULL == clientN)
	{
		return NULL;
	}
	
	ipLength = strlen(_destIp)+1;
	clientN->m_ip = (char*)malloc(sizeof(char)*ipLength);
	if(NULL == clientN->m_ip)
	{
		free(clientN);
		return NULL;
	}
	
	clientN->m_port = _port;
	strcpy(clientN->m_ip, _destIp);
	clientN->m_sock = 0;
	
	return clientN;
}

void ClientN_Destroy(ClientN** _clientN)
{
	if(NULL == _clientN)
	{
		return;
	}
	close((*_clientN)->m_sock);
	free(*_clientN);
	*_clientN = NULL;
}

ClientN_Status ClientN_Connect(ClientN* _clientN)
{
 	struct sockaddr_in Sin;
 	
 	if(NULL == _clientN)
 	{
 		return CLIENT_NET_UNINITIALZED;
 	}
 	
	_clientN->m_sock = Init_Socket();
	if(FAIL == _clientN->m_sock)
	{
		return CLIENT_NET_CONECT_FAIL;
	}
	
	InitAddr(_clientN, &Sin);
		
	if (connect(_clientN->m_sock, (struct sockaddr*)&Sin, sizeof(Sin)) < 0)
	{ 
		return CLIENT_NET_CONECT_FAIL;
	} 
	
	return CLIENT_NET_SUCCESS;
}

ClientN_Status ClientN_Send(ClientN* _clientN, char* _data, size_t _len)
{
	int sendBytes;
    
	if(NULL == _clientN|| NULL == _data)
 	{
 		return CLIENT_NET_UNINITIALZED;
 	}
 	
 	sendBytes = send(_clientN->m_sock, _data, _len, 0);
	if(0 == sendBytes)
	{
		return CLIENT_NET_SEND_FAIL;
	}  	
	
	return CLIENT_NET_SUCCESS;
} 

ClientN_Status ClientN_Recieve(ClientN* _clientN, char* _buffer, size_t _bufferLen)
{
    int readBytes = 0;
    
	if(NULL == _clientN|| NULL == _buffer)
 	{
 		return CLIENT_NET_UNINITIALZED;
 	}
 	
 	readBytes = recv(_clientN->m_sock, _buffer, _bufferLen ,0); 
	if(0 == readBytes)
	{
		return CLIENT_NET_RECIEVE_FAIL;
	}
	return CLIENT_NET_SUCCESS;
}

int ClientN_GetSock(ClientN* _clientN)
{
    return (NULL == _clientN) ? -1:  _clientN->m_sock;

}

/**********************INER FUNC**************************************/
static void InitAddr(ClientN* _clientN, struct sockaddr_in* _Sin)
{
	memset(_Sin, 0, sizeof(*_Sin));
	
	_Sin->sin_family = AF_INET;
	_Sin->sin_addr.s_addr = inet_addr(_clientN->m_ip);
	_Sin->sin_port = htons(_clientN->m_port);
}

static int Init_Socket()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > sock)
	{
		return FAIL;
	}	
	return sock;
}

	
