#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcpy, strlen */
#include <stdio.h> /* sprintf */
#include <limits.h> /* UCHAR_MAX */
#include "GroupM.h"
#include "Group.h"
#include "HashMap.h"
#include "GenQueue.h"

#define MAX_BUFFER_SIZE 4000
#define ADDRESS_SIZE 15
#define ADDRESS_FIRST_BYTE 225
#define PORT "5000"
#define PREV_BYTE(NUM) ((NUM) -= 4)
#define UNITY 2
#define TENS 1
#define HUNDREDS 0


struct GroupM
{
	HashMap *m_groups; /* Contain groups, key = group name*/
	Queue *m_addressBank; /* Pull of IP addresses for Groups */
};

typedef struct Stream
{
	char m_groupsNames[MAX_BUFFER_SIZE];
	size_t m_index;
}Stream;


static GroupM_Result Fill_AddressesBank(Queue *_addressesBank, size_t _pullSize);
static void UpdateAddress(char *_address, int *_num1, int *_num2, int *_num3, int *_num4);
static size_t HashFunc (const void* _key); /* return the last 6 digits of an address */
static int GroupEqualityCheck (const void* _firstKey, const void* _secondKey);
static int Check_Status (int status);
static void GroupM_GroupDestroy (void* _key);
static int GroupM_GroupsStream(const void* _key, void* _value, void* _context);



GroupM* GroupM_Create (size_t _numOfGroups)
{
	GroupM *groupM = NULL;

	if(NULL == (groupM = (GroupM*)malloc(sizeof(GroupM))))
	{
		return NULL;
	}

	if(NULL == (groupM->m_groups = HashMap_Create(_numOfGroups, HashFunc, GroupEqualityCheck)))
	{
		free(groupM);
		return NULL;
	}

	if(NULL == (groupM->m_addressBank = Queue_Create(_numOfGroups)))
	{
		free(groupM->m_groups);
		free(groupM);
		return NULL;
	}

	if(GROUPM_SUCCESS != Fill_AddressesBank(groupM->m_addressBank, _numOfGroups))
	{
		return NULL;
	}

	return groupM;
}




void GroupM_Destroy (GroupM **_groupM)
{
	if(NULL == _groupM || NULL == *_groupM)
	{
		return;
	}

	HashMap_Destroy(&(*_groupM)->m_groups, NULL , GroupM_GroupDestroy );
	Queue_Destroy(&(*_groupM)->m_addressBank , free);
	free(*_groupM);
	*_groupM = NULL;
	return;
}




GroupM_Result GroupM_OpenGroup (GroupM *_groupM, char *_groupName, char *_address, char *_port)
{
	Group *group = NULL;
	Map_Result statusMap;
	Queue_Result statusQueue;
	char *address = NULL;
	if(NULL == _groupM || NULL == _groupName || NULL == _address || NULL == _port)
	{
		return GROUPM_UNINITIALIZED_ERROR;
	}

	/* Looking for duplicate Group name */
	if(MAP_KEY_NOT_FOUND_ERROR != (statusMap = HashMap_Find(_groupM->m_groups, _groupName, (void**)&group)))
	{
		return Check_Status(statusMap);
	}

	/* getting an address from the Queue bank */
	if(QUEUE_SUCCESS != (statusQueue = Queue_Dequeue(_groupM->m_addressBank, (void**)&address)))
	{
		return GROUPM_OVERFLOW_ERROR;
	}

	/* Creating a new group */
	if(NULL == (group = Group_Create(_groupName, address)))
	{
		Queue_Enqueue(_groupM->m_addressBank, address);
		return GROUPM_ALLOCATION_ERROR;
	}

	Group_AddUser(group);

	/* Adding the new group to the Hash_Map container */
	if(MAP_SUCCESS != (statusMap = HashMap_Insert(_groupM->m_groups, Group_GetName(group), group)))
	{
		Queue_Enqueue(_groupM->m_addressBank, address);
		Group_Destroy(&group);
		return Check_Status(statusMap);
	}

	strcpy(_address , address);
	strcpy(_port , PORT);

	return GROUPM_SUCCESS;
}




void GroupM_GetAllGroups (GroupM *_groupM, char *_groupsNames)
{
	Stream stream;
	size_t numOfGroups;
	int i;

	if(NULL == _groupM || NULL == _groupsNames)
	{
		return;
	}

	stream.m_groupsNames[1] = '\0'; /* a space between the groups amount and all the groups names */

	stream.m_index = 2; /* first index for groups names */

	numOfGroups = HashMap_ForEach(_groupM->m_groups, GroupM_GroupsStream , &stream);

	stream.m_groupsNames[0] = numOfGroups; /* num of groups in the first byte */

	for(i = 0 ; i < stream.m_index ; ++i)
	{
		_groupsNames[i] = stream.m_groupsNames[i];
	}

	return;
}



GroupM_Result GroupM_AddUser (GroupM *_groupM, char *_groupName, char *_address, char* _port)
{
	Group *group = NULL;

	if(NULL == _groupM || NULL == _groupName)
	{
		return GROUPM_UNINITIALIZED_ERROR;
	}

	if(MAP_SUCCESS != HashMap_Find(_groupM->m_groups, _groupName, (void**)&group))
	{
		return GROUPM_GROUP_NOT_EXIST_ERROR;
	}
	
	Group_AddUser(group);

	Group_GetAddress (group, _address);

	Group_GetPort (group, _port);

	return GROUPM_SUCCESS;
}



GroupM_Result GroupM_RemoveUser (GroupM *_groupM, char *_groupName)
{
	Group *group = NULL;
	void *keyItem = NULL, *valueItem = NULL;
	char *address = NULL;
	
	if(NULL == _groupM || NULL == _groupName)
	{
		return GROUPM_UNINITIALIZED_ERROR;
	}

	if(MAP_SUCCESS != HashMap_Find(_groupM->m_groups, _groupName, (void**)&group))
	{
		return GROUPM_GROUP_NOT_EXIST_ERROR;
	}

	if(1 == Group_Size(group)) /* The last user left the group */
	{
		HashMap_Remove(_groupM->m_groups, _groupName, &keyItem, &valueItem);
		address = Group_Destroy(&group);
		if(QUEUE_SUCCESS != Queue_Enqueue(_groupM->m_addressBank, address))
		{
			printf("Debug - Queue_Enqueue failed when group closed\n");
			/* Delete the line above ! */
		}
	}
	else
	{
		Group_RemoveUser(group);
	}

	return GROUPM_SUCCESS;
}

size_t GroupM_numOfGroups (const GroupM *_groupM)
{
	if(NULL == _groupM)
	{
		return 0;
	}

	return HashMap_Size(_groupM->m_groups);	
}

size_t GroupM_UsersInGroup (const GroupM *_groupM, char* _groupName)
{
	Group *group = NULL;
	if(NULL == _groupM || NULL == _groupName)
	{
		return 0;
	}
	if(MAP_SUCCESS != HashMap_Find(_groupM->m_groups, _groupName, (void**)&group))
	{
		return GROUPM_GROUP_NOT_EXIST_ERROR;
	}
	return Group_Size(group);
}


/* ---------- Local Functions ---------- */

static GroupM_Result Fill_AddressesBank(Queue *_addressesBank, size_t _pullSize)
{
	char *buffer, address[ADDRESS_SIZE];
	int num1 = ADDRESS_FIRST_BYTE, num2 = 0, num3 = 0, num4 = 1;
	int i;

	for(i = 0 ; i < _pullSize ; ++i)
	{
		UpdateAddress(address, &num1, &num2, &num3, &num4);
		buffer = (char*)malloc(ADDRESS_SIZE + 1);
		strcpy(buffer, address);

		if(QUEUE_SUCCESS != Queue_Enqueue(_addressesBank , buffer))
		{
			return -1;
		}

	}
	return GROUPM_SUCCESS;
}


static void UpdateAddress(char *_address, int *_num1, int *_num2, int *_num3, int *_num4)
{
	sprintf(_address, "%d.%d.%d.%d" , *_num1, *_num2, *_num3, *_num4);
	if(*_num4 < UCHAR_MAX)
	{
		++(*_num4);
		return;
	}
	else if(*_num3 < UCHAR_MAX)
	{
		*_num4 = 1;
		++(*_num3);
		return;
	}
	else
	{
		*_num4 = 1;
		*_num3 = 0;
		++(*_num2);
		return;
	}
	return;
}




/* ---------- Hash functions ---------- */

 /* make a number from the Group Name */
static size_t HashFunc (const void* _key)
{
	char *groupName = (char*)_key;
	size_t i, len = strlen(groupName), letterSum = 0;

	for(i = 0 ; groupName[i] != '\0' ; ++i)
	{
		letterSum += groupName[i];
	}

	return (len * letterSum);
}


static int GroupEqualityCheck (const void* _firstKey, const void* _secondKey)
{
	return !(strcmp((char*)_firstKey , (char*)_secondKey));
}


static int Check_Status (int status)
{
	switch(status)
	{
		case MAP_SUCCESS:
			return GROUPM_DUPLICATE_ERROR;

		case MAP_ALLOCATION_ERROR:
			return GROUPM_ALLOCATION_ERROR;

		case MAP_KEY_DUPLICATE_ERROR:
			return GROUPM_DUPLICATE_ERROR;

		case MAP_OVERFLOW_ERROR:
			return GROUPM_OVERFLOW_ERROR;

		case MAP_UNINITIALIZED_ERROR:
			return GROUPM_UNINITIALIZED_ERROR;

		default:
			return -1;
	}
}

static void GroupM_GroupDestroy (void* _value)
{
	char *address = NULL;
	Group *group = (Group*)_value;
	address =  Group_Destroy (&group);
	free(address);

	return;
}


static int GroupM_GroupsStream(const void* _key, void* _value, void* _context)
{
	char *name = (char*)_key , *groupsNames = ((Stream*)_context)->m_groupsNames;
	size_t size, index = ((Stream*)_context)->m_index;

	strcpy(&groupsNames[index] , name);

	size = strlen(name) + 1;

	((Stream*)_context)->m_index += size;

	return 1;
}




/* ---------- DeBug functions ---------- */

size_t GroupM_HashSize (const GroupM *_groupM)
{
	return HashMap_Size(_groupM->m_groups);
}

size_t GroupM_HashPrimeSize (const GroupM *_groupM)
{
	return HashMap_HashSize(_groupM->m_groups);
}

size_t GroupM_HashCapacity (const GroupM *_groupM)
{
	return HashMap_Capacity(_groupM->m_groups);
}




