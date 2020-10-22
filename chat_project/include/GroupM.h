#ifndef __GROUPM_H__
#define __GROUPM_H__

#include <sys/types.h> /* size_t */

typedef enum GroupM_Result {
	GROUPM_SUCCESS = 0 ,
	GROUPM_UNINITIALIZED_ERROR,
	GROUPM_ALLOCATION_ERROR,
	GROUPM_DUPLICATE_ERROR,
	GROUPM_GROUP_NOT_EXIST_ERROR,
	GROUPM_UNDERFLOW_ERROR,
	GROUPM_OVERFLOW_ERROR
} GroupM_Result;


typedef struct GroupM GroupM;



/**
 * @brief Function dynamically creates a new GroupM (Group Manager) ADT of a given expected amount of groups.
 *
 * @param[in] _numOfGroups - Amount of groups.
 *
 * @return GroupM* on success / NULL on fail
 */
GroupM* GroupM_Create (size_t _numOfGroups);



/**
 * @brief Dynamically deallocates a previously allocated Group.
 *
 * @params[in] _groupM - A pointer to previously created GroupM returned via GroupM_Create.
 *
 * @return (void).
 */
void GroupM_Destroy (GroupM **_groupM);



/**
 * @brief The function open a new Group, 
 *
 * @param[in] _groupM - a GroupM to open a new group.
 * @param[in] groupName - a name for the new group.
 *
 * @return _address - the address of the new group.
 * @return _port - the port of the new group.
 * @return success or error code
 * @return GROUPM_SUCCESS on success
 * @return GROUPM_UNINITIALIZED_ERROR when one or more of the input arguments are NULL.
 * @return GROUPM_ALLOCATION_ERROR when no memory available.
 * @return GROUPM_OVERFLOW_ERROR when the GroupM is full.
 * @return GROUPM_DUPLICATE_ERROR when Group with the same name is already exist.
 */
GroupM_Result GroupM_OpenGroup (GroupM *_groupM, char *groupName, char *_address, char *_port);



/**
 * @brief The function add a user to exist group, 
 *
 * @param[in] _groupM - a GroupM to be updated.
 * @param[in] groupName - name of the group to be increased.
 *
 * @return success or error code
 * @return GROUPM_SUCCESS on success
 * @return GROUPM_UNINITIALIZED_ERROR when one or more of the input arguments are NULL.
 * @return GROUPM_GROUP_NOT_EXIST_ERROR when Group with the given name is not exist.
 */
GroupM_Result GroupM_AddUser (GroupM *_groupM, char *_groupName, char *_address, char* _port);



/**
 * @brief The function remove a user from exist group, 
 *
 * @param[in] _groupM - a GroupM to be updated.
 * @param[in] groupName - name of the group to be decreased.
 *
 * @return success or error code
 * @return GROUPM_SUCCESS on success
 * @return GROUPM_UNINITIALIZED_ERROR when one or more of the input arguments are NULL.
 * @return GROUPM_GROUP_NOT_EXIST_ERROR when Group with the given name is not exist.
 */
GroupM_Result GroupM_RemoveUser (GroupM *_groupM, char *_groupName);


/**
 * @brief The function return all the groups names in a given string (_groupNames). The first byte in the string equal to the number of groups, and then all the groups names(with '\0' between them). 
 *
 * @param[in] _groupM - a GroupM to use.
 *
 * @return char* - The Groups names stream.
 */
void GroupM_GetAllGroups (GroupM *_groupM, char *_groupsNames);


/**
 * @brief Return the actual number of groups currently in the GroupM.
 *
 * @param[in] _groupM - GroupM to use.
 *
 * @return number of groups on success, 0 if GroupM is empty or invalid
 */
size_t GroupM_numOfGroups (const GroupM *_groupM);


/**
 * @brief Return the actual number of groups currently in the GroupM.
 *
 * @param[in] _groupM - GroupM to use.
 * @param[in] _groupName - Group name to check.
 *
 * @return number of users in the group (according the group name).
 */
size_t GroupM_UsersInGroup (const GroupM *_groupM, char* _groupName);



/* For Debug only */
size_t GroupM_HashSize (const GroupM *_groupM);
size_t GroupM_HashPrimeSize (const GroupM *_groupM);
size_t GroupM_HashCapacity (const GroupM *_groupM);
/* For Debug only */



#endif /* _GROUPM_H__ */
