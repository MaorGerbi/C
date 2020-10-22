#define NDEBUG
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "BST.h"
#define TRUE 1
#define FALSE 0
/*typedef struct Tree Tree;*/

typedef struct Node{
	int data;
	struct Node* right;
	struct Node* left;
    }Node;

static void TreePrintIn(Node* _root)
{
    if(NULL ==_root)
    {
    	return ;
    }
	TreePrintIn(_root->left);
	printf("%d ",_root->data);
	TreePrintIn(_root ->right);
}
static void TreePrintPost(Node* _root)
{
    if(NULL ==_root)
    {
    	return ;
    }
	TreePrintPost(_root->left);
	TreePrintPost(_root ->right);
	printf("%d ",_root->data);
}
static void TreePrintPre(Node* _root)
{
    if(NULL ==_root)
    {
    	return ;
    }
    printf("%d ",_root->data);
	TreePrintPre(_root->left);
	TreePrintPre(_root ->right);
}

static Node* NodeCreate(int _data)
{
	Node* newNode = (Node*)calloc(1,sizeof(Node));
	if(NULL != newNode)
	{
		newNode->data = _data;
	}
	return newNode;
}

static int NodeDestroy(Node* _node)
{
    int data;
	assert(NULL != _node);
	data = _node-> data;

	free(_node);
    return data;
}

static void Destroy(Node* _root)
{
	if(NULL == _root)
	{
		return;
	}
	Destroy(_root->left);
	Destroy(_root->right);
	NodeDestroy(_root);
}
   
Tree* TreeCreate()
{	
	Node* sentinael= NodeCreate(INT_MAX);
	sentinael->right = sentinael;
	return (Tree*)sentinael;
}

void TreeDestroy(Tree* _tree)
{   
    Node *root = (Node*)_tree;
	if((NULL == root)||(root->right != root))
	{
		return ;
	}
	Destroy(root->left);
}

ADTErr TreeInsert(Tree* _tree, int _data)
{   
    Node *root= (Node*)_tree,*item = NodeCreate(_data);
     
    if(NULL == item)
    {
    	return ERR_ALLOCATION_FAILED;
    }
    
	while(NULL != root)
	{
		if(root->data > _data)
		{
			if(NULL == root->left)
			{ 
				root ->left = item;/*insert*/
				return ERR_OK;
			}
			root = root -> left;
		}
		else
		{
		    if(root->data < _data)
			{
				if(NULL == root->right)
				{
					root ->right = item;/*insert*/
					return ERR_OK;
				}
				root = root -> right;
			}
			else
			{
				NodeDestroy(item);
				return ERR_NOT_FAOUND;
			}
		 }
	 }
	return ERR_GENERAL;
}

int TreeIsDataFound(Tree* _tree, int _data)
{
    Node *root= (Node*)_tree; 		     		  
    if(NULL == root)
    {
    	return ERR_ALLOCATION_FAILED;
    }
    
	while(NULL != root)
	{

		if(root->data > _data)
		{
			root = root -> left;
		}
		else
		{
		    if(root->data < _data)
		    {
				root = root-> right;
			}
			else
			{
				return TRUE;
			}
		}
	
     }
     return FALSE;
}
 

void TreePrint(Tree* _tree,TreeTraverse _traverseMode)
{
    Node* root = (Node*)_tree;
	if(NULL == root)
	{
		printf("empty tree!!\n");
	}
	switch(_traverseMode)
	{
		case PRE_ORDER:
			TreePrintPre(root->left);
			break;	
		case IN_ORDER:
			TreePrintIn(root->left);
			break;
		case POST_ORDER:
			TreePrintPost(root->left);
			break;
	}
}

int IsBinarySearchTree(Tree* _root)
{
	static int ROOT = _root -> data;
	if(NULL != _root -> left)
	{
		if(_root->left->data > _root->data &&_root->left< ROOT)
		{
			return false;
		}
	}
	else
	{
		if(root->left->data < _root->data && _root->right > ROOT )
		{
				return false;
		}
	}
    return true;
    
	IsBinarySearchTree(Tree -> left);
	IsBinarySearchTree(Tree -> right);
	if(root)
	{
		return 1;
	}
	if(root->data > 	
	
	
	
	
	
	
	
	
	
	
	
	
	
