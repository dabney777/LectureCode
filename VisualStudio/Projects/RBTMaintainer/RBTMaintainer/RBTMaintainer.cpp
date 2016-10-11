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

void LeftRotation(RBTNode *node) {
	RBTNode *parent=node->parent, *left=node->lchild, *right=node->rchild;
	if (node->parent != NULL) {
		if (node == parent->lchild) {
			parent->lchild = right;
		}else {
			parent->rchild = right;
		}
	}
	else	{		right->parent = node->parent;	}
	node->parent = right;
	node->rchild = right->lchild;
	right->parent = parent;
	right->lchild->parent = node;
	right->lchild = node;

}

void RightRotation(RBTNode *node) {
	if (node->parent != NULL) {
		if (node->parent->lchild == node) {
			node->parent->lchild = node->lchild;
		}
		else {
			node->parent->rchild = node->lchild;
		}
	}
	else	{		node->lchild->parent = node->parent;	}
	node->parent = node->lchild;
	RBTNode *tmp = node->lchild->rchild;
	tmp->parent = node;
	node->parent->rchild = node;
	node->lchild = tmp;

	
}

void flipNodeColor(RBTNode *node) {
	if (node->lchild->color == node->rchild->color&&node->lchild->color == 1) {
		if (node->parent != NULL) {
			node->color = 1;
		}
		node->lchild->color = node->rchild->color = 1;
	}
}
void insertToBLACKParent(RBTNode *node, RBTNode *insertP) {
	if (insertP->color != 0)cout << "insertToBLACKParent have a wrong." << endl;
	if (node->key < insertP->key) { insertP->lchild = node; node->parent = insertP; }
	if (node->key >= insertP->key) { insertP->rchild = node; node->parent = insertP; }
	flipNodeColor(insertP);
}

void insertToREDParent(RBTNode *node, RBTNode *insertP,RBTNode *uncle) {
	if (uncle->color == 1) {//insertP is grantpa's lchild
		if (insertP == insertP->parent->lchild) {
			if (insertP == insertP->parent->lchild) { //node is insertP's lchild 
				insertP->parent->color = 1;
				insertP->color = 0;
				BSTRightRotate(insertP->parent);
			}
			else {						//node is insertP's rchild
				BSTLeftRotate(insertP);//insertP is the new insert node
				insertP->parent->lchild = Nil;
				insertToREDParent(insertP, node, uncle);
			}
		}else {
			if (insertP == insertP->parent->rchild) { //node is insertP's rchild 
				insertP->parent->color = 1;
				insertP->color = 0;
				BSTLeftRotate(insertP->parent);
			}
			else {						//node is insertP's lchild
				BSTRightRotate(insertP);//insertP is the new insert node
				insertP->parent->rchild = Nil;
				insertToREDParent(insertP, node, uncle);
			}
		}
	}
}
void RBTInsert(int key, RBTNode *root) {
	RBTNode *insertPosition = RBTSearch(root, key),*uncle=NULL,*parent=NULL;
	if (insertPosition->color == 0) { insertToBLACKParent(CreatRBTNode(key), insertPosition); }
	else {
		parent = insertPosition->parent;
		if (parent->lchild == insertPosition) {
			uncle = parent->rchild;
		}else {
			uncle = parent->lchild;
		}
		insertToREDParent(CreatRBTNode(key), insertPosition, uncle);
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
void printRBT(RBTNode *root) {


}


int main()
{
	RBTList RBT;


    return 0;
}

