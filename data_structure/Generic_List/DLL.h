#ifndef __LIST_H__
#define __LIST_H__

/**
 *  @file list.h
 *  @brief Create a Generic Double Linked List data type
 *
 *  @details Implemented as double linked list using head and tail sentinels.
 *  Nodes are allocated from heap and store pointer to user provided element.
 *
 *  @author Author MuhammadZ (muhammadz@experis.co.il)
 *
 *  @bug No known bugs.
 */

#include <stddef.h>  /* size_t */
#include "Common.h"
typedef struct List List;
typedef void (*DestroyFun)(void* _item);

typedef enum List_Result {
	LIST_SUCCESS = 0,
	LIST_UNINITIALIZED_ERROR,			/**< Uninitialized list 					 	*/
	LIST_ALLOCATION_ERROR,				/**< Node allocation failed due to heap error   */
	LIST_UNDERFLOW_ERROR

} List_Result;

/**
 * @brief Create a list
 *
 * @returns a pointer to the created list.
 * @retval NULL on failure due to allocation failure
 */
List* List_Create(void);

/**
 * @brief Destroy list
 * @details Destroys the list completely
 *          optionally destroys elements using user provided function
 *
 * @params[in] _pList : A pointer to previously created List returned via ListCreate
 *					   on completion *_pList will be null
 * @params[in] _elementDestroy : A function pointer to be used to destroy elements inserted into the list
 *             or a null if no such destroy is required
 */

void List_Destroy(List** _pList, DestroyFun _elementDestroy);

/**
 * @brief Add element to head of list
 * @details time complexity: O(1).
 *
 * @params _list A previously created List ADT returned via ListCreate
 * @params _item An item to add to the list
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure
 */
List_Result List_PushHead(List* _list, const void* _item);

/**
 * @brief Add element to the list's tail
 * @details time complexity O(1).
 *
 * @params _list
 * @params _item to ad to the list
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure
 */
List_Result List_PushTail(List* _list, const void* _item);

/** @brief Remove element from list's head
 *  @details if successful, stores a pointer to the removed item in _pItem
 *  time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @params _pItem: A pointer to receive the removed item
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_UNDERFLOW_ERROR if the list is empty
 */
List_Result List_PopHead(List* _list, void* *_pItem);

/** @brief Remove element from list's tail
 *  @details time complexity O(1).
 * *
 * @params _list : A previously created List ADT returned via ListCreate
 * @params _pItem: A pointer to receive the removed item
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_UNDERFLOW_ERROR if the list is empty
 */
List_Result List_PopTail(List* _list, void* *_pItem);

/** @brief Get number of elements in the list
 * Average time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @retval number of elements on success
 * @retval 0 if the list is empty or not initialized
 */
size_t List_Size(const List* _list);

/** @brief Check if list is empty
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @retval true if list is empty
 */
int List_IsEmpty(const List* _list);

void List_Print(List* _list,void(*PersonPrint)(void* _person));
#endif /* __LIST_H__ */
