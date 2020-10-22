#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_SIZE 4096
#define STRING_FILE_SIZE 50

/*arg[1] is the group number
arg[2] is the port number*/

static int AllocateSock();
static void InitSin(struct sockaddr_in* _sinClient,char* _group, int _port);
static void SendSocket(int _sock, struct sockaddr_in *_sinClient, char _data[]);
static int InitScok(struct sockaddr_in* _sinClient, char* _group, int _port);
static void SavePid(char* _groupName, char* _userName);

int main(int argc, char *argv[])
{
	char* group;
	char* groupName;
	char* userName;
	int port;
	int sock;
	struct sockaddr_in sinClient;
	char data[MAX_DATA_SIZE];
	char dataToSend[MAX_DATA_SIZE];

	if (argc != 5)
	{
		printf("wrong argument as been inserted\n");	
		return 1;
	}

	group = argv[1];
	port = atoi(argv[2]);
	groupName =argv[3];
	userName =argv[4];

	SavePid(groupName, userName);
	
	sock = InitScok(&sinClient, group, port);
	printf("this window is for writing only, please right you meassags in here:\n");
	printf("welcome %s to group: %s\n",userName, groupName);

	while(1)
	{
		fgets(data, MAX_DATA_SIZE, stdin); 
		sprintf(dataToSend,"%s: %s", userName, data);
		SendSocket(sock, &sinClient, dataToSend);

		sleep(1); 
	}

	return 0;
}

static void SavePid(char* _groupName, char* _userName)
{
	FILE* file;
	char fileStr[STRING_FILE_SIZE];

	sprintf(fileStr,"Files/%s%s", _groupName, _userName);
	file = fopen(fileStr, "a");
	fprintf(file,"%d\n", getpid());
	fclose(file);
}

static void SendSocket(int _sock, struct sockaddr_in *_sinClient, char _data[])
{
	int sent_bytes;

	sent_bytes = sendto(_sock, _data, strlen(_data) + 1, 0, (struct sockaddr*)_sinClient, sizeof(*_sinClient));

	if(sent_bytes < 0)
	{
		perror("sento falier");
		abort();
	}
}

static int InitScok(struct sockaddr_in* _sinClient, char* _group, int _port)
{
	int sock = AllocateSock();
	InitSin(_sinClient, _group, _port);

	return sock;
}

static int AllocateSock()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		perror("socket falier");
		abort();
	}

	return sock;
}


static void InitSin(struct sockaddr_in* _sinClient,char* _group, int _port)
{
	memset(_sinClient, 0, sizeof(*_sinClient));
	_sinClient -> sin_family = AF_INET;
	_sinClient -> sin_addr.s_addr = inet_addr(_group);
	_sinClient -> sin_port = htons(_port);
}
