#include "../include/Vector.h"
#include "Stack.h"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

typedef enum Status {
	ERR,
	OK
	}Status;
	
void Test_Print(Status status)
{
	status ? printf(GRN"\nPASS!\n"RESET) : printf(RED"\nFAILED\n"RESET);
}

void Test_StackCreate()
{
	Stack* stack = NULL;
	
	printf("Test_StackCreate: ");
	stack = StackCreate(2,4);
	stack ?  Test_Print(OK): Test_Print(ERR);
	
    stack = StackCreate(0,0);
	stack ?  Test_Print(ERR): Test_Print(OK);
	
	stack = StackCreate(0,4);
	stack ?  Test_Print(OK): Test_Print(ERR);
}

void Test_StackDestroy()
{
	Stack* stack = NULL;
	
	printf("Test_StackDestroy ");
	stack = StackCreate(2,4);
	
	StackDestroy(stack);
	StackDestroy(stack);
	Test_Print(OK);
}
void Test_StackPush()
{
	Stack* stack = NULL;
	int value, status;
	printf("Test_StackPush \n");
	
	stack = StackCreate(2,4);
	StackPush(stack,2);
	StackTop(stack,&value);
	value == 2 ?  Test_Print(OK): Test_Print(ERR);
	StackDestroy(stack);

	status = StackPush(NULL ,3);
	status == ERR_NOT_INITIALIZED ?  Test_Print(OK): Test_Print(ERR);
	StackDestroy(stack);
	
	stack = StackCreate(1,0);
	StackPush(stack,2);
	status = StackPush(stack,2);
	status == ERR_OVERFLOW ?  Test_Print(OK): Test_Print(ERR);
}

void Test_StackTop()
{	
	Stack* stack = NULL;
	int value, status;
	printf("Test_StackTop \n");
	
	stack = StackCreate(2,4);
	StackPush(stack,2);
	StackTop(stack,&value);
	value == 2 ?  Test_Print(OK): Test_Print(ERR);
	StackDestroy(stack);
	
	stack = StackCreate(2,4);
	status = StackTop(NULL ,&value);
	status == ERR_NOT_INITIALIZED ?  Test_Print(OK): Test_Print(ERR);
	StackDestroy(stack);
}	

void Test_StackPop()
{
	Stack* stack = NULL;
	int value, status;
	printf("Test_StackPop \n");
	
	stack = StackCreate(2,4);
	StackPush(stack,2);
	StackPop(stack, &value);
	value == 2 ?  Test_Print(OK): Test_Print(ERR);
	StackDestroy(stack);
	
    stack = StackCreate(2,4);
	status = StackPop(NULL , &value);
	status == ERR_NOT_INITIALIZED ?  Test_Print(OK): Test_Print(ERR);
	StackDestroy(stack);
	
    stack = StackCreate(2,4);
	status = StackPop(stack , &value);
	status == ERR_UNDERFLOW ?  Test_Print(OK): Test_Print(ERR);
	StackDestroy(stack);	
}

void Test_StackIsEmpty()
{
	Stack* stack = NULL;
	int value, status;
	printf("Test_StackIsEmpty \n");
	
	stack = StackCreate(2,4);
	StackPush(stack,2);
	StackIsEmpty(stack) ?  Test_Print(ERR): Test_Print(OK);
	StackDestroy(stack);
	
	stack = StackCreate(2,4);
	StackIsEmpty(stack) ?  Test_Print(OK): Test_Print(ERR);
	StackDestroy(stack);
	
	stack = StackCreate(2,4);
	StackIsEmpty(NULL) ?  Test_Print(OK): Test_Print(ERR);
	StackDestroy(stack);
}
	
int main()
{
	Test_StackCreate();
	Test_StackDestroy();
	Test_StackPush();
	Test_StackTop();
	Test_StackPop();
	Test_StackIsEmpty();
	
	return 0;
}
