#include "../include/Vector.h"
#include "Stack.h"

Stack*  StackCreate (size_t _size, size_t _blockSize)
{
	return (Stack*)VectorCreate(_size, _blockSize);
}

void    StackDestroy(Stack* _stack)
{
	Vector* vector = (Vector*)_stack;
	
	VectorDestroy(vector);
}

ADTErr  StackPush(Stack* _stack, int  _item)
{
	Vector* vector = (Vector*)_stack;
	
	return VectorAdd(vector, _item);
}

ADTErr  StackPop(Stack* _stack, int*  _item)
{
	Vector* vector = (Vector*)_stack;
	
	return VectorDelete(vector, _item);
}

ADTErr  StackTop(Stack* _stack, int* _item)
{
    Vector* vector = (Vector*)_stack;
    int numOfItems;
    
	VectorItemsNum(vector, &numOfItems);    
	return VectorGet(vector, numOfItems, _item);
}

bool StackIsEmpty(Stack* _stack)
{
    Vector* vector = (Vector*)_stack;
    int numOfItems;
    if(NULL == _stack)
    {
    	return 1;
    }  
      
	VectorItemsNum(vector, &numOfItems); 
	return !(numOfItems);
}

void    StackPrint(Stack *_stack)
{
	   Vector* vector = (Vector*)_stack;
	   
	   VectorPrint(vector);
}
