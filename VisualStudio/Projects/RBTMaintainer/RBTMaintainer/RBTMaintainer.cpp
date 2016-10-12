// RBTMaintainer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

#define N 10000

using namespace std;


struct RBTNode;
RBTNode *CreatRBTNode(int _key, bool _isNil, int _color);
RBTNode *CreatNilNode();
RBTNode *Nil= CreatNilNode();

typedef struct RBTNode{
	int color = 1;		//0 is Black and 1 is Red!
	RBTNode *parent=NULL, *lchild= NULL, *rchild = NULL;
	int key = 0;
	bool isNil = false;
}RBTNode;
RBTNode *CreatNilNode() {
	RBTNode *newNode = (RBTNode*)malloc(sizeof(RBTNode));
	newNode->color = 0;
	newNode->isNil = true;
	newNode->key = 0;
	newNode->lchild = newNode->rchild = newNode->parent = NULL;
	return newNode;
}
RBTNode *CreatRBTNode(int _key, bool _isNil = false,int _color=1) {
	RBTNode *newNode = (RBTNode*)malloc(sizeof(RBTNode));
	newNode->key = _key;
	newNode->isNil = _isNil;
	newNode->lchild = CreatNilNode();
	newNode->rchild = CreatNilNode();
	newNode->lchild->parent = newNode->rchild->parent = newNode;
	newNode->color = _color;
	newNode->parent = NULL;
	return newNode;
}

RBTNode *RBTSearch(RBTNode *tree, RBTNode *last, int key) {		//Which Node the new Node will insert
	if (tree == NULL) return NULL;
	if (tree->isNil == true) return last;
	if (key > tree->key) return RBTSearch(tree->rchild, tree, key);
	else return RBTSearch(tree->lchild, tree, key);
}

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
	RBTNode *parent = node->parent, *left = node->lchild, *right = node->rchild;
	if (node->parent != NULL) {
		if (node == parent->lchild) {
			parent->lchild = left;
		}
		else {
			parent->rchild = left;
		}
	}
	else { left->parent = node->parent; }
	node->parent = left;
	node->lchild = left->rchild;
	left->parent = parent;
	left->rchild->parent = node;
	left->rchild = node;

	
}

void flipNodeColor(RBTNode *node) {
	if (node->lchild->color == node->rchild->color&&node->lchild->color == 1) {
		if (node->parent != NULL) {
			node->color = 1;
		}
		node->lchild->color = node->rchild->color = 0;
	}
}
void insertToBLACKParent(RBTNode *node, RBTNode *insertP) {
	if (insertP->color != 0)cout << "insertToBLACKParent have a wrong." << endl;
	if (node->key < insertP->key) { insertP->lchild = node; node->parent = insertP; }
	if (node->key >= insertP->key) { insertP->rchild = node; node->parent = insertP; }
	flipNodeColor(insertP);
}

void insertToREDParent(RBTNode *node, RBTNode *insertP,RBTNode *uncle) {
	if (uncle == NULL) {
		if (node->key > insertP->key) {
			insertP->rchild = node;
			node->parent = insertP;
		}
		else {
			insertP->lchild = node;
			node->parent = insertP;
		}
	}else
	if (uncle->color == 1) {//insertP is grantpa's lchild
		if (insertP == insertP->parent->lchild) {
			if (node->key < insertP->key) { //node is insertP's lchild 
				insertP->parent->color = 1;
				insertP->color = 0;
				insertP->lchild = node;
				node->parent = insertP;
				RightRotation(insertP->parent);
			}
			else {				//node is insertP's rchild
				insertP->rchild = node;
				node->parent = insertP;
				LeftRotation(insertP);//insertP is the new insert node
				insertP->parent->lchild = Nil;
				insertToREDParent(insertP, node, uncle);
			}
		}else {
			if (insertP == insertP->parent->rchild) { //node is insertP's rchild 
				insertP->parent->color = 1;
				insertP->color = 0;
				insertP->rchild = node;
				node->parent = insertP;
				RightRotation(insertP);
			}
			else {						//node is insertP's lchild
				insertP->lchild = node;
				node->parent = insertP;
				RightRotation(insertP);//insertP is the new insert node
				insertP->parent->rchild = Nil;
				insertToREDParent(insertP, node, uncle);
			}
		}
		
	}
	else {
		if (insertP == insertP->parent->rchild) {
			if (node->key > insertP->key) {
				insertP->rchild = node;
				node->parent = insertP;
				insertP->color = 0;
				insertP->parent->color = 1;
				LeftRotation(insertP->parent);
			}
			else {
				insertP->lchild = node;
				node->parent = insertP;
				RightRotation(insertP);
				node->rchild = Nil;
				insertToREDParent(insertP, node, uncle);
			}
		}
		else {
			if (node->key < insertP->key) {
				node->parent = insertP;
				insertP->lchild = node;
				insertP->color = 1;
				node->color = 0;
				RightRotation(insertP->parent);
			}
			else {
				node->parent = insertP;
				insertP->rchild = node;
				LeftRotation(insertP);
				node->lchild = CreatNilNode();
				node->lchild->parent = node;
				insertToREDParent(insertP, node, uncle);
			}
		}
	}

	return;
}
RBTNode *RBTInsert(int key, RBTNode *root) {
	if (root == NULL) {
		root = CreatRBTNode(key); root->color = 0;
	}
	else {
		RBTNode *insertPosition = RBTSearch(root,NULL, key), *uncle = NULL, *parent = insertPosition->parent;
		RBTNode *node = CreatRBTNode(key);
		if (insertPosition->color == 0) { insertToBLACKParent(node, insertPosition); }
		else {
			if (parent->parent != NULL) {
				if (parent->lchild == insertPosition) {
					uncle = parent->rchild;
				}
				else {
					uncle = parent->lchild;
				}
				insertToREDParent(node, insertPosition, uncle);
			}
			insertToREDParent(node, insertPosition, NULL);
		}
	}
	return root;
}

void RBTDelete(RBTNode &node) {

}




void printRBT(RBTNode *root) {
	if (root->isNil == true) return;
	printRBT(root->lchild);
	cout<<root->key<<"|"<<endl;
	printRBT(root->rchild);

}


int main()
{
	int a,n;
	ifstream in("C:\\Users\\Dabney\\Desktop\\DATA.txt");
	in >> n>>a;
	RBTNode *root = RBTInsert(a,NULL);
	for (int i = 0; i < n-1; i++) {
		in >> a;
		RBTInsert(a, root);
	}
	printRBT(root);
	system("PAUSE");
    return 0;
}

