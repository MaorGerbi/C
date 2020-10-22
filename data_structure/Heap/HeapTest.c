#include <stdio.h>
#include "Heap.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

#define RIGHT_SON(i) i*2 +1
#define LEFT_SON(i) i*2

typedef enum Status {ERR, OK} Status;
struct Heap{
	Vector* m_vector;
	int m_numOfItems;
	};

void Test_Print(Status status)
{
	status ? printf(GRN"\nPASS!\n"RESET) : printf(RED"\nFAILED\n"RESET);
}
 
static Vector* InitVector()
{
    int i;
    Vector* V1;
    V1 = VectorCreate(5,5);
    
    for (i = 1; i <= 10; i++)
    {
    	VectorAdd(V1, i);
    }
    return V1;
}
static Status IsMaxHeap(Heap* _heap,int  _root)
{
	int leftSon, rightSon, root;
    Vector* _vector = (Vector*)_heap->m_vector;
    
	if(_heap->m_numOfItems/2 < _root)
	{
		return OK;
	}
	
	VectorGet(_vector, _root, &root);
	VectorGet(_vector, LEFT_SON(_root), &leftSon);
    VectorGet(_vector, RIGHT_SON(_root), &rightSon);
	if((RIGHT_SON(_root) < _heap->m_numOfItems && rightSon > root)|| leftSon > root)
	{
		return ERR;
	}
	else 
	{
		return IsMaxHeap(_heap, LEFT_SON(_root)) && IsMaxHeap(_heap, RIGHT_SON(_root));
	}
}
	
void Test_HeapBuild()
{
    Vector* vector = NULL;
    Heap* heap;
    
	printf("Test_HeapBuild: \n");
	vector = InitVector();
	heap = HeapBuild(vector);
	Test_Print(IsMaxHeap(heap, 1));

}

void Test_HeapDestroy()
{
	Vector* vector = NULL;
    Heap* heap;
    
	printf("\nTest_HeapDestroy: \n");
	vector = InitVector();
	heap = HeapBuild(vector);
	HeapDestroy(&heap);
    (NULL == heap)? Test_Print(OK):Test_Print(ERR);
    HeapDestroy(&heap);
    Test_Print(OK);
}
void Test_HeapInsert()
{
	Vector* vector = NULL;
	Heap* heap = NULL;
	int status;
	
	printf("\nTest_HeapInsert : \n");
	vector = InitVector();
	heap = HeapBuild(vector);
	HeapInsert(heap, 30);
	HeapInsert(heap, 31);
	HeapInsert(heap, 32);
	HeapInsert(heap, 20);
    Test_Print(IsMaxHeap(heap, 1));
    HeapDestroy(&heap);
    
	heap = HeapBuild(vector);
	status = HeapInsert(NULL, 30);
	status == ERR_NOT_INITIALIZED ?  Test_Print(OK) : Test_Print(ERR);
    HeapDestroy(&heap);    
}
void Test_HeapMax()
{
	Vector* vector = NULL;
    Heap* heap;
    int max, status;
    
	printf("\nTest_HeapMax: \n");
	vector = InitVector();
	heap = HeapBuild(vector);
	HeapMax(heap, &max);
	(max == 10)? Test_Print(OK) : Test_Print(ERR);
	
	HeapInsert(heap, 30);
	status = HeapMax(NULL , &max);
	status == ERR_NOT_INITIALIZED ?  Test_Print(OK) : Test_Print(ERR);
	
	vector = VectorCreate(1,1);
	heap = HeapBuild(vector);
	status = HeapMax(heap , &max);
	status == ERR_UNDERFLOW ?  Test_Print(OK) : Test_Print(ERR);
}

void Test_HeapExtractMax()
{
	Vector* vector = NULL;
    Heap* heap;
    int status, max;
	printf("\nTest_HeapExtractMax: \n");
	vector = InitVector();
	heap = HeapBuild(vector);
	HeapExtractMax(heap,NULL);
	Test_Print(IsMaxHeap(heap, 1));
	HeapDestroy(&heap);
	
	HeapInsert(heap, 30);
	status = HeapExtractMax(NULL , &max);
	status == ERR_NOT_INITIALIZED ?  Test_Print(OK) : Test_Print(ERR);
	
	vector = VectorCreate(1,1);
	heap = HeapBuild(vector);
	status = HeapExtractMax(heap , &max);
	status == ERR_UNDERFLOW ?  Test_Print(OK) : Test_Print(ERR);
}	

void Test_HeapItemsNum()
{
	Vector* vector = NULL;
    Heap* heap;
    int num;
    
	printf("\nTest_HeapItemsNum: \n");
	vector = InitVector();
	VectorPrint(vector);
	printf("\nTest_HeapItemsNum: \n");
	heap = HeapBuild(vector);
	VectorPrint(vector);
	num  = HeapItemsNum(heap);
	num == 10 ?  Test_Print(OK) : Test_Print(ERR);

	HeapPrint(heap,1);
}
	
int main()
{
	Test_HeapBuild();
	Test_HeapDestroy();
	Test_HeapInsert();
	Test_HeapMax();
	Test_HeapExtractMax();
	Test_HeapItemsNum();
	   
	return 0;
}
