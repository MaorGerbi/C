#include "DLL.h"

#define MAGIC_NUM     0xbfbbffbb
#define NOT_MAGIC_NUM 0xbbff1234
#define NOT_VALID(L) NULL == (L) || (L)->m_magicNum != MAGIC_NUM


Node* NodeCreat(void* m_data)
{
	Node* ptrN = (Node*)calloc(1,sizeof(Node));
	
	if(NULL != ptrN)
	{
		ptrN->m_data = m_data;
	}
	return ptrN;
}


void InsertNode(Node* _sentinel, Node* _NodeToINsert)
{	
	_NodeToINsert->m_next = _sentinel->m_next;
	_NodeToINsert->m_prev = _sentinel;
	_sentinel->m_next->m_prev = _NodeToINsert;
	_sentinel->m_next = _NodeToINsert;	
}

static void RmoveItem(Node* _NodeToRemove, void* *_data)
{
    *_data = _NodeToRemove->m_data;
    
	_NodeToRemove->m_prev->m_next = _NodeToRemove->m_next;
	_NodeToRemove->m_next->m_prev = _NodeToRemove->m_prev;
	free(_NodeToRemove);
}

/*****************************************************/

List* List_Create()
{
    List* ptrL = (List*) calloc(1,sizeof(List));
    
	if(NULL == ptrL)
	{
		return NULL;
	}
	ptrL->m_magicNum     = MAGIC_NUM;
	ptrL->m_start.m_next = &ptrL->m_end;
	ptrL->m_start.m_prev = &ptrL->m_start;
	ptrL->m_end.m_prev   = &ptrL->m_start;
	ptrL->m_end.m_next   = &ptrL->m_end;
	return ptrL;
}

void List_Destroy(List** _pList, DestroyFun _elementDestroy)
{
    Node *head = NULL, *tail = NULL, *current = NULL;
    
    if(NOT_VALID(*_pList))
	{
		return ;
	}
	
    head = &(*_pList)->m_start;
    tail = &(*_pList)->m_end;   
    current = head->m_next;
	while(head->m_next != tail)
	{ 
   		head->m_next = current->m_next;
   		if(NULL != _elementDestroy)
	    {
   			(*_elementDestroy)(current->m_data);
   		}
	    free(current);
	    current = head->m_next;		
	}

    (*_pList)->m_magicNum = NOT_MAGIC_NUM;
    free(*_pList);
    *_pList = NULL;
}	

List_Result List_PushHead(List* _list, const void* _item)
{
    Node* ptrN = NULL;
    
	if(NOT_VALID(_list))
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	ptrN = NodeCreat(_item);
	if(NULL == ptrN )
	{
		return LIST_ALLOCATION_ERROR;
	}
	InsertNode(&_list-> m_start, ptrN);
	return LIST_SUCCESS;
}
size_t List_Size(const List* _list)
{
    int count = 0; 
    Node *head = NULL, *tail = NULL;
    
	if(NOT_VALID(_list))
	{
		return 0;
	}
    head = _list->m_start.m_next;
    tail = &_list-> m_end;
	while(head != tail)
	{
	    ++count;
	    head = head->m_next;  		
	}
	return count;
}

int List_IsEmpty(const List* _list)
{
    if(NOT_VALID(_list))
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	return (_list->m_start.m_next == &_list->m_end);
}

List_Result List_PushTail(List* _list, const void* _item)
{
    Node* ptrN = NULL;
    
	if(NOT_VALID(_list))
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	ptrN = NodeCreat(_item);
	if(NULL == ptrN)
	{
		return LIST_ALLOCATION_ERROR;
	}
	
	InsertNode(_list->m_end.m_prev, ptrN);	
	return LIST_SUCCESS;
}

List_Result List_PopHead(List* _list, void* *_pItem)
{
    if(NOT_VALID(_list)|| NULL == _pItem)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if(!List_IsEmpty(_list))
	{
		RmoveItem(_list->m_start.m_next, _pItem);
        return LIST_SUCCESS;
    }
    return LIST_UNDERFLOW_ERROR;
}

List_Result List_PopTail(List* _list, void* *_pItem)
{
	if(NOT_VALID(_list)||NULL == _pItem)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(!List_IsEmpty(_list))
	{
		RmoveItem(_list->m_end.m_prev, _pItem);
        return LIST_SUCCESS;
    }
    return LIST_UNDERFLOW_ERROR;
}


void List_Print(List* _list, void(*PersonPrint)(void* _person))
{
    Node* head, *tail; 
    
	if(NOT_VALID(_list))
    {
    	printf("List empty!!");
    }
                                
    else
    {
		head  = _list->m_start.m_next;
		tail  = &_list->m_end;
		while(head != tail)
		{
			(*PersonPrint)(head->m_data);
		    head = head->m_next;
		}
	}    
}  


