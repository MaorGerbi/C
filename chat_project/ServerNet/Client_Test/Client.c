#include <stdio.h> /* printf */
#include <stdlib.h> /* exit */
#include <string.h> /* memset */
#include <unistd.h> /* close */
#include <sys/socket.h> /* socklen_t, socket, recvfrom, sendto */
#include <sys/types.h> /* ssize_t */
#include <netinet/in.h> /* struct sockadder_in */
#include <arpa/inet.h> /* htons */

#define SIZE 100
#define PORT 9000

static void Sock_Init(struct sockaddr_in *_sin);
static void Sock_Create(int *_sock);
static void Sock_Connect(int *_sock, struct sockaddr_in *_sin);
static void Sock_Send(int *_sock, void* _package);
static void Sock_Receive(int *_sock, char *_buffer);

typedef struct Package
{
	char m_signal;
	char m_name[30];
	char m_password[30];
	size_t m_clientNumber;
}Package;

int main (void)
{
	struct sockaddr_in sin;
	int sock;
	char pack[] = { 0 , 'z', 'i', 'v' , '\0' , '1' , '2' , '3' , '\0'};
	char buffer[SIZE];

	Sock_Create(&sock);

	Sock_Init(&sin);

	Sock_Connect(&sock, &sin);


	Sock_Send(&sock, pack);

	Sock_Receive(&sock, buffer);

	puts(buffer);

	close(sock);
	
	return 0;
}




static void Sock_Init(struct sockaddr_in *_sin)
{
	memset (_sin , 0 , sizeof(*_sin));
	_sin->sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &_sin->sin_addr.s_addr);
	_sin->sin_port = htons(PORT);
	return;	
}

static void Sock_Create(int *_sock)
{
	*_sock = socket (AF_INET , SOCK_STREAM, 0);
	if(*_sock < 0)
	{
		perror ("socket failed");
		exit(0);
	}
	return;
}


static void Sock_Connect(int *_sock, struct sockaddr_in *_sin)
{
	if( connect(*_sock, (struct sockaddr*)_sin, sizeof(*_sin)) < 0 ) /* fixes the port in the sock */
	{
		perror("connection failed");
		exit(0);
	}
	return;
}


static void Sock_Send(int *_sock, void* _package)
{
	if( send(*_sock, _package, SIZE, 0) < 0)
	{
		perror("sendto failed");
		exit(0);
	}
	return;
}


static void Sock_Receive(int *_sock, char *_buffer)
{
	if( recv(*_sock, _buffer, SIZE, 0) < 0 )
	{
		perror("recvfrom failed");
		exit(0);
	}
	return;
}




