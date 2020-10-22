#include "Queue.h"

struct Queue{
	void*  *m_items;
	size_t m_size;
	size_t m_head;
	size_t m_tail;
	
};
	
Queue* Queue_Create(size_t _maxSize)
{
	Queue* queue = NULL;
	
	if(1 >= _maxSize)
	{
		return NULL;
	}
	
	queue = (Queue*)malloc(sizeof(Queue));
	if(NULL == queue)
	{
		return NULL;
	}
	
	queue->m_items = malloc(_maxSize*sizeof(void*));
	if(NULL == queue->m_items)
	{
		return NULL;
	}
	
	queue->m_size = _maxSize;
	queue->m_tail = 1;
	queue->m_head = 0;
	
	return queue;
}

void Queue_Destroy(Queue* *_queue, ElementDestroy func)
{   
    size_t tail, head;
    
  	if(NULL == *_queue)
	{
		return ;
	}
	
	tail = (*_queue)->m_tail;
	head = (*_queue)->m_head;	
    if(NULL != func)
    {
    	while((head + 1) != tail) 
    	{
    		head = (head+1)%(*_queue)->m_size;
            (*func)((*_queue)->m_items[head]);
        }
    }
    
    free(*_queue);
    *_queue = NULL;
}

Queue_Result Queue_Enqueue(Queue* _queue, void* _item)
{
	if(NULL == _queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}	
	
	if(NULL == _item)
	{
		return QUEUE_INVALID_ARGUMENT;
	}

	if(_queue->m_tail == _queue->m_head)
	{
		return QUEUE_OVERFLOW;
	}
	_queue->m_items[_queue->m_tail] = _item;
	_queue->m_tail =  (_queue->m_tail+1)%_queue->m_size;
	
	return QUEUE_SUCCESS;
}

Queue_Result Queue_Dequeue(Queue* _queue, void* *_pValue)
{
	if(NULL == _queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}	
	
	if(NULL == _pValue)
	{
		return QUEUE_INVALID_ARGUMENT;
	}
	
	_queue->m_head = (_queue->m_head+1)%_queue->m_size;
	if(_queue->m_tail == _queue->m_head)
	{
		return QUEUE_UNDERFLOW;
	}
	 
	*_pValue = _queue->m_items[_queue->m_head];
	 
	 return QUEUE_SUCCESS;	
}

int Queue_IsEmpty(const Queue* _queue)
{
	if(NULL == _queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}	
	
	return (_queue->m_tail - _queue->m_head == 1);
}

int Queue_IsFull(const Queue* _queue)
{
	if(NULL == _queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}	
	
	return (_queue->m_tail == _queue->m_head);
}

