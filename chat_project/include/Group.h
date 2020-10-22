#ifndef _GROUP_H__
#define _GROUP_H__

#include <sys/types.h> /* size_t */

typedef struct Group Group;

#define ADRRESS_SIZE 25


/**
 * @brief Function dynamically creates a new Group ADT of a given group name and address.
 *
 * @param[in] _groupName - Group name.
 * @param[in] _adrress - Group IP Address.
 *
 * @return Group* on success / NULL on fail
 */
Group* Group_Create (char *_groupName, char *_adrress);


/**
 * @brief Dynamically deallocates a previously allocated Group.
 *
 * @params[in] _group - A pointer to previously created Group returned via Group_Create
 *
 * @return char* - The Group address.
 */
char* Group_Destroy (Group **_group);


/**
 * @brief Increase the number of users in a group.
 *
 * @param[in] _group to be enlarge.
 */
void Group_AddUser (Group *_group);


/**
 * @brief Decrease the number of users in a group.
 *
 * @param[in] _group to be reduced.
 */
void Group_RemoveUser (Group *_group);


/**
 * @brief Return the actual number of users currently in the Group.
 *
 * @param[in]	_group - Group to use.
 *
 * @return number of users on success, 0 if Group is empty or invalid
 */
size_t Group_Size (const Group *_group);


/**
 * @brief Return the name of the group.
 *
 * @param[in] _group - Group to use.
 *
 * @return _groupName - The group name is returned in the string (string size should be at least as Group Name size).
 */
char* Group_GetName (const Group *_group);


/**
 * @brief Change the group name.
 *
 * @param[in]	_group - Group to use.
 * @param[in]	_newName - New name for the group.
 */
void Group_ChangeName (Group *_group, const char *_newName);


void Group_GetAddress (const Group *_group, char *_groupAddress);


void Group_GetPort (const Group *_group, char *_groupPort);


#endif /* _GROUP_H__ */


