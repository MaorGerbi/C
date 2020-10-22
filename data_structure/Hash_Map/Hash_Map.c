#include "Hash_Map.h"

struct HashMap {
	List** m_listArr;
	size_t m_capacity;
	size_t m_size;
	size_t m_numOfItems;
	HashFunction m_hashFunc;
	KeyEqualityFunction m_keysEqualFunc;
    
	};
	
static Pair* Pair_Create(void* _key, void* _value)
{
	Pair* pair;
	
	pair = (Pair*)malloc(sizeof(Pair));
	Pair->m_key   = _key;
	Pair->m_value = _value;
	
	return Pair;
}
	
int Is_Prime(size_t num)
{
    int i;
	for(i = 2; i < num/2; i++)
	{
		if(num % i == 0)
		{
			return 0;
		}
	}
	return 1;
}
	
size_t static Find_NextPrime(size_t capacity)
{
	while(!Is_Prime(capacity))
	{
		++capacity;
	}
	return capacity;
}
/**********************************************************************/
	
HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, KeyEqualityFunction _keysEqualFunc)
{
	HashMap* hashPtr = NULL;
	List** hashMap	= NULL;
	size_t size = 0;
	if(NULL == _hashFunc ||NULL == _keysEqualFunc ||0 == _capacity)
	{
		return NULL; 
	}
	
	hashPtr = (HashMap*)malloc(sizeof(HashMap));
	if(NULL == hashPtr)
	{
		return NULL; 
	}
	size = Find_NextPrime(_capacity);
	hashMap = (List**)calloc(size,sizeof(List*));
	if(NULL == hashMap)
	{
		free(hashPtr);
		return NULL;
	}
    hashPtr->m_listArr = hashMap;
	hashPtr->m_size = size;
	hashPtr->m_capacity  = _capacity;
	hashPtr->m_hashFunc = _hashFunc;
	hashPtr->m_keysEqualFunc = _keysEqualFunc;
	hashPtr->m_numOfItems = 0;
	
	return hashPtr;
}
	
Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value)
{
    size_t index;
    List* list = NULL;
    Pair* pair = NULL;
	if(NULL == _map)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	if(findPlaceOn(_KEY))
	{
		MAP_KEY_DUPLICATE_ERROR;
	}
	
	if(_map->m_capacity == _map->numOfItems)
	{
		return MAP_OVERFLOW_ERROR;
	}
	
	pair = Pair_Create(_key, _value);
	if(NULL == Pair)
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	/*find the place to insert key on hashMap*/
	index = (*_map->m_hashFunc)(_key) % _map->m_size;
	list = ListCreate(_map->hashMap[index]);
	ListItr_InsertBefore(ListItr_Begin(list), pair);
	return MAP_SUCCESS;
}
	
Map_Result HashMap_Find(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	if(NULL == _map)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
    index = (*_map->m_hashFunc)(_searchKey) % _map->m_size;
    
    if(NULL != _map->hashMap[index])
    {
         void* currItem = ListItr_Begin(_map);
         
    	 while(currItem != ListItr_End(_map))
    	 {
    	 	if((*_map->m_keysEqualFunc)(_searchKey, (Pair*)ListItr_Get(currItem)->m_key))
    	 	{
    	 	    if(NULL != _pValue)
    	 	    {
    	 			*_pValue = (Pair*)ListItr_Get(currItem)->m_value;
    	 		}
    	 		return MAP_SUCCESS;  	 		
    	 	}
    	 }
   	}
   return MAP_KEY_NOT_FOUND_ERROR ; 
}   	 	
    	  	
	
	
Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	if(NULL == _map)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
    index = (*_map->m_hashFunc)(_searchKey) % _map->m_size;
    
    if(NULL != _map->hashMap[index])
    {
         void* currItem = ListItr_Begin(_map);
    	 while(currItem != ListItr_End(_map))
    	 {
    	 	if((*_map->m_keysEqualFunc)(_searchKey, (Pair*)ListItr_Get(currItem)->m_key))
    	 	{
    	 	    if(NULL != _pValue)
    	 	    {
    	 			*_pValue = (Pair*)ListItr_Get(currItem)->m_value;
    	 		}
    	 		*_pKey = (Pair*)ListItr_Get(currItem)->m_key;
    	 		ListItr_Remove(currItem);
    	 		return MAP_SUCCESS;  	 		
    	 	}
    	 }
   	}
    return MAP_KEY_NOT_FOUND_ERROR ; 
}   

size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	if(NULL == _map || NULL == _action)
	{
		return 0;
	}
	
	for(i = 0; i < _map->m_size; i++)
	{
	    if(NULL != _map->hashMap[i])
	    {
	     	void* currItem = ListItr_Begin(_map);
    	 	while(currItem != ListItr_End(_map))
    	 	{
				if((*_action)((Pair*)ListItr_Get(currItem)->m_key,(Pair*)ListItr_Get(currItem)->m_value, _context))
				{
                 	++count;
                }
                else
                {
                	return count;
                }
                currItem = ListItr_Next(currItem);
            } 
         }

     }
}
		
Map_Stats HashMap_GetMapStatistics(const HashMap* _map)
{
    Map_Stats* mapStats = NULL;
    int maxChainLength = 0, collisions = 0, numOfPair = 0;
	if(NULL == _map)
	{
		return NULL;
	}
	mapStats = (Map_Statats*)malloc(sizeof(Map_Statats));
	
	for(i = 0; i < _map->m_size; i++)
	{
	    if(NULL != _map->hashMap[i])
	    {
	     	void* currItem = ListItr_Begin(_map);
    	 	while(currItem != ListItr_End(_map))
    	 	{  
	         	currItem = ListItr_Next(currItem);
	        	++chainLength
            }
            if(1 < chainLength)
            {
            	++collisions;
            	(maxChainLength < chainLength) ? maxChainLength = chainLength;
            } 
         }
     }
     
     mapStats->pairs = numOfItems;
     mapStats->collisions = collisions;/*all 2+ items*/
     mapStats->buckets = _map->m_size - collisions;
     mapStats->chains = collisions;/*TODO count++  - > 2 + */
	 mapStats->maxChainLength = maxChainLength;
	 mapStats->averageChainLength = numOfItems/chains; 
}

size_t HashMap_Size(const HashMap* _map)
{
	return _map->m_size;
}

size_t HashMap_Capacity(const HashMap* _map)
{
	return _map->m_capacity;
}

size_t HashMap_HashSize(const HashMap* _map)
{
	return _map->m_numOfItems;
}  

typedef struct Map_Stats {
	size_t pairs;				/* number of pairs stored */
	size_t collisions;			/* total number of collisions encountered */
	size_t buckets;				/* total number of buckets */
	size_t chains;				/* non empty buckets (having non zero length list) */
	size_t maxChainLength;		/* length of longest chain */
	size_t averageChainLength;
Map_Result HashMap_GetStatistics(const HashMap* _map, size_t *_pCollisions, float *_pAverageChain);	
	
	/*
typedef enum Map_Result {
	MAP_SUCCESS = 0,
	MAP_UNINITIALIZED_ERROR, 	
	MAP_KEY_NULL_ERROR, 			
	MAP_KEY_DUPLICATE_ERROR, 		
	MAP_KEY_NOT_FOUND_ERROR, 		
	MAP_OVERFLOW_ERROR,		
	MAP_ALLOCATION_ERROR 			
} Map_Result;*/

	
