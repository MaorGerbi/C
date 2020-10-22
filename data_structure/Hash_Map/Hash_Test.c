#include <stdio.h>
#include "Hash_Map.h"

#define OK 1
#define ERR 0

typedef int Status;
/*
typedef size_t (*HashFunction)(const void* _key);
typedef int (*KeyEqualityFunction)(const void* _firstKey, const void* _secondKey);
*/

int Key_EqualityFunction(const void* _firstKey, const void* _secondKey)
{
    size_t *key1,*key2;
    key1 = (size_t*)_firstKey;
    key2 = (size_t*)_secondKey;
	return *key1 == *key2;
}

size_t Hash_Function(const void* _key)
{   
    size_t* key = (size_t*)_key;
	return (*key)*2;
}

static void Test_Print(Status _status)
{
	_status ? printf("PASS!\n"): printf("~FAIL~!\n");
}

void Check_HashMapCreate()
{
    HashMap* hashPtr = NULL;
    
	printf("Check_HashMap Create:\n");
	
	hashPtr = HashMap_Create(10, Hash_Function, Key_EqualityFunction);
	(hashPtr == NULL) ? Test_Print(ERR) : Test_Print(OK); 
	
	hashPtr = HashMap_Create(10, NULL, Key_EqualityFunction);
    (hashPtr == NULL) ? Test_Print(OK) : Test_Print(ERR);
    
    hashPtr = HashMap_Create(10, Hash_Function, NULL);
    (hashPtr == NULL) ? Test_Print(OK) : Test_Print(ERR);
    
    hashPtr = HashMap_Create(0, Hash_Function, Key_EqualityFunction);
    (hashPtr == NULL) ? Test_Print(OK) : Test_Print(ERR);
}

void Check_HashMap_Insert()
{
	Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value);
		
	
	
	
		
int main()
{
	Check_HashMapCreate();
	Check_HashMap_Insert();
	
	return 0;
}
	
