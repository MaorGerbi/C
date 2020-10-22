#include <stdio.h>
#include <string.h>
#include "Group.h"


typedef enum
{
    PASSED = 0,
    FAILED
} Status;


Status Test_Create (void); /* Create Test 1 */
Status Test_Create_Neg (void); /* Create Neg Test 2 */
Status Test_Destroy (void); /* Destroy Test 3 */
Status Test_Destroy_Neg (void); /* Destroy Neg Test 4 */
Status Test_Add_Remove_Size (void); /* Add , Remove and Size Test 5 */
Status Test_Get_Name (void); /* Get_Name Test 6 */
Status Test_Change_Name (void); /* Change_Name Test 7 */


void PrintTest (Status status); /* Print if Test if PASSED or FAILED */



int k;

int main (void)
{
	putchar('\n');
	printf("Create Tests:\n");
	PrintTest(Test_Create());
	PrintTest(Test_Create_Neg());

	putchar('\n');
	printf("Destroy Tests:\n");
	PrintTest(Test_Destroy());
	PrintTest(Test_Destroy_Neg());

	putchar('\n');
	printf("Add & Remove Tests:\n");
	PrintTest(Test_Add_Remove_Size());

	putchar('\n');
	printf("Get_Name Tests:\n");
	PrintTest(Test_Get_Name());

	putchar('\n');
	printf("Change_Name Tests:\n");
	PrintTest(Test_Change_Name());

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
	Group *group = Group_Create("Group1" , "127.0.0.1");
	if(NULL == group)
	{
		return FAILED;
	}
	Group_Destroy(&group);
	return PASSED;
}


Status Test_Create_Neg (void) /* Create Neg Test 2 */
{
	Group *group1 = NULL, *group2 = NULL;
	group1 = Group_Create(NULL , "127.0.0.1");
	group2 = Group_Create("Groupppp" , NULL);
	if(NULL != group1 || NULL != group2)
	{
		return FAILED;
	}
	return PASSED;
}




/* ---------- Destroy Tests ---------- */

Status Test_Destroy (void) /* Destroy Test 3 */
{
	char *addr = NULL;
	Group *group = Group_Create("Group1" , "127.0.0.1");
	addr = Group_Destroy(&group);
	if(strcmp("127.0.0.1" , addr))
	{
		return FAILED;
	}
	return PASSED;
}


Status Test_Destroy_Neg (void) /* Destroy Neg Test 4 */
{
	Group *group = Group_Create("Group1" , "127.0.0.1");
	Group_Destroy(&group);
	Group_Destroy(&group);
	Group_Destroy(NULL);
	return PASSED;
}


/* ---------- Add & Remove Tests ---------- */

Status Test_Add_Remove_Size (void) /* Add , Remove and Size Test 5 */
{
	char *_address;
	Group *group = Group_Create("Group1" , "127.58.22.1");

	if(0 != Group_Size(group))
	{
		return FAILED;
	}

	Group_AddUser(group);
	Group_AddUser(group);
	Group_AddUser(group);
	if(3 != Group_Size(group))
	{
		return FAILED;
	}

	Group_RemoveUser(group);
	if(2 != Group_Size(group))
	{
		return FAILED;
	}

	Group_AddUser(group);
	Group_AddUser(group);
	if(4 != Group_Size(group))
	{
		return FAILED;
	}

	Group_RemoveUser(group);
	Group_RemoveUser(group);
	Group_RemoveUser(group);
	Group_RemoveUser(group);
	if(0 != Group_Size(group))
	{
		return FAILED;
	}

	Group_AddUser(group);
	if(1 != Group_Size(group))
	{
		return FAILED;
	}

	_address = Group_Destroy(&group);

	if(strcmp("127.58.22.1" , _address))
	{
		return FAILED;
	}
	return PASSED;
}





/* ---------- Get_Name Tests ---------- */

Status Test_Get_Name (void) /* Get_Name Test 6 */
{
	char *name = NULL;
	Group *group = Group_Create("Group1" , "127.0.0.1");

	name = Group_GetName(group);

	if(strcmp("Group1" , name))
	{
		return FAILED;
	}

	Group_Destroy(&group);
	return PASSED;
}





/* ---------- Change_Name Tests ---------- */

Status Test_Change_Name (void) /* Change_Name Test 7 */
{
	char *newName;
	Group *group = Group_Create("Group1" , "127.0.0.1");

	Group_ChangeName(group, "Yoooosssssiiiiiii");

	newName = Group_GetName(group);

	if(strcmp("Yoooosssssiiiiiii" , newName))
	{
		return FAILED;
	}

	Group_Destroy(&group);
	return PASSED;
}


