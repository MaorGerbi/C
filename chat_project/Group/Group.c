#include <stdlib.h>
#include <string.h>
#include "Group.h"

#define PORT "5000"
#define PORT_SIZE 6

struct Group
{
	char *m_name;
	char *m_address;
	char m_port[PORT_SIZE];
	size_t m_numOfUsers;
};


Group* Group_Create (char *_groupName, char *_address)
{
	Group *group = NULL;

	if(NULL == _groupName || NULL == _address)
	{
		return NULL;
	}

	if(NULL == (group = (Group*)calloc(1 , sizeof(Group))))
	{
		return NULL;
	}

	if(NULL == (group->m_name = (char*)malloc(strlen(_groupName) + 1)))
	{
		free(group);
		return NULL;
	}

	strcpy(group->m_name , _groupName);
	group->m_address = _address;
	strcpy(group->m_port , PORT);

	return group;
}


char* Group_Destroy (Group **_group)
{
	char *address = NULL;
	if(NULL == _group || NULL == *_group)
	{
		return NULL;
	}

	address = (*_group)->m_address;

	free(*_group);

	return address;
}


void Group_AddUser (Group *_group)
{
	if(NULL == _group)
	{
		return;
	}

	++_group->m_numOfUsers;

	return;
}


void Group_RemoveUser (Group *_group)
{
	if(NULL == _group)
	{
		return;
	}

	--_group->m_numOfUsers;

	return;
}


size_t Group_Size (const Group *_group)
{
	return NULL == _group ? 0 : _group->m_numOfUsers;
}


char* Group_GetName (const Group *_group)
{
	if(NULL == _group)
	{
		return NULL;
	}
	
	return _group->m_name;
}


void Group_ChangeName (Group *_group, const char *_newName)
{
	if(NULL == _group || NULL == _newName)
	{
		return;
	}
	strcpy(_group->m_name , _newName);
	return;
}


void Group_GetAddress (const Group *_group, char *_groupAddress)
{
	if(NULL == _group || NULL == _groupAddress)
	{
		return;
	}
	strcpy(_groupAddress , _group->m_address);
	return;
}


void Group_GetPort (const Group *_group, char *_groupPort)
{
	if(NULL == _group || NULL == _groupPort)
	{
		return;
	}
	strcpy(_groupPort , _group->m_port);
	return;
}


