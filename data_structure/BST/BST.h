/**************************************************************************************
    Author : Maor Gerbi
    Description : Basic Binary tree.
***************************************************************************************/
#ifndef __TREE_H__
#define __TREE_H__
#include "ADTDefs.h"
#include <stdlib.h>

#define FIND_TO_ATTACH 1
#define FIND_DATA      0

typedef struct Tree Tree;


typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
} TreeTraverse;

Tree*   TreeCreate();
void    TreeDestroy(Tree* _tree);
ADTErr  TreeInsert(Tree* _tree, int _data);
int     TreeIsDataFound(Tree* _tree, int _data);

int     IsBinarySearchTree(Tree *_tree);

void    TreePrint(Tree* _tree, TreeTraverse _traverseMode);


void CheckTreeCompletion(Tree* _tree, int* isComplete, int* subTreeHeight);
int  AreSimilarTrees(Tree* _treeA, Tree* _treeB);
int  IsFullTree(Tree* _tree);
int IsDescendedTree(Tree* _tree);

#endif /*__TREE_H__*/

