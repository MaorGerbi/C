#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/ADTDefs.h"
#include "../include/Vector.h"

#define RIGHT_SON(i) i*2 +1
#define LEFT_SON(i) i*2
#define PARENT(i) i/2

typedef struct Heap{
	Vector* m_vector;
	int m_numOfItems;
	}Heap;
	
static int FindLargest(Vector* _vector, int _i)
{
	int vectorSize, tempLargeIndex, tempLargeValue,leftSon, rightSon, root = 0;
	
	VectorItemsNum(_vector,&vectorSize);
	if(vectorSize >= LEFT_SON(_i))
	{
	    VectorGet(_vector, _i, &root);
		VectorGet(_vector, LEFT_SON(_i), &leftSon);
		tempLargeIndex = leftSon > root ? LEFT_SON(_i) : _i;
	}
	else
	{
		tempLargeIndex = _i;
	}
	
	if(vectorSize >= RIGHT_SON(_i))
	{
		VectorGet(_vector, RIGHT_SON(_i), &rightSon);
		VectorGet(_vector, tempLargeIndex, &tempLargeValue);
		return tempLargeValue > rightSon ? tempLargeIndex : RIGHT_SON(_i);
	}
	return tempLargeIndex;
}
	
static void swap(Vector* _vector, int _x, int _y)
{
	int x, y;
	
	VectorGet(_vector, _x, &x);  
	VectorGet(_vector, _y, &y);
	  
	VectorSet(_vector, _x, y);
	VectorSet(_vector, _y, x);
}
	
static void MaxHeapify(Vector* _vector, int i)
{
    int largest;
    
	largest = FindLargest(_vector, i);
	if (largest != i)
	{
		swap(_vector,i ,largest);
		MaxHeapify(_vector, largest);
	}
}

static void HeapUp(Heap* _heap, int _newItemIndex)
{
 	int newValue, parentValue;
 	
	if (1 == _newItemIndex)
	{
		return;
	}
	
	VectorGet(_heap->m_vector, _newItemIndex, &newValue);
	VectorGet(_heap->m_vector, PARENT(_newItemIndex), &parentValue);
	if (newValue > parentValue)
	{
		swap(_heap->m_vector, PARENT(_newItemIndex), _newItemIndex);
		HeapUp(_heap, PARENT(_newItemIndex));
	}
	
	return;
}
/****************************************************************/
Heap* HeapBuild(Vector* _vector)
{
    Heap* heap;
    int numOfItems,i;
    
	if(ERR_OK != VectorItemsNum(_vector, &numOfItems))
	{
		return NULL;
	}
	
	heap = (Heap*) malloc(sizeof(Heap));

	for(i = numOfItems/2 ; i > 0 ; i--)
	{
		MaxHeapify(_vector, i);
	}
	heap->m_numOfItems = numOfItems;
	heap->m_vector = _vector;
	return heap;
}

Vector* HeapDestroy(Heap** _heap)
{  
 	Vector* vector = NULL; 
 	
	if(NULL == _heap || NULL == *_heap )
	{
		return NULL;
	}
	
	vector = (*_heap)->m_vector;
	free(*_heap);
	*_heap = NULL;
	
	return vector;
} 

ADTErr  HeapInsert(Heap* _heap, int _data)
{
	if(NULL == _heap)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(ERR_OK != VectorAdd(_heap->m_vector, _data))
	{
			return ERR_REALLOCATION_FAILED;
	}
	
	 _heap->m_numOfItems++;
	HeapUp(_heap , _heap->m_numOfItems);
	return ERR_OK;
}

ADTErr  HeapMax(Heap* _heap, int* _data)
{
	if(NULL == _heap || NULL == _data)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_heap->m_numOfItems > 0)
	{
		return VectorGet(_heap->m_vector, 1, _data);
	}
	return ERR_UNDERFLOW;
}

ADTErr  HeapExtractMax(Heap* _heap, int* _data)
{    
	if(NULL == _heap)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(0 == _heap->m_numOfItems)
	{
		return ERR_UNDERFLOW;
	}
	
    if(_data != NULL)
    {
    	HeapMax(_heap , _data);
	}
	
    swap(_heap->m_vector, 1, _heap->m_numOfItems);    
    _heap->m_numOfItems--;
	MaxHeapify(_heap->m_vector, 1);
	return ERR_OK;
}

int HeapItemsNum(Heap* _heap)
{
	if(NULL != _heap)
	{
		return _heap->m_numOfItems;
	}		
	return 0;
}
	
void HeapPrint(Heap* _heap)
{
	int value, breakPoint = 0;
	double i = 9.8, linebreak;
	linebreak = log(i);
	
	for(i = 1; i <= _heap->m_numOfItems; ++i)
	{
		VectorGet(_heap->m_vector, i, &value);
		printf(" %d ",value);
		
		/*
	    if(breakPoint == linebreak)
		{
			printf("\n");
			++breakPoint;
		}*/
	}
}

