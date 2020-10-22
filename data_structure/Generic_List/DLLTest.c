#include <stdio.h>
#include <string.h>
#include <stdlib.h>/*mallo*/
#include "DLL.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"
#define OK 1
#define ERR 0
typedef int Status;


typedef struct Person{
    char name[20];
	int id;
	int age;
    }Person; 
        
Person *person[3];

void Person_Destroy(void* _person)
{
	free((Person*)_person);
}

void Person_Print(void* _person)
{
	Person* p;
	p = (Person*)_person;
	
	printf("name: %s\n, id: %d, age: %d--->>>\n",p->name,p->id,p->age);	
}   
static void Print_Test(Status _status)
{
	_status ? printf(GRN "PASS\n"RESET): printf(RED "FAILED\n" RESET);
}

Status CheckList_Create()
{
	if(NULL == List_Create())
	{
		return ERR;
	}
	
	return OK;
}

void CheckList_Destroy()
{
	List* listPtr = NULL;
    listPtr = List_Create();
    List_PushHead(listPtr,(void*)person[0]);
	List_PushHead(listPtr,(void*)person[1]);
	List_PushHead(listPtr,(void*)person[2]);	
    List_Destroy(&listPtr, &Person_Destroy);
    Print_Test(OK);
    List_Destroy(&listPtr, &Person_Destroy);
    Print_Test(OK);
}

Status CheckListCountItems()
{
    Status status;
	List* listPtr = NULL;
    listPtr = List_Create();
    	
    List_PushHead(listPtr,(void*)person[0]);
	List_PushHead(listPtr,(void*)person[1]);
	List_PushHead(listPtr,(void*)person[2]);

	
	status = (3 == List_Size(listPtr)) ? OK: ERR;
	Print_Test(status);
	
	status = (0 == List_Size(NULL)) ? OK: ERR;
	Print_Test(status);
	List_Destroy(&listPtr, &Person_Destroy);
	return status;
}

void CheckListPushHead()
{
	List* listPtr = NULL;
	int i, sizeList;
	void* p= NULL;
	Status status = OK;
    listPtr = List_Create();
    
    List_PushHead(listPtr,(void*)person[2]);
	List_PushHead(listPtr,(void*)person[1]);
	List_PushHead(listPtr,(void*)person[0]);
   
	sizeList = List_Size(listPtr);	
	
	for(i = 0; i < sizeList; i++)
	{
	    List_PopHead(listPtr, &p);
	    
		if(((Person*)p)->id != person[i]->id)
		{
			status = ERR;
		}
	}
	Print_Test(status);
	
	if(LIST_UNINITIALIZED_ERROR == List_PushHead(NULL, (void*)person[2]))
	{
		status = OK;
	}
	else
	{
		status = ERR;
	}
	Print_Test(status);
}

void CheckListPushTail()
{
	List* listPtr = NULL;
	int i, sizeList;
	void* p= NULL;
	Status status = OK;
    listPtr = List_Create();
    
    List_PushTail(listPtr,(void*)person[0]);
	List_PushTail(listPtr,(void*)person[1]);
	List_PushTail(listPtr,(void*)person[2]);
    List_Print(listPtr,Person_Print);
	sizeList = List_Size(listPtr);	
	
	for(i = 0; i < sizeList; i++)
	{
	    List_PopHead(listPtr, &p);
	    
		if(((Person*)p)->id != person[i]->id)
		{
			status = ERR;
		}
	}
	Print_Test(status);
	
	if(LIST_UNINITIALIZED_ERROR == List_PushTail(NULL, (void*)person[2]))
	{
		status = OK;
	}
	else
	{
		status = ERR;
	}
	Print_Test(status);
}

void CheckListPopHead()
{
    void* p = NULL;
	List* listPtr = NULL;
	Status status = OK;
	
    listPtr = List_Create();
    if(LIST_UNDERFLOW_ERROR == List_PopHead(listPtr, &p))
    {
    	status = OK;
    }
    else
    {
    	status = ERR;
    }
	Print_Test(status);
	
	if(LIST_UNDERFLOW_ERROR == List_PopTail(listPtr, (void*)person[0]))
    {
    	status = OK;
    }
    else
    {
    	status = ERR;
    }
	Print_Test(status);
    
    List_PushHead(listPtr,(void*)person[0]);
	List_PushHead(listPtr,(void*)person[1]);
	List_PushHead(listPtr,(void*)person[2]);
    
    List_PopHead(listPtr, &p);
    status = (((Person*)p)->id == person[2]->id) ? OK: ERR;
	Print_Test(status);
	
	List_PopTail(listPtr, &p);
	status = (((Person*)p)->id == person[0]->id) ? OK: ERR;
	Print_Test(status);
	
	if(LIST_UNINITIALIZED_ERROR == List_PopHead(NULL,&p))
	{
    	status = OK;
    }
    else
    {
    	status = ERR;
    }
	Print_Test(status);
	
    if(LIST_UNINITIALIZED_ERROR == List_PopTail(NULL,&p))
    {
    	status = OK;
    }
    else
    {
    	status = ERR;
    }
	Print_Test(status);
	
}

void CheckListIsEmpty()
{
    Status status;
	List* listPtr = NULL;
    listPtr = List_Create();
    status = List_IsEmpty(listPtr) ? OK: ERR;
   	Print_Test(status);
   	
   	List_PushHead(listPtr,(void*)&person[2]);
   	status = List_IsEmpty(listPtr) ? ERR: OK;
   	Print_Test(status);
   	
    status = List_IsEmpty(NULL) ? OK: ERR;
   	Print_Test(status);  	
}
Person* Person_Create(int _id)
{
	Person* p = NULL;
	p = (Person*)malloc(sizeof(Person));
	
	strcpy(p->name, "maor");
	p -> id =_id;
	p -> age =_id; 
	return p;
}
  
int main()
{
    int i;
   
     
    for(i = 0; i < 3; i++)
    {
    	person[i] = Person_Create(i);
    }
 
    printf("Test List_Create:\n");
    Print_Test(CheckList_Create());
    printf("Test List_Destroy:\n");
    CheckList_Destroy();
    printf("Test ListCountItems:\n");
    CheckListCountItems();
    printf("Test ListPushHead\n");
    CheckListPushHead();
    printf("Test ListPushTail\n");
    CheckListPushTail();
    printf("Test ListPopHead & ListPopTail\n");
    CheckListPopHead();
    printf("Test ListIsEmpty\n");
    CheckListIsEmpty();
    
	return 0;
}
