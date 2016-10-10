// RBTMaintainer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

#define N 10000
RBTNode *Nil = CreatRBTNode(0, true);
typedef struct RBTNode{
	int color = 1;		//0 is Black and 1 is Red!
	RBTNode *parent=NULL, *lchild=Nil, *rchild = Nil;
	int key = 0;
	bool isNil = false;
}RBTNode;

typedef struct RBTList {
	RBTNode NodeList[N];
	int NodeNum;
};

void LeftRotation(RBTNode &node) {
	
}

void RightRotation(RBTNode &node) {

}
enum InsertCondition{ RBB, BRR, BRB, BBR, BBB}ic;//root,left child,right child.


void RBTInsert(int key, RBTNode *root) {
	if (root == NULL) { root = CreatRBTNode(key); root->color = 0; return; }//when an empty tree
	
	RBTNode *node = CreatRBTNode(key), *insertPosition;
	RBTNode *uncle;
	insertPosition = RBTSearch(root, node->key);
	
	if (insertPosition->parent == NULL)
		if (node->key < insertPosition->key) {
			node->parent = insertPosition;
			insertPosition->lchild = node;
		}
		else {
			node->parent = insertPosition;
			insertPosition->rchild = node;
		}
	
	if (insertPosition->parent->color == 1) RBTInsertOperate(node, insertPosition, RBB);
	if (insertPosition->color == 0) {
		if (insertPosition->key < insertPosition->parent->key) {
			uncle = insertPosition->parent->rchild;
			if (uncle->color == 0) RBTInsertOperate(node, insertPosition, BBB);
				else RBTInsertOperate(node, insertPosition, BBR);
		}
		else
			uncle = insertPosition->parent->lchild;
			if (uncle->color == 0) RBTInsertOperate(node, insertPosition, BBB);
				else RBTInsertOperate(node, insertPosition, BRB);
	}
}


void RBTInsertOperate(RBTNode *node, RBTNode *insertPosition, InsertCondition ic) {
	switch (ic)
	{
	case RBB:
		break;
	case BRR:
		break;
	case BRB:
		break;
	case BBR:
		break;
	case BBB:
		break;
	default:cout << "That is impossible!OOOOOOh~" << endl;
		break;
	}
}


void RBTDelete(RBTNode &node) {

}

RBTNode *CreatRBTNode(int _key,bool _isNil=false) {
	RBTNode *newNode = (RBTNode*)malloc(sizeof(RBTNode));
	newNode->key = _key;
	newNode->isNil = _isNil;
	return newNode;
}

RBTNode *RBTSearch(RBTNode *tree, int key) {		//Which Node the new Node will insert
	if (tree == NULL) return NULL;
	if (tree->isNil == true) return tree->parent;
	if (key > tree->key) RBTSearch(tree->rchild, key);
	if (key <= tree->key) RBTSearch(tree->lchild, key);
}


int main()
{
	RBTList RBT;


    return 0;
}

