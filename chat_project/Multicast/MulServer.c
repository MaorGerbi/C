#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>/*getpid*/
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096
#define STRING_FILE_SIZE 50

/*arg[1] is the ipGroup number
arg[2] is the port number*/

static int AllocateSock();
static void InitSock(struct sockaddr_in *_sinServer,struct ip_mreq *_mreq,  int _port, int _sock, char* _ipGroup);
static void BindSock(int _sock, struct sockaddr_in *_sinServer);
static void RecivedSocket(int _sock,struct sockaddr_in *_sinServer);
static void SavePid(char* _groupName, char* _userName);
static int Init(struct sockaddr_in *_sinServer,struct ip_mreq *_mreq, int _port,char* _ipGroup);

/*example for run:     ./MulServer.out '225.1.1.1' '1234'          */

int main(int argc, char *argv[])
{
	char* ipGroup;
	char* groupName;
	char* userName;
	int port;
	int sock;	
	struct sockaddr_in sinServer;
	struct ip_mreq mreq;

	if (argc != 5) {
		printf("wrong argument as been inserted\n");
		return 1;
	}

	ipGroup = argv[1]; 
	port = atoi(argv[2]);
	groupName = argv[3];
	userName = argv[4];
	

	SavePid(groupName, userName);

	sock = Init(&sinServer, &mreq, port, ipGroup);

	printf("this window is the muilticast windos,don't right in here\n\n");
	printf("welcome to group:  %s. \n",groupName);
	while (1)
	{
		RecivedSocket(sock,&sinServer);	
	}

	return 0;
}

static int Init(struct sockaddr_in *_sinServer,struct ip_mreq *_mreq, int _port,char* _ipGroup)
{
	int sock = AllocateSock();
	InitSock(_sinServer, _mreq, _port, sock, _ipGroup);
	BindSock(sock, _sinServer);
	
	return sock;
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

static void RecivedSocket(int _sock,struct sockaddr_in *_sinServer)
{
	socklen_t sin_len = sizeof(*_sinServer);
	char buffer[BUFFER_SIZE];
	int read_bytes;
	read_bytes = recvfrom(_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr*)_sinServer, &sin_len);

	if(read_bytes < 0)
	{
		perror("revfrom falier");
	}

	printf("%s\n", buffer);
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

static void InitSock(struct sockaddr_in *_sinServer,struct ip_mreq *_mreq,  int _port, int _sock, char* _ipGroup)
{
	__u_int yes = 1;

	/*allow multiple sockets to use the same PORT number*/
	if(setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes)) < 0)
	{
		perror("setsockopt failed");
		abort();
	}
	memset(_sinServer, 0, sizeof(*_sinServer));/*importent to initilize all other members*/
	_sinServer -> sin_family = AF_INET;
	_sinServer -> sin_addr.s_addr = inet_addr(_ipGroup);/*give an addres,not importemt what addres*/
	_sinServer -> sin_port = htons(_port);/*need to have the same number as the server*/

	/*add sock to the multicast ipGroup*/
	_mreq -> imr_multiaddr.s_addr = inet_addr(_ipGroup);
	_mreq -> imr_interface.s_addr = htonl(INADDR_ANY);
	if(setsockopt(_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) _mreq, sizeof(*_mreq)) < 0)
	{
		perror("setsockopt");
		abort();
	}
}

/*to connect sock to specific port*/
static void BindSock(int _sock, struct sockaddr_in *_sinServer)
{
	if(bind(_sock, (struct sockaddr*)_sinServer, sizeof(*_sinServer)) < 0)
	{
		perror("bind falier");
		abort();
	}
}

