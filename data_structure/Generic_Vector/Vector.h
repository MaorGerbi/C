#ifndef VECTOR_H
#define VECTOR_H

/** Generic Vector data type (container)
 * Stores pointer to user provided elements of generic type (void*)
 * The Vector is heap allocated and can grow and shrink on demand.
 *
 * Vector indexing starts at 1
 *
 * Author: Alexander Katz (Based on header file by Muhammad Z)
 *
 * Created: 12.11.2018
 */


#include <stddef.h>	/* size_t */

typedef struct Vector Vector;

typedef enum Vector_Result {
	VECTOR_SUCCESS,
	VECTOR_UNINITIALIZED_ERROR,
	VECTOR_ALLOCATION_ERROR,
	VECTOR_INDEX_OUT_OF_BOUNDS_ERROR,
	VECTOR_UNDERFLOW_ERROR,
	VECTOR_OVERFLOW_ERROR
} Vector_Result;



/**
 * @brief Function dynamically creates a new vector ADT of a given capacity and extent
 * @param[in] _initialCapacity - initial number of elements that can be stored in the container
 * @param[in] _extendSize - size of capacity changes (increase/decrease)
 *
 * @return Vector* - on success / NULL on fail
 * Warnings:
 *	if _extendSize is 0 the vector will be of fixed size.
 * 	if both _initialCapacity and _extentSize are zero, function will return NULL.
 */
Vector* Vector_Create(size_t _initialCapacity, size_t _extendSize);


/**
 * @brief Dynamically deallocates a previously allocated vector, possibly releasing the elements
 * by calling a user-provided element destroy function.
 *
 * @param[in]	_vector - vector to be deallocated.
 * @param[in]	_elementDestroy : A function pointer to be called for all elements in the container
 */
void Vector_Destroy(Vector* *_vector, void (*_elementDestroy)(void* _element));


/**
 * @brief Add an element (element) to the end of the vector
 * @param[in]	_vector to append an Item to
 * @param[in]	_element to add.
 *
 * @return success or error code
 *	VECTOR_SUCCESS on success
 *	VECTOR_UNINITIALIZED_ERROR if input vector is not initialized
 *	VECTOR_ALLOCATION_ERROR if resize failed
 *	VECTOR_OVERFLOW_ERROR if vector is full and blocksize was 0 at initialization
 */
Vector_Result Vector_Append(Vector* _vector, void* _element);

/**
 * @brief Remove an element from the end of the vector.
 * @param[in]	_vector to delete an element from
 * @param[out]	_pValue - pointer to variable that will receive the deleted element value
 * @return success or error code
 *	VECTOR_SUCCESS on success
 *	VECTOR_UNINITIALIZED_ERROR if input vector is not initialized
 *	VECTOR_ALLOCATION_ERROR if resize failed
 *	VECTOR_UNDERFLOW_ERROR if vector is empty
 */
Vector_Result Vector_Remove(Vector* _vector, void* *_pValue);

/**
 * @brief Retrieve a specified elements's value
 * @param[in]	_vector to use.
 * @param[in]	_index of element to get value from.
 * @param[out]	_pValue - pointer to variable that will receive the element's value.
 * @return success or error code
 *	VECTOR_SUCCESS on success
 *	VECTOR_UNINITIALIZED_ERROR if input vector is not initialized
 *	VECTOR_INDEX_OUT_OF_BOUNDS_ERROR if given index is smaller than 1 or larger than
 *		number of elements in vector
 */
Vector_Result Vector_Get(const Vector* _vector, size_t _index, void* *_pValue);


/**
 * @brief Function changes a specified element's value
 * @param[in]	_vector to use.
 * @param[in]	_index of element to be changed
 * @param[in]	_value - new value
 * @return success or error code
 *	VECTOR_SUCCESS on success
 *	VECTOR_UNINITIALIZED_ERROR if input vector is not initialized
 *	VECTOR_INDEX_OUT_OF_BOUNDS_ERROR if given index is smaller than 1 or larger than
 *		number of elements in vector
 */
Vector_Result Vector_Set(Vector* _vector, size_t _index, void*  _value);

/**
 * @brief Return the actual number of elements currently in the vector.
 * @param[in]	_vector - Vector to use.
 * @return number of elements on success, 0 if vector is empty or invalid
 */
size_t Vector_Size(const Vector* _vector);


/**
 * @brief Return the current capacity of the  vector.
 * @param[in]	_vector - Vector to use.
 * @return capacity of vector on success, 0 if vector is empty or invalid
 */
size_t Vector_Capacity(const Vector* _vector);


/**
 * @brief Iterates over all elements in a vector, executing a user-specified action
 *      if user action returns zero, the iteration will stop.
 * @param[in] 	_vector - vector to iterate over.
 * @param[in] 	_action - User provided function pointer to be invoked for each element
 * @param[in]	_context - User provided context, will be sent to _action
 * @return number of times the user function was invoked or 0 if vector is empty or invalid
 */
typedef int	(*VectorElementAction)(void* _element, size_t _index, void* _context);

size_t Vector_ForEach(const Vector* _vector, VectorElementAction _action, void* _context);


#endif /* VECTOR_H */
