/**************************************************************************************
    Author :            Maor Gerbi
    Description : Stack Implementation. Using dynamic vector ADT.
***************************************************************************************/
#ifndef __STACK_H__
#define __STACK_H__

typedef struct Stack Stack;
typedef int bool;

/*
discription - Create new stack 
input       - size     : The initial allocation size.
  		      blockSize: The extention block size. 
output      - pointer to new stack 
error       - none
*/
Stack*  StackCreate (size_t _size, size_t _blockSize);

/*
description - Destroy Stack (Created by StackCreate)
input       - _stack: pointer to Stack
output      - none
error       - none
*/
void    StackDestroy(Stack* _stack);

/*
description - push item into stack 
input       - _stack: pointer to Stack
 			  _item : to add  
output      - ERR_OK, error
error       -ERR_REALLOCATION_FAILED, ERR_NOT_INITIALIZED,ERR_OVERFLOW
*/
ADTErr  StackPush   (Stack* _stack, int  _item);

/*
description - pop item from stack (last in)
input       - _stack: pointer to Stack
 			  _item : pointer to varible insert the value thtat removed  
output      -ERR_OK, 
error       -ERR_REALLOCATION_FAILED, ERR_NOT_INITIALIZED,ERR_UNDERFLOW
*/
ADTErr  StackPop    (Stack* _stack, int* _item);

/*
description - show the top value in stack
input       - _stack: pointer to Stack
 			  _item : pointer to varible insert the value on top 
output      -ERR_OK, 
error       - ERR_NOT_INITIALIZED
*/
ADTErr  StackTop    (Stack* _stack, int* _item);

/*
description - check if stack is empty (TRUE-none zero, False-zero)
input       - _stack: pointer to Stack
output      - int TRUE/FALSE
error       - none 
*/
bool StackIsEmpty(Stack* _stack);

/*  Unit-Test functions  */
void    StackPrint   (Stack *_stack);

#endif /*__STACK_H__*/
