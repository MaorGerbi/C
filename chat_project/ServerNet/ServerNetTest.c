#include <stdio.h>
#include <string.h>
#include "ServerNet.h"


typedef enum
{
    PASSED,
    FAILED
} Status;

typedef struct Package
{
	char m_signal;
	char m_name[30];
	char m_password[30];
	size_t m_clientNumber;
}Package;

typedef struct Context
{
	size_t m_numOfClient;
	char m_string[50];
	ServerNet *m_server;
}Context;

Status Test_Create (void); /* Create Test 1 */
Status Test_Create_Functions (void); /* Create Test 2 */
Status Test_Destroy (void); /* Destroy Test 3 */
Status Test_Run (void); /* Run Test 4 */


void PrintTest (Status status); /* Print if Test if PASSED or FAILED */



static void Server_NewClient (int _sock, void* _context);
static void Server_CloseClient (int _sock, void* _context);
static void Server_GotMessage (int _client_sock, void* _inMsg, void* _context);
static void Server_Fail (int _sock, void* _context);

int k;

int main (void)
{
	putchar('\n');
	printf("Create Tests:\n");
	PrintTest(Test_Create());
	PrintTest(Test_Create_Functions());

	putchar('\n');
	printf("Destroy Tests:\n");
	PrintTest(Test_Destroy());

	putchar('\n');
	printf("Run Tests:\n");
	PrintTest(Test_Run());


	return 0;
}





/* ---------- Print Function ---------- */

void PrintTest (Status status) /* Print if Test if PASSED or FAILED */
{
	if(PASSED == status)
	{
		printf("Test %d PASSED \n" , ++k);
	}
	else
	{
		printf("Test %d FAILED \n" , ++k);
	}
}


/* ---------- Create Tests ---------- */

Status Test_Create (void) /* Create Test 1 */
{
	ServerNet *server = ServerNet_Create (NULL, NULL, NULL, NULL);
	if(NULL == server)
	{
		return FAILED;
	}
	ServerNet_Destroy(&server);
	return PASSED;
}


Status Test_Create_Functions (void) /* Create Test 2 */
{
	ServerNet *server = ServerNet_Create (Server_NewClient, Server_GotMessage, Server_CloseClient, Server_Fail);
	if(NULL == server)
	{
		return FAILED;
	}
	ServerNet_Destroy(&server);
	return PASSED;
}




/* ---------- Destroy Tests ---------- */

Status Test_Destroy (void) /* Destroy Test 3 */
{
	ServerNet *server = ServerNet_Create (NULL, NULL, NULL, NULL);
	ServerNet_Destroy(&server);
	ServerNet_Destroy(&server);
	if(NULL != server)
	{
		return FAILED;
	}
	return PASSED;
}




/* ---------- Run Tests ---------- */

Status Test_Run (void) /* Run Test 4 */
{
	Context con;
	ServerNet *server = ServerNet_Create (Server_NewClient, Server_GotMessage, Server_CloseClient, Server_Fail);

	con.m_numOfClient = 0;
	strcpy(con.m_string , "i am a context string !\n");
	con.m_server = server;

	ServerNet_Run(server, (void*)&con);

	ServerNet_Destroy(&server);
	return PASSED;
}





/* ---------- Local Server Functions ---------- */

static void Server_NewClient (int _sock, void* _context)
{
	++((Context*)_context)->m_numOfClient;
	if(((Context*)_context)->m_numOfClient == 1)
	{
		printf("number of clients = %ld\n", ((Context*)_context)->m_numOfClient);
	}
	return;
}


static void Server_CloseClient (int _sock, void* _context)
{
	--((Context*)_context)->m_numOfClient;
	if(((Context*)_context)->m_numOfClient == 0)
	{
		printf("number of clients = %ld\n", ((Context*)_context)->m_numOfClient);
	}
	return;
}


static void Server_GotMessage (int _client_sock, void* _inMsg, void* _context)
{
	char send[] = "hi client !\n";
	Package pack;
	Context con;

	memcpy(&pack , _inMsg, sizeof(pack));
	memcpy(&con , _context, sizeof(con));
	printf("numOfClients = %ld , context = %s" , con.m_numOfClient, con.m_string);
	printf("signal = %c , name = %s , password = %s , client_number = %ld \n\n" , pack.m_signal, pack.m_name, pack.m_password, pack.m_clientNumber);
	if(SERVER_SUCCESS != ServerNet_Send (_client_sock, send, strlen(send) + 1))
	{
		printf("Send Failed !\n");
	}
	return;
}


static void Server_Fail (int _sock, void* _context)
{
	printf("Server_Fail\n");
	return;
}







