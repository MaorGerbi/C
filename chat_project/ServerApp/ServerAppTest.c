#include <stdio.h>
#include "ServerApp.h"

int main(void)
{
	ServerApp *serv = NULL;
	

	serv = ServertApp_Create("../file/FileUserPasswords.txt", 1000);


	if(NULL == serv)
	{
		printf("server is NULL !!!!\n");
		return 0;
	}

	ServerApp_Run(serv);

	ServerApp_Destory(&serv);

	return 0;
}
