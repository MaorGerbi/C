#include <stdio.h>
#include <string.h>
#include "GroupM.h"
#include "Group.h"
#include "GenQueue.h"
typedef enum
{
    PASSED = 0,
    FAILED
} Status;


Status Test_Create (void); /* Create Test 1 */
Status Test_Destroy (void); /* Destroy Test 2 */
Status Test_Open_Group (void); /* Open Group Test 3 */
Status Test_Get_All_Groups (void); /* GetAllGroups Test 4 */
Status Test_Add_User (void); /* Add User Test 5 */
Status Test_Remove_User (void); /* Remove User Test 6 */


void PrintTest (Status status); /* Print if Test if PASSED or FAILED */


int k;

int main (void)
{
	putchar('\n');
	printf("Create Tests:\n");
	PrintTest(Test_Create());

	putchar('\n');
	printf("Destroy Tests:\n");
	PrintTest(Test_Destroy());

	putchar('\n');
	printf("Open Group Tests:\n");
	PrintTest(Test_Open_Group());

	putchar('\n');
	printf("Get All Groups Tests:\n");
	PrintTest(Test_Get_All_Groups());

	putchar('\n');
	printf("Add User Tests:\n");
	PrintTest(Test_Add_User());

	putchar('\n');
	printf("Remove User Tests:\n");
	PrintTest(Test_Remove_User());


	return 0;
}





/* ---------- Print Function ---------- */

void PrintTest (Status status) /* Print if Test if PASSED or FAILED */
{
	if(PASSED == status)
	{
		printf("Test %d PASSED \n" , ++k);
	}
	else
	{
		printf("Test %d FAILED \n" , ++k);
	}
	return;
}




/* ---------- Create Tests ---------- */

Status Test_Create (void) /* Create Test 1 */
{
	int numOfGroups = 200;
	GroupM *groupM = GroupM_Create(numOfGroups);
	if(NULL == groupM)
	{
		return FAILED;
	}
	GroupM_Destroy(&groupM);
	return PASSED;
}



/* ---------- Destroy Tests ---------- */

Status Test_Destroy (void) /* Destroy Test 2 */
{
	int numOfGroups = 200;
	GroupM *groupM = GroupM_Create(numOfGroups);
	GroupM_Destroy(&groupM);
	if(NULL != groupM)
	{
		return FAILED;
	}
	GroupM_Destroy(&groupM);
	return PASSED;
}


/* ---------- Open Group Tests ---------- */

Status Test_Open_Group (void) /* Open Group Test 3 */
{
	int numOfGroups = 1000;
	char port [10], address[16];
	GroupM *groupM = GroupM_Create(numOfGroups);

	if(GROUPM_SUCCESS != GroupM_OpenGroup (groupM, "ZivMaorAsaf" , address, port))
	{
		return FAILED;
	}

	if(1 != GroupM_UsersInGroup(groupM, "ZivMaorAsaf"))
	{
		return FAILED;
	}

	if(GROUPM_DUPLICATE_ERROR != GroupM_OpenGroup (groupM, "ZivMaorAsaf", address, port))
	{
		return FAILED;
	}

	if(GROUPM_SUCCESS != GroupM_OpenGroup (groupM, "Team3", address, port))
	{
		return FAILED;
	}

	if(GROUPM_DUPLICATE_ERROR != GroupM_OpenGroup (groupM, "Team3", address, port))
	{
		return FAILED;
	}

	GroupM_Destroy(&groupM);

	return PASSED;
}


/* ---------- Get All Groups Tests ---------- */

Status Test_Get_All_Groups (void) /* GetAllGroups Test 4 */
{
	int groupAmount;
	int numOfGroups = 1000;
	char port [10], address[16];
	char groupStream[4096];
	GroupM *groupM = GroupM_Create(numOfGroups);

	GroupM_OpenGroup (groupM, "zzzz" , address, port);
	GroupM_OpenGroup (groupM, "mmmm" , address, port);
	GroupM_OpenGroup (groupM, "aaaa" , address, port);
	GroupM_OpenGroup (groupM, "bbbb" , address, port);

	GroupM_GetAllGroups (groupM, groupStream);

	if(4 != (groupAmount = groupStream[0]))
	{
		return FAILED;
	}
	if( strcmp("aaaa" , &groupStream[2]) || strcmp("bbbb" , &groupStream[7]) || strcmp("mmmm" , &groupStream[12]) || strcmp("zzzz" , &groupStream[17]) )
	{
		return FAILED;
	}

	GroupM_Destroy(&groupM);

	return PASSED;
}


/* ---------- Add User Tests ---------- */

Status Test_Add_User (void) /* Add User Test 5 */
{
	int numOfGroups = 1000;
	char port [10], address[16];
	GroupM *groupM = GroupM_Create(numOfGroups);

	GroupM_OpenGroup (groupM, "Ziv" , address, port);

	GroupM_AddUser(groupM ,"Ziv", address, port);
	GroupM_AddUser(groupM ,"Ziv", address, port);
	GroupM_AddUser(groupM ,"Ziv", address, port);
	GroupM_AddUser(groupM ,"Ziv", address, port);

	if( strcmp("225.0.0.1" , address) || strcmp("5000" , port))
	{
		return FAILED;
	}

	if(5 != GroupM_UsersInGroup(groupM, "Ziv"))
	{
		return FAILED;
	}

	GroupM_Destroy(&groupM);

	return PASSED;
}


/* ---------- Remove User Tests ---------- */

Status Test_Remove_User (void) /* Remove User Test 6 */
{
	int numOfGroups = 1000;
	char port [10], address[16];
	GroupM *groupM = GroupM_Create(numOfGroups);

	GroupM_OpenGroup (groupM, "Ziv" , address, port);

	GroupM_AddUser(groupM ,"Ziv", address, port);
	GroupM_AddUser(groupM ,"Ziv", address, port);
	GroupM_AddUser(groupM ,"Ziv", address, port);
	GroupM_AddUser(groupM ,"Ziv", address, port);

	if(5 != GroupM_UsersInGroup(groupM, "Ziv"))
	{
		return FAILED;
	}

	if(1 != GroupM_numOfGroups(groupM))
	{
		return FAILED;
	}

	GroupM_RemoveUser(groupM ,"Ziv");
	GroupM_RemoveUser(groupM ,"Ziv");

	if(3 != GroupM_UsersInGroup(groupM, "Ziv"))
	{
		return FAILED;
	}

	GroupM_RemoveUser(groupM ,"Ziv");
	GroupM_RemoveUser(groupM ,"Ziv");

	if(1 != GroupM_UsersInGroup(groupM, "Ziv"))
	{
		return FAILED;
	}

	if(1 != GroupM_numOfGroups(groupM))
	{
		return FAILED;
	}

	GroupM_RemoveUser(groupM ,"Ziv");

	if(0 != GroupM_numOfGroups(groupM))
	{
		return FAILED;
	}

	GroupM_Destroy(&groupM);

	return PASSED;
}







