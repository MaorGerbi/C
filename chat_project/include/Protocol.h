#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define MAX_BUFFER_SIZE 4000
#define GROUPNAME_SIZE 30
#define IP_ADDRESS_SIZE 16
#define USERNAME_SIZE 30
#define PASSWORD_SIZE 30
#define PORT_SIZE 8

typedef enum Tag
{
/*     Request Tags     */

	REGISTER_REQUEST = 0,   /* Register_Request */
	LOG_IN_REQUEST,         /* Register_Request */

	LOG_OUT_REQUEST,        /* Register_Request */

	OPEN_GROUP_REQUEST,     /* Group_Request */
	JOIN_GROUP_REQUEST,     /* Group_Request */
	LEAVE_GROUP_REQUEST,    /* Group_Request */

	GROUPS_NAMES_REQUEST,   /* Groups_Names_Request */


/*     Response Tags     */

	REGISTER_RESPONSE,      /* Register_Response */
	LOG_IN_RESPONSE,        /* Register_Response */
	LOG_OUT_RESPONSE,       /* Register_Response */

	GROUPS_NAMES_RESPONSE,  /* Group_Names_Response */

	OPEN_GROUP_RESPONSE,    /* Group_Response */
	JOIN_GROUP_RESPONSE,    /* Group_Response */

	LEAVE_GROUP_RESPONSE    /* Leave_Group_Response */
}Tag;


typedef enum Protocol_Result {
	PROTOCOL_SUCESS = 0,
	PROTOCOL_UNINITIZLIZED
} Protocol_Result;



/* ---------- Request Structs ---------- */


/* Struct for Register and Login operations */
typedef struct Register_Request
{
	char m_tag;
	char m_name[USERNAME_SIZE];
	char m_password[PASSWORD_SIZE];
}Register_Request;


/* Struct for Logout operation */
typedef struct Logout_Request
{
	char m_tag;
	char m_name[USERNAME_SIZE];
	char m_groupsNames[MAX_BUFFER_SIZE];
}Logout_Request;


/* Struct for Open Group, Join Group and Leave Group operations */
typedef struct Group_Request
{
	char m_tag;
	char m_groupName[GROUPNAME_SIZE];
}Group_Request;


/* Struct for Groups Names Request (before Join Group operation)*/
typedef struct Groups_Names_Request
{
	char m_tag;
}Groups_Names_Request;





/* ---------- Response Structs ---------- */

/* Struct for Register, Login and Logout operations */
typedef struct Register_Response
{
	char m_tag;
	char m_status; /* accept - 1 , failed - 0 */
}Register_Response;


/* Struct for Open Group and Join Group operations */
typedef struct Group_Response
{
	char m_tag;
	char m_status; /* accept - 1 , failed - 0 */
	char m_ipAddress[IP_ADDRESS_SIZE];
	char m_port[PORT_SIZE];
	char m_groupName[GROUPNAME_SIZE];
}Group_Response;


/* Struct for show all Groups names operation */
typedef struct Group_Names_Response
{
	char m_tag;
	char m_allGroups[MAX_BUFFER_SIZE];
}Group_Names_Response;


/* Struct for Leave Group operations */
typedef struct Leave_Group_Response
{
	char m_tag;
	char m_status; /* accept - 1 , failed - 0 */
	char m_groupName[GROUPNAME_SIZE];
}Leave_Group_Response;







/**
 * @brief The function returns the tag of a spesific package.
 *
 * @param[in] _pack - A pack to be checked by tag.
 *
 * @return _tag - Tag from the enum tag list.
 * @return success or error code
 * @return PROTOCOL_SUCCESS on success
 * @return PROTOCOL_UNINITIZLIZED - _pack or _tag are NULL.
 */
Protocol_Result Protocol_CheckTag(const char* _pack, char *_tag);


/**
 * @brief The function packing the _data structure and put it in the _pack.
 *
 * @param[in] _data - One of the Protocol struct according the choosen tag - filled with the rellevant data.
 *
 * @return _pack - empty buffer to be detailed.
 * @return _size - The package (_pack) size [Bytes].
 * @return success or error code
 * @return PROTOCOL_SUCCESS on success
 * @return PROTOCOL_UNINITIZLIZED - _data, _pack or _size are NULL.
 */
Protocol_Result Protocol_Pack(const void* _data, char* _pack, size_t *_size);


/**
 * @brief The function unpacking a pack that packed in Protocol_Pack.
 *
 * @param[in] _pack - A pack to be unpacked.
 *
 * @return success or error code
 * @return PROTOCOL_SUCCESS on success
 * @return PROTOCOL_UNINITIZLIZED - _pack, _tag or _msg are NULL.
 * @return _msg - A struct from the struct list above (accodring _tag)
 */
Protocol_Result Protocol_Unpack(const char* _pack, void* _msg); /* msg = struct */



#endif /* __PROTOCOL_H__ */
