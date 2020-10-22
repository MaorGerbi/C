#include <stdio.h>
#include "BST.h"
#define PASS 1
#define FAIL 0
int main()
{   
    Tree* myTree = TreeCreate();
  
    /*TreeDestroy(myTree);*/
    TreeInsert(myTree, 10);
    TreeInsert(myTree, 12);
    TreeInsert(myTree, 9);
	TreeInsert(myTree, 12);
	TreeInsert(myTree, 7);
	TreeInsert(myTree, 15);
	TreeInsert(myTree, 12);
	TreeInsert(myTree, 7);
	TreeInsert(myTree, 99);
	TreeInsert(myTree, 14);
	TreeInsert(myTree, 15);
	TreeInsert(myTree, 6);
    printf("PRE_ORDER\n");
    TreePrint(myTree, PRE_ORDER);
    printf("\n");
    printf("IN_ORDER\n");
    TreePrint(myTree, IN_ORDER);
    printf("\n");
    printf("POST_ORDER\n");
    TreePrint(myTree,POST_ORDER);
    printf("\n");
    if(TreeIsDataFound(myTree ,9))
    {
    	printf("the value 9 is : in the tree\n");
    }
    if(TreeIsDataFound(myTree ,7))
    {
    	printf("the value 7 is : in the tree\n");
    }
    if(TreeIsDataFound(myTree ,99))
    {
    	printf("the value 99 is : in the tree\n");
    }  
    
    
    TreeDestroy(myTree);
    printf("run\n");
    printf("destroy ok \n");

	return 0;
}

/*
ADTErr  
int     TreeIsDataFound(Tree* _tree, int _data);



static void printTestRes(int status, char*)
{
	printf("res
void CreatTest()
{
    Tree* myTree = TreeCreate();
    printf("test for creating");
	if(myTree)
	{
		printf("pass\n");
	}
	else
	{
		printf("fail!\n");
	}
}*/
