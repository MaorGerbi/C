#include <stdio.h>
#include <string.h>
#include "Protocol.h"



static size_t Pack_Register_Request (const void* _data, char* _pack);
static size_t Pack_Logout_Request (const void* _data, char* _pack);
static size_t Pack_Group_Request (const void* _data, char* _pack);
static size_t Pack_Group_Names_Request (const void* _data, char* _pack);

static size_t Pack_Register_Response (const void* _data, char* _pack);
static size_t Pack_Group_Response (const void* _data, char* _pack);
static size_t Pack_Group_Names_Response (const void* _data, char* _pack); /* To improve ! */
static size_t Pack_Leave_Group_Response (const void* _data, char* _pack);



static void Unpack_Register_Request (void* _data, const char* _pack);
static void Unpack_Logout_Request(void* _data, const char* _pack);
static void Unpack_Group_Request (void* _data, const char* _pack);
static void Unpack_Group_Names_Request (void* _data, const char* _pack);

static void Unpack_Register_Response (void* _data, const char* _pack);
static void Unpack_Group_Response (void* _data, const char* _pack);
static void Unpack_Group_Names_Response (void* _data, const char* _pack); /* To improve ! */
static void Unpack_Leave_Group_Response (void* _data, const char* _pack);





Protocol_Result Protocol_CheckTag(const char* _pack, char *_tag)
{
	if(NULL == _pack)
	{
		return PROTOCOL_UNINITIZLIZED;
	}
	*_tag = _pack[0];
	return PROTOCOL_SUCESS;
}



Protocol_Result Protocol_Pack(const void* _data, char* _pack, size_t *_size)
{
	if(NULL == _data || NULL == _pack || NULL == _size)
	{
		return PROTOCOL_UNINITIZLIZED;
	}


	/*  Request Structures */

	if( ((char*)_data)[0] <= LOG_IN_REQUEST ) /* Register and Login - Request */
	{
		*_size = Pack_Register_Request(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( ((char*)_data)[0] <= LOG_OUT_REQUEST ) /* Logout - Request */
	{
		*_size = Pack_Logout_Request(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( ((char*)_data)[0] <= LEAVE_GROUP_REQUEST ) /* Open Group, Join Group and Leave Group - Request */
	{
		*_size = Pack_Group_Request(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( ((char*)_data)[0] <= GROUPS_NAMES_REQUEST ) /* Get Groups Names - Request */
	{
		*_size = Pack_Group_Names_Request(_data, _pack);
		return PROTOCOL_SUCESS;
	}



	/*  Response Structures */

	if( ((char*)_data)[0] <= LOG_OUT_RESPONSE ) /* Register, Login and Logout - Response */
	{
		*_size = Pack_Register_Response(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( ((char*)_data)[0] <= GROUPS_NAMES_RESPONSE ) /* Get Groups Names - Response */
	{
		*_size = Pack_Group_Names_Response(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( ((char*)_data)[0] <= JOIN_GROUP_RESPONSE ) /* Open Group and Join Group - Response */
	{
		*_size = Pack_Group_Response(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( ((char*)_data)[0] <= LEAVE_GROUP_RESPONSE ) /* Leave Group - Response */
	{
		*_size = Pack_Leave_Group_Response(_data, _pack);
		return PROTOCOL_SUCESS;
	}

	return PROTOCOL_SUCESS;
}





Protocol_Result Protocol_Unpack(const char* _pack, void* _data)
{
	if(NULL == _pack || NULL == _data || _pack[0] < 0)
	{
		return PROTOCOL_UNINITIZLIZED;
	}

	/*  Request Structures */

	if( _pack[0] <= LOG_IN_REQUEST ) /* Register and Login - Request */
	{
		Unpack_Register_Request(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( _pack[0] <= LOG_OUT_REQUEST ) /* Logout - Request */
	{
		Unpack_Logout_Request(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( _pack[0] <= LEAVE_GROUP_REQUEST ) /* Open Group, Join Group and Leave Group - Request */
	{
		Unpack_Group_Request(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( _pack[0] <= GROUPS_NAMES_REQUEST ) /* Get Groups Names - Request */
	{
		Unpack_Group_Names_Request(_data, _pack);
		return PROTOCOL_SUCESS;
	}


	/*  Response Structures */

	if( _pack[0] <= LOG_OUT_RESPONSE ) /* Register, Login and Logout - Response */
	{
		Unpack_Register_Response(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( _pack[0] <= GROUPS_NAMES_RESPONSE ) /* Get Groups Names - Response */
	{
		Unpack_Group_Names_Response(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( _pack[0] <= JOIN_GROUP_RESPONSE ) /* Open Group and Join Group - Response */
	{
		Unpack_Group_Response(_data, _pack);
		return PROTOCOL_SUCESS;
	}
	if( _pack[0] <= LEAVE_GROUP_RESPONSE ) /* Leave Group - Response */
	{
		Unpack_Leave_Group_Response(_data, _pack);
		return PROTOCOL_SUCESS;
	}

	return PROTOCOL_SUCESS;
}






/* --------------- Pack Functions --------------- */


/* ----- Request Functions ----- */

static size_t Pack_Register_Request (const void* _data, char* _pack)
{
	size_t i = 2, size;
	Register_Request *reg = (Register_Request*)_data;

	_pack[0] = reg->m_tag;
	_pack[1] = '\0';

	size = strlen(reg->m_name) + 1;
	memcpy(&_pack[i], reg->m_name, size);
	i += size;

	size = strlen(reg->m_password) + 1;
	memcpy(&_pack[i], reg->m_password, size);
	i += size;

	return i;
}


static size_t Pack_Logout_Request (const void* _data, char* _pack)
{
	size_t i = 2, size;
	Logout_Request *logout = (Logout_Request*)_data;

	_pack[0] = logout->m_tag;
	_pack[1] = '\0';

	size = strlen(logout->m_name) + 1;
	memcpy(&_pack[i], logout->m_name, size);
	i += size;

	memcpy(&_pack[i], logout->m_groupsNames, MAX_BUFFER_SIZE);
	i += MAX_BUFFER_SIZE;

	return i;
}



static size_t Pack_Group_Request (const void* _data, char* _pack)
{
	size_t i = 2, size;
	Group_Request *group = (Group_Request*)_data;

	_pack[0] = group->m_tag;
	_pack[1] = '\0';

	size = strlen(group->m_groupName) + 1;

	memcpy(&_pack[i], group->m_groupName, size);
	i += size;

	return i;
}


static size_t Pack_Group_Names_Request (const void* _data, char* _pack)
{
	Groups_Names_Request *group = (Groups_Names_Request*)_data;

	_pack[0] = group->m_tag;
	_pack[1] = '\0';

	return 2;
}




/* ----- Response Functions ----- */

static size_t Pack_Register_Response (const void* _data, char* _pack)
{
	_pack[0] = ((Register_Response*)_data)->m_tag;
	_pack[1] = '\0';
	_pack[2] = ((Register_Response*)_data)->m_status;
	
	return 3;
}


static size_t Pack_Group_Response (const void* _data, char* _pack)
{
	size_t i = 3, size;
	Group_Response *group = (Group_Response*)_data;

	_pack[0] = group->m_tag;
	_pack[1] = group->m_status;
	_pack[2] = '\0';

	size = strlen(group->m_ipAddress) + 1;
	memcpy(&_pack[i], group->m_ipAddress, size);
	i += size;

	size = strlen(group->m_port) + 1;
	memcpy(&_pack[i], group->m_port, size);
	i += size;

	size = strlen(group->m_groupName) + 1;
	memcpy(&_pack[i], group->m_groupName, size);
	i += size;

	return i;
}


static size_t Pack_Group_Names_Response (const void* _data, char* _pack)
{
	Group_Names_Response *group = (Group_Names_Response*)_data;

	_pack[0] = group->m_tag;
	_pack[1] = '\0';

	memcpy(&_pack[2], group->m_allGroups, MAX_BUFFER_SIZE);

	return MAX_BUFFER_SIZE + 2;
}


static size_t Pack_Leave_Group_Response (const void* _data, char* _pack)
{
	Leave_Group_Response *group = (Leave_Group_Response*)_data;
	size_t size;

	_pack[0] = group->m_tag;
	_pack[1] = '\0';
	_pack[2] = group->m_status;

	size = strlen(group->m_groupName) + 1;

	strcpy(&_pack[3] , group->m_groupName);

	return size + 3;
}



/* --------------- Unpack Functions --------------- */

/* ----- Request Functions ----- */

static void Unpack_Register_Request (void* _data, const char* _pack)
{
	size_t i = 2;
	Register_Request *reg = (Register_Request*)_data;

	reg->m_tag = _pack[0];

	strcpy(reg->m_name, &_pack[i]);
	i += strlen(reg->m_name) + 1;

	strcpy(reg->m_password, &_pack[i]);
	i += strlen(reg->m_password) + 1;

	return;
}


static void Unpack_Logout_Request(void* _data, const char* _pack)
{
	size_t i = 2;
	Logout_Request *logout = (Logout_Request*)_data;

	logout->m_tag = _pack[0];

	strcpy(logout->m_name, &_pack[i]);
	i += strlen(logout->m_name) + 1;

	memcpy(logout->m_groupsNames, &_pack[i], MAX_BUFFER_SIZE);

	return;
}


static void Unpack_Group_Request (void* _data, const char* _pack)
{
	size_t i = 2;
	Group_Request *group = (Group_Request*)_data;

	group->m_tag = _pack[0];

	strcpy(group->m_groupName, &_pack[i]);

	return;
}


static void Unpack_Group_Names_Request (void* _data, const char* _pack)
{
	((Groups_Names_Request*)_data)->m_tag = _pack[0];
	return;
}


/* ----- Response Functions ----- */

static void Unpack_Register_Response (void* _data, const char* _pack)
{
	((Register_Response*)_data)->m_tag = _pack[0];
	((Register_Response*)_data)->m_status = _pack[2];
	return;
}


static void Unpack_Group_Response (void* _data, const char* _pack)
{
	size_t i = 3;
	Group_Response *group = (Group_Response*)_data;
	group->m_tag = _pack[0];
	group->m_status = _pack[1];

	strcpy(group->m_ipAddress, &_pack[i]);
	i += strlen(group->m_ipAddress) + 1;

	strcpy(group->m_port, &_pack[i]);
	i += strlen(group->m_port) + 1;

	strcpy(group->m_groupName, &_pack[i]);
	i += strlen(group->m_groupName) + 1;

	return;
}


static void Unpack_Group_Names_Response (void* _data, const char* _pack)
{
	Group_Names_Response *group = (Group_Names_Response*)_data;
	group->m_tag = _pack[0];

	memcpy(group->m_allGroups, &_pack[2], MAX_BUFFER_SIZE);

	return;
}


static void Unpack_Leave_Group_Response (void* _data, const char* _pack)
{
	Leave_Group_Response *group = (Leave_Group_Response*)_data;

	group->m_tag = _pack[0];
	group->m_status = _pack[2];
	strcpy(group->m_groupName , &_pack[3]);
	return;
}


