#include <stdio.h>
#include "UserManager.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

#define CAPACITY 10

void CreateTest();
void CreateNULL1();
void CreateNULL2();
void CreateTestNULL3();
void DestoryTest();
void DestoryDubleFreeTest();
void RegisterTest();
void RegisterTestUNINITIALIZED();
void RegisterTestDUPLICATE();
void RegisterTestOVERFLOW();
void LogInTest();
void LogInWrongUserTest();
void LogInWrongPasswordTest();
void DisconnectTest();
void DisconnectTestUNINITIALIZED();
void DisconnectTestUNINITIALIZED2();
void DisconnectTestNOT_FOUND();

int main()
{
	CreateTest();
	CreateNULL1();
	CreateNULL2();
	CreateTestNULL3();
	DestoryTest();
	DestoryDubleFreeTest();
	RegisterTest();
	RegisterTestUNINITIALIZED();
	RegisterTestDUPLICATE();
	RegisterTestOVERFLOW();
	LogInTest();
	LogInWrongUserTest();
	LogInWrongPasswordTest();
	DisconnectTestUNINITIALIZED();
	DisconnectTestUNINITIALIZED2();
	DisconnectTestNOT_FOUND();

	return 0;
}

void CreateTest()
{
	UserM* userM = UserM_Create("TestFile.txt", CAPACITY);
	if(NULL == userM)
	{
		printf(RED "Test for Create, sanity: FAIL\n" RESET);
		return;
	}

	printf(GREEN "Test for Create, sanity: PASS\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void CreateTestNULL3()
{
	UserM* userM = UserM_Create("TestFile.txt", 0);
	if(NULL == userM)
	{
		printf(GREEN "Test for Create, negative: PASS\n" RESET);
		
		return;
	}

	printf(RED "Test for Create, negative: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void CreateNULL1()
{
	UserM* userM = UserM_Create(NULL, CAPACITY);
	if(NULL == userM)
	{
		printf(GREEN "Test for Create, negative: PASS\n" RESET);
		return;
	}

	printf(RED "Test for Create, negative: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void CreateNULL2()
{
	UserM* userM = UserM_Create("notExistFile", CAPACITY);
	if(NULL == userM)
	{
		printf(GREEN "Test for Create, negative: PASS\n" RESET);
		return;
	}

	printf(RED "Test for Create, negative: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void DestoryTest()
{
	UserM* userM = UserM_Create("TestFile.txt", CAPACITY);
	if(NULL == userM)
	{
		printf(RED "Test for Destroy, postive: FAIL\n" RESET);
		return;
	}

	UserM_Destroy(&userM);
	if(NULL == userM)
	{
		printf(GREEN "Test for Destroy, postive: PASS\n" RESET);
		return;
	}

	printf(RED "Test for Destroy, postive: FAIL\n" RESET);
	return;
}

void DestoryDubleFreeTest()
{
	UserM* userM = UserM_Create("TestFile.txt", CAPACITY);
	if(NULL == userM)
	{
		printf(RED "Test for Destroy, limit: FAIL\n" RESET);
		return;
	}
	UserM_Destroy(&userM);
	UserM_Destroy(&userM);
	if(NULL == userM)
	{
		printf(GREEN "Test for Destroy, limit: PASS\n" RESET);
		return;
	}

	printf(RED "Test for Destroy, limit: FAIL\n" RESET);
	return;
}

void RegisterTest()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, CAPACITY);
	if(NULL == userM)
	{
		printf(RED "Test for Register, postive: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_SUCCESS != UserM_Register(userM, "ziv", "123"))
	{
		printf(RED "Test for Register, postive: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}
	if(ERR_M_SUCCESS != UserM_Register(userM, "maor", "456"))
	{
		printf(RED "Test for Register, postive: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(GREEN "Test for Register, postive: PASS\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void RegisterTestUNINITIALIZED()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, CAPACITY);
	if(NULL == userM)
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_UNINITIALIZED != UserM_Register(NULL, "ziv", "123"))
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	if(ERR_M_UNINITIALIZED != UserM_Register(userM, NULL, "123"))
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	if(ERR_M_UNINITIALIZED != UserM_Register(userM, "ziv", NULL))
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}


	printf(GREEN "Test for Register, negative: PASS\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void RegisterTestDUPLICATE()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, CAPACITY);
	if(NULL == userM)
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_SUCCESS != UserM_Register(userM, "ziv", "123"))
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}
	if(ERR_M_USER_ALLREADY_EXISTS != UserM_Register(userM, "ziv", "123"))
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(GREEN "Test for Register, negative: PASS\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void RegisterTestOVERFLOW()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, 1);
	if(NULL == userM)
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_SUCCESS != UserM_Register(userM, "ziv", "123"))
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}
	if(ERR_M_FILE_FULL != UserM_Register(userM, "maor", "134"))
	{
		printf(RED "Test for Register, negative: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(GREEN "Test for Register, negative: PASS\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void LogInTest()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, 1);
	if(NULL == userM)
	{
		printf(RED "Test for Log in, postive: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_SUCCESS != UserM_Register(userM, "ziv", "123"))
	{
		printf(RED "Test for Log in, postive: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	if(ERR_M_SUCCESS == UserM_Login(userM,  "ziv", "123"))
	{
		printf(GREEN "Test for Log in, postive: PASS\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(RED "Test for Log in, postive: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}


void LogInWrongUserTest()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, 1);
	if(NULL == userM)
	{
		printf(RED "Test for Log in, negative: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_USER_NOT_FOUND == UserM_Login(userM,  "ziv", "123"))
	{
		printf(GREEN "Test for Log in, negative: PASS\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(RED "Test for Log in, negative: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void LogInWrongPasswordTest()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, 1);
	if(NULL == userM)
	{
		printf(RED "Test for Log in, negative: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_SUCCESS != UserM_Register(userM, "ziv", "123"))
	{
		printf(RED "Test for Log in, postive: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	if(ERR_M_WRONG_PASSWORD == UserM_Login(userM,  "ziv", "124"))
	{
		printf(GREEN "Test for Log in, negative: PASS\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(RED "Test for Log in, negative: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void DisconnectTest()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, 1);
	if(NULL == userM)
	{
		printf(RED "Test for Log in, negative: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_SUCCESS != UserM_Register(userM, "ziv", "123"))
	{
		printf(RED "Test for disconnect, postive: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	if(ERR_M_SUCCESS != UserM_Login(userM,  "ziv", "123"))
	{
		printf(RED "Test for disconnect, postive: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	if(ERR_M_SUCCESS == UserM_Disconnect(userM, "ziv"))
	{
		printf(GREEN "Test for disconnectn, postive: PASS\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(RED "Test for disconnect, postive: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void DisconnectTestUNINITIALIZED()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, 1);
	if(NULL == userM)
	{
		printf(RED "Test for Log in, negative: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_UNINITIALIZED == UserM_Disconnect(userM, NULL))
	{
		printf(GREEN "Test for disconnectn, negative: PASS\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(RED "Test for disconnect, negative: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void DisconnectTestUNINITIALIZED2()
{
	if(ERR_M_UNINITIALIZED == UserM_Disconnect(NULL, "ziv"))
	{
		printf(GREEN "Test for disconnectn, negative: PASS\n" RESET);
		return;
	}

	printf(RED "Test for disconnect, negative: FAIL\n" RESET);
	return;
}

void DisconnectTestNOT_LOG_IN()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, 1);
	if(NULL == userM)
	{
		printf(RED "Test for disconnect, negative: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_SUCCESS != UserM_Register(userM, "ziv", "123"))
	{
		printf(RED "Test for disconnect, negative: FAIL\n" RESET);
		UserM_Destroy(&userM);
		return;
	}


	if(ERR_M_USER_NOT_LOG_IN == UserM_Disconnect(userM, "ziv"))
	{
		printf(GREEN "Test for disconnectn, negative: PASS\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(RED "Test for disconnect, negative: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}

void DisconnectTestNOT_FOUND()
{
	char fileName[] = "TestFile.txt";
	FILE* file = fopen(fileName, "w");

	UserM* userM = UserM_Create(fileName, 1);
	if(NULL == userM)
	{
		printf(RED "Test for disconnect, negative: FAIL\n" RESET);
		return;
	}

	fclose(file);

	if(ERR_M_USER_NOT_FOUND == UserM_Disconnect(userM, "ziv"))
	{
		printf(GREEN "Test for disconnectn, negative: PASS\n" RESET);
		UserM_Destroy(&userM);
		return;
	}

	printf(RED "Test for disconnect, negative: FAIL\n" RESET);
	UserM_Destroy(&userM);
	return;
}


