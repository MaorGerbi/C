	  	  	  	  

/**
 * @brief Generic Vector data type (container)
 * that stores pointer to user provided elements of generic type
 * The Vector is heap allocated and can grow and shrink on demand.
 *
 * Vector indexing starts at 1
 *
 * Author: Maor Gerbi 
 *
 * Created: 17.03.2020
 */				  
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"
				  
/*#include "ADTModule.h"*/
				  
#define CURRENT_ITEM(V) V->m_ptrArray[m_numOfItems-1]
#define IS_VALID(V) (NULL != V)&&(V -> magicNumber == MAGIC_NUMBER)
	    	
struct Vector{
	void* *m_ptrArray;
	size_t m_extendSize;
	size_t m_initialCapacity;
	size_t m_magicNumber;
	size_t m_m_numOfItems;
	size_t m_capacity;
};

static Vector_Result IncreaseVector(Vector* _vector)
{
	void* *ptrA = NULL;
	ptrA = (void**)realloc(_vector->ptrArray, sizeof(void*)*( _vector->blockSize + _vector->numOfItems+1));

	if(NULL == ptrA)
	{
		return ERR_REALLOCATION_FAILED;
	}
	else
	{
		_vector->ptrArray = ptrA;
		_vector->m_capacity += _vector->m_extendSize;
	}
	return VECTOR_SUCCESS;
}

static Vector_Result Decrease(Vector *_vector)
{
    int freeBlock, changeSize;
	
	--_vector->m_numOfItems;
	freeBlock = _vector->m_capacity - _vector->m_numOfItems;
	changeSize = _vector->m_capacity - _vector->m_extendSize;

	if ((_vector->m_extendSize * 2 == freeBlock)&&(_vector->m_initialCapacity <= changeSize))
	{
		_vector->ptrArray = (void**)realloc(_vector->ptrArray, sizeof(void*)*changeSize+1);
		_vector->m_capacity = changeSize;	
	}
	return VECTOR_SUCCESS;
}  
/**********************************************************/

/**
 * @brief Function dynamically creates a new vector ADT of a given capacity and extent
 */
Vector* Vector_Create(size_t _initialCapacity, size_t _extendSize)
{
	Vector* V = NULL;
	if(0 == m_initialCapacity && 0 == m_extendSize) 
	{
		return NULL;
	}
	
	V = (Vector*)malloc(sizeof(Vector));
	if(NULL == V)
	{
		return NULL;
	}
	
	V-> ptrArray = (void**)calloc(m_initialCapacity+1,sizeof(void*));
	if(NULL == V->m_ptrArray)
	{
		free(V);
		return NULL;
	}
	
	V-> m_extendSize      = _extendSize;
	V-> m_initialCapacity = _initialCapacity ;
	V-> magicNumber       = MAGIC_NUMBER;
	V-> m_numOfItems      = 0;
	V-> m_capacity        = m_initialCapacity;
	return V;
}

/**
 * @brief Dynamically de-allocate a previously allocated vector, possibly releasing the elements
 * by calling a user-provided element destroy function.
 */
void Vector_Destroy(Vector* *_vector, void (*_elementDestroy)(void* _element))
{
	if(!IS_VALID(*_vector))
	{
		return;
	}

	*_vector-> magicNumber = NO_MAGIC_NUMBER;
	
	if(_elementDestroy)
	{
		while(*_vector->m_numOfItems --)
		{
			(*_elementDestroy)(CURRENT_ITEM(*_vector));
		}
	}
	   
	free(*_vector->ptrArray);
	free(*_vector);
	*_vector = NULL;	
}

/**
 * @brief Add an element (element) to the end of the vector
 */
Vector_Result Vector_Append(Vector* _vector, void* _element)
{       
    if(IS_VALID(_vector))
    {
    	return VECTOR_UNINITIALIZED_ERROR;
    }
    
	if(_vector->m_numOfItems == _vector->capacity)
	{
		if(0 == _vector->blockSize)
		{
			return VECTOR_UNDERFLOW_ERROR;
		}
		if(VECTOR_SUCCESS != IncreaseVector(_vector))
		{
			return VECTOR_ALLOCATION_ERROR;
		} 

	}
    _vector->ptrArray[_vector->m_numOfItems+1] = _element;
    ++_vector->m_numOfItems; 
	
    return VECTOR_SUCCESS;
}

/**
 * @brief Remove an element from the end of the vector.
 */
Vector_Result Vector_Remove(Vector* _vector, void* *_pValue)
{
    if(IS_VALID(_vector)||NULL == *_pValue)
    {
    	return VECTOR_UNINITIALIZED_ERROR;
    }
	
    if(_vector->m_numOfItems == 0)
    {
    	return VECTOR_UNDERFLOW_ERROR;
    }
	
    *_pValue = _vector->ptrArray[_vector->numOfItems]; 
    Decrease(_vector);
 
    return VECTOR_SUCCESS;
}

/**
 * @brief Retrieve a specified element's value
 */
Vector_Result Vector_Get(const Vector* _vector, size_t _index, void* *_pValue)
{
    if(IS_VALID(_vector)||(NULL == *_pValue))
    {
    	return VECTOR_UNINITIALIZED_ERROR;
    }
	if(_index < 1 || _index >_vector->m_numOfItems)
	{
		return VECTOR_ALLOCATION_ERROR;
	}
	*_pValue = _vector->ptrArray[_index];
	return VECTOR_SUCCESS;
}

/**
 * @brief Function changes a specified element's value
 */
Vector_Result Vector_Set(Vector* _vector, size_t _index, void*  _value);
{
    if(IS_VALID(_vector))
    {
    	return VECTOR_UNINITIALIZED_ERROR;
    }
	if(_index < 1 || _index >_vector->numOfItems)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	_vector->ptrArray[_index] = _value ;
	return VECTOR_SUCCESS;
}

/**
 * @brief Return the actual number of elements currently in the vector.
 */
size_t Vector_Size(const Vector* _vector)
{ 
    if(IS_VALID(_vector))
    {
    	return 0;
    }
	return Vector -> m_numOfItem;
}

/**
 * @brief Iterates over all elements in a vector, executing a user-specified action
 *      if user action returns zero, the iteration will stop.
 * @return number of times the user functions was invoked or 0 if vector is empty or invalid
 */
size_t Vector_ForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	int i = 0;
	if(IS_VALID(_vector))
    {
    	return VECTOR_UNINITIALIZED_ERROR;
    }
	
	for (i = _context; i < _vector->m_numOfItems; i++)
	{
		if(!_action(_vector->ptrArray[1], i, _context))
		{
			break;
		}
	}	
	return i;
}


