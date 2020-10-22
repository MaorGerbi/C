/***************************************************************************
Author:                   Maor Gerbi
description:              Basic Binary Heap.
****************************************************************************/
# ifndef __HEAP_H__
# define __HEAP_H__
#include "../include/Vector.h"


/*
    ERR_OK = 0,                         
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    ERR_NOT_FAOUND,
    */

typedef struct Heap Heap;

/*
Description - creat new heap O(n)
input       - pointer to vector forom user
output      - pointer to new heap
error       - none  */            
Heap*   HeapBuild(Vector* _vec);

/*
Description - destroy heap (created at HeapBuild)
input       - pointer to heap
output      - pointer to vector
error       - none  */   
Vector*    HeapDestroy(Heap** _heap);

/*
Description - insert item into heap  O(log n)
input       - pointer to heap
		      _data: to insert            
output      - ERR_OK, err
error       - ERR_NOT_INITIALIZED, ERR_REALLOCATION_FAILED  */   
ADTErr  HeapInsert(Heap* _heap, int _data); 

/*
Description - insert root into _data 
input       - pointer to heap
		      _data: to insert            
output      - ERR_OK, err
error       - ERR_NOT_INITIALIZED, */  
ADTErr  HeapMax(Heap* _heap, int* _data);

/*
Description - extract the the max item at heap O(log n)
input       - pointer to heap
		      _data: to insert            
output      - ERR_OK, err
error       - ERR_NOT_INITIALIZED, ERR_UNDERFLOW */ 
ADTErr  HeapExtractMax(Heap* _heap, int* _data);

/*
Description - return num of items in heap
input       - pointer to heap          
output      - int: num of items
error       - none */ 
int     HeapItemsNum(Heap* _heap);


/*
Description - print heap
input       - pointer to heap
              _index: root index          
output      - none
error       - none */ 
void HeapPrint(Heap* _heap, int index);

#endif



