#ifndef __Common_H__
#define __Common_H__

#include <stdlib.h>
#include <stdio.h>
#include "DLL.h"

/*
typedef struct Pair{  for hash
	void* key;
	void* value;
	}Pair;
*/	
typedef struct Node{
	void* m_data;
	struct Node* m_next;
	struct Node* m_prev;
}Node;

struct List{
	Node m_start;
	Node m_end;
	size_t m_magicNum;
};

Node* NodeCreat(const void* m_data);
void InsertNode(Node* _sentinel, Node* _NodeToINsert);
#endif/*Connon_H*/
