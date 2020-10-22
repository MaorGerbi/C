#include <stdio.h>
#include "Queue.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

typedef enum Status{ERR, OK} Status;

void Test_Print(Status status)
{
	status ? printf(GRN"\nPASS!\n"RESET) : printf(RED"\nFAILED\n"RESET);
}

void Test_QueueCreate()
{
	Queue* queue = NULL;
	
	printf("Test_QueueCreate");
	
	queue = Queue_Create(20);
	queue ? Test_Print(OK) : Test_Print(ERR);
	
	queue = Queue_Create(1);
	!queue ? Test_Print(OK) : Test_Print(ERR);
}

void Test_QueueDestroy()
{
	Queue* queue = NULL;
	
	printf("Test_QueueDestroy");
	
	queue = Queue_Create(20);
	Queue_Destroy(&queue, NULL);
	!queue ? Test_Print(OK) : Test_Print(ERR);
	
	Queue_Destroy(&queue, NULL);
	!queue ? Test_Print(OK) : Test_Print(ERR);
}	
void Test_QueueEnqueue()
{
	Queue* queue = NULL;
	int num;
	int status;
	
	printf("Test_QueueEnqueue\n");
	
	queue = Queue_Create(2);
	status = Queue_Enqueue(queue, (void*)&num);
	status == QUEUE_SUCCESS ? Test_Print(OK) : Test_Print(ERR);
	
	status = Queue_Enqueue(queue, NULL);
	status == QUEUE_INVALID_ARGUMENT ? Test_Print(OK) : Test_Print(ERR);

	
	status = Queue_Enqueue(NULL, (void*)&num);
	status == QUEUE_UNINITIALIZED_ERROR ? Test_Print(OK) : Test_Print(ERR);
	
	status = Queue_Enqueue(NULL, (void*)&num);
	status = Queue_Enqueue(queue, (void*)&num);
	status == QUEUE_OVERFLOW ? Test_Print(OK) : Test_Print(ERR);
	
}

void Test_QueueDequeue()
{
	Queue* queue = NULL;
	int num = 5, status;
	void* item = NULL;
	int* value;
	
	printf("Test_QueueDequqe\n");

	queue = Queue_Create(2);
	Queue_Enqueue(queue, (void*)&num);	
	Queue_Dequeue(queue, &item);
	value = (int*)item;
	*value == 5 ? Test_Print(OK) : Test_Print(ERR);
	
	status = Queue_Dequeue(NULL, &item);
	status == QUEUE_UNINITIALIZED_ERROR ? Test_Print(OK) : Test_Print(ERR);
	
	status = Queue_Dequeue(queue, NULL);
	status == QUEUE_INVALID_ARGUMENT ? Test_Print(OK) : Test_Print(ERR);

	status = Queue_Dequeue(queue,&item);
	status == QUEUE_UNDERFLOW ? Test_Print(OK) : Test_Print(ERR);	
	
}

void Test_QueueIsEmpty()
{
    Queue* queue = NULL;
    int res, num;
    
	printf("Test_QueueIsEmpty\n");

	queue = Queue_Create(2);
	res = Queue_IsEmpty(queue);
	res ? Test_Print(OK) : Test_Print(ERR);
	
	Queue_Enqueue(queue, (void*)&num);
	res = Queue_IsEmpty(queue);
	!res ? Test_Print(OK) : Test_Print(ERR);
}
void Test_QueueIsFull()
{
    Queue* queue = NULL;
    int res, num;
    
	printf("Test_QueueIsFull\n");

	queue = Queue_Create(2);
	res = Queue_IsFull(queue);
	!res ? Test_Print(OK) : Test_Print(ERR);
	
	Queue_Enqueue(queue, (void*)&num);
	Queue_Enqueue(queue, (void*)&num);
	res = Queue_IsFull(queue);
	res ? Test_Print(OK) : Test_Print(ERR);
} 
int main()
{
	Test_QueueCreate();
	Test_QueueDestroy();
	Test_QueueEnqueue();
    Test_QueueDequeue();
    Test_QueueIsEmpty();
    Test_QueueIsFull();

	return 0;
}
