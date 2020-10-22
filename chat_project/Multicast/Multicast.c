#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Multicast.h"

#define STRING_SIZE 200
#define SYSTEM_STRING_SIZE 60
#define PORT_SIZE 6
#define MAX_PORT 64000

static int FileCreate(char* _groupName ,char* _userName);

Multicast_Result MulticastCreate(char* _group, int _port, char* _groupName, char* _userName)
{
	char str[STRING_SIZE];
	int ReturnVal;
	
	if(_port < 0 || _port > MAX_PORT)
	{
		return MULTICAST_PORT_ERR;
	}

	/*need to check _group number in here*/
	
	if(!FileCreate(_groupName, _userName))
	{
		return MULTICAST_FILE_ERR;
	}


	sprintf(str, "gnome-terminal -- ./MulServer.out '%s' '%d' '%s' '%s'", _group, _port, _groupName, _userName);/*this line need the MulServer.out function*/
	ReturnVal = system(str);

	if(-1 == ReturnVal)
	{
		return MULTICAST_GENERAL_ERR;
	}

	sprintf(str, "gnome-terminal -- ./MulClient.out '%s' '%d' '%s' '%s'", _group, _port, _groupName, _userName);/*this line need the MulClient.out function*/

	ReturnVal = system(str);
	if(-1 == ReturnVal)
	{
		return MULTICAST_GENERAL_ERR;
	}

	return MULTICAST_SUCESS;
}

Multicast_Result MulticastDestroy(char* _groupName, char* _userName)
{
	FILE* file;
	char fileStr[STRING_SIZE];
	char SysStr[SYSTEM_STRING_SIZE];
	int len;

	sprintf(fileStr,"Files/%s%s", _groupName, _userName);/*need to make sure the File is exsits*/
	file = fopen(fileStr, "r");
	if(NULL == file)
	{
		return MULTICAST_FILE_ERR;
	}

	
	while(!feof(file))/*TODO- ruing one more time then it should*/
	{
		if(!fgets(fileStr, STRING_SIZE, file))
		{
			break;
		}
		len = strlen(fileStr);
		fileStr[len - 1] = '\0';

		sprintf(SysStr, "kill -9 %s", fileStr);	
	
		if(-1 == system(SysStr))
		{
			return MULTICAST_GENERAL_ERR;
		}
	}
		
	
	fclose(file);
	remove(fileStr);/*not removeing*/

	return MULTICAST_SUCESS;

}

static int FileCreate(char* _groupName ,char* _userName)
{
	FILE* file;
	char fileStr[STRING_SIZE];

	sprintf(fileStr,"Files/%s%s", _groupName, _userName);/*need to make sure the File is exsits*/
	file = fopen(fileStr, "w");

	if(NULL == file)
	{
		printf("file could not be opend \n");
		return 0;
	}

	fclose(file);
	return 1;
}
