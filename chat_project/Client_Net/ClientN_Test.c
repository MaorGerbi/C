#include <stdio.h>
#include "Client_Net.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"
#define PORT 1234
#define BUFFER_LENGTH 4096
struct ClientN{
	int   m_sock;
	int   m_port;
	char* m_ip;
};

typedef enum Status{ERR, OK} Status;

void Test_Print(Status status)
{
	status ? printf(GRN"\nPASS!\n"RESET) : printf(RED"\nFAILED\n"RESET);
}

void Test_ClientNCreate()
{
	ClientN* clientN = NULL;
	int port = PORT;
	char* ipDest = "127.0.0.1";
	
	printf("Test_ClientNCreate \n");
	clientN = ClientN_Create(ipDest,port);
	clientN ? Test_Print(OK) : Test_Print(ERR);
	ClientN_Destroy(&clientN);
	
	clientN = ClientN_Create(NULL, port);
	clientN ? Test_Print(ERR) : Test_Print(OK);
	
	
	clientN = ClientN_Create(ipDest, -1);
	clientN ? Test_Print(ERR) : Test_Print(OK);
	
}

void Test_ClientNDestroy()
{
	ClientN* clientN = NULL;
	int port = PORT;
	char* ipDest = "127.0.0.1";
	
	printf("Test_ClientNDestroy \n");
	clientN = ClientN_Create(ipDest,port);
	ClientN_Destroy(&clientN);
	clientN ? Test_Print(ERR) : Test_Print(OK);

}
void Test_ClientNConnect()
{
	ClientN* clientN = NULL;
	int port = PORT;
	char* ipDest = "127.0.0.1";
	ClientN_Status status;
	
	printf("Test_ClientNConnect \n");
	clientN = ClientN_Create(ipDest,port);
	
	status = ClientN_Connect(clientN);
	status == CLIENT_NET_SUCCESS ? Test_Print(OK) : Test_Print(ERR);
	
	status = ClientN_Connect(NULL);
	status == CLIENT_NET_UNINITIALZED ? Test_Print(OK) : Test_Print(ERR);
	
}	
	
void Test_ClientNSend()
{
	ClientN* clientN = NULL;
	int port = PORT;
	char* ipDest = "127.0.0.1";
	char *data = "hello from client!!";
	ClientN_Status status;
	
	
	printf("Test_ClientNSend \n");
	
	clientN = ClientN_Create(ipDest,port);
	ClientN_Connect(clientN);
	status = ClientN_Send(clientN, data);
	status == CLIENT_NET_SUCCESS ? Test_Print(OK) : Test_Print(ERR);
	
	status = ClientN_Send(NULL, data);
	status == CLIENT_NET_UNINITIALZED ? Test_Print(OK) : Test_Print(ERR);
	
	
}
void Test_ClientNRecieve()
{
	ClientN* clientN = NULL;
	int port = PORT;
	char* ipDest = "127.0.0.1";
	char* data = "hello from client!!";
	ClientN_Status status;
	char buffer[BUFFER_LENGTH];
	
	printf("Test_ClientNRecieve() \n");
	clientN = ClientN_Create(ipDest,port);
	ClientN_Connect(clientN);
	status = ClientN_Send(clientN, data);
	status = ClientN_Recieve(clientN, buffer, BUFFER_LENGTH);
	status == CLIENT_NET_SUCCESS ? Test_Print(OK) : Test_Print(ERR);
	printf("%s \n", buffer);
}		
int main()
{
    
	Test_ClientNCreate();
	
	Test_ClientNDestroy();
	Test_ClientNConnect();
	Test_ClientNSend();
	
	Test_ClientNRecieve();
	
	return 0;
}
