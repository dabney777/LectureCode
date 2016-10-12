// RBTMaintainer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#define N 10000
#define BLACK 1
#define RED 0
using namespace std;
class RBT {
private:
	struct RBTNode {
		RBTNode *left, *right, *parent;
		bool color;
		int key;
		RBTNode() {
			left = right = parent = NULL;
			color = RED;
			key = 0;
		}
		RBTNode *grandparent() {
			if (parent != NULL) {
				return parent->parent;
			}
			return NULL;
		}
		RBTNode *uncle() {
			if (parent->right == this) return parent->left;
			return parent->right;
		}
	};
	RBTNode *root=NULL, *NIL=new RBTNode();
	void rightRotate(RBTNode *node) {
		RBTNode *gp = node->grandparent();
		RBTNode *pa = node->parent;
		RBTNode *uncle = node->uncle();
		if (gp != NULL) {
			if (gp->left == pa) gp->left = node;
			else gp->right = node;
		}else { root = node; }
		node->parent = gp;//把新节点给接上
		
		pa->parent = node;
		pa->left = node->right;
		if (node->right != NIL) { node->right->parent = pa; }
		node->right = pa;
	}

	void leftRotate(RBTNode *node) {
		RBTNode *gp = node->grandparent();
		RBTNode *pa = node->parent;
		RBTNode *uncle = node->uncle();
		

		if (gp != NULL) {
			if (gp->left == pa) gp->left = node;
			else gp->right = node;
		}
		else { root = node; }
		node->parent = gp;//把新节点接入到插入节点中
		
		pa->parent = node;
		pa->right = node->left;
		if (node->left != NIL) { node->left->parent = pa; }
		node->left = pa;
	}

	void flipcolor(RBTNode *node) {
		if (node==NULL)
		{
			return;

		}
		if (node->left != NIL&&node->right != NIL&&node->left->color == RED&&node->right->color == RED)
		{
			node->left->color = BLACK;
			node->right->color = BLACK;
			if (node != root) {
				node->color = RED;
				flipcolor(node->parent);
			}
		}

	}
	string outPutColor(RBTNode *node) {
		return node->color ? "BLACK" : "RED";
	}
	RBTNode *creatNewNode(int data){
		RBTNode *node = new RBTNode();
		node->left = node->right = NIL;
		node->key = data;
		return node;
	}
	void insertToBLACKPoint(RBTNode *insertP,RBTNode *node){
		if (node->key > insertP->key) { 
			insertP->right = node; 
			node->parent = insertP;
		}
		else { 
		insertP->left = node; 
		node->parent = insertP;
		}
	}
	void insertToREDPoint(RBTNode *insertP, RBTNode *node) {
		flipcolor(insertP->parent);
		if (insertP->color == BLACK) { insertToBLACKPoint(insertP, node); }
		else {
			if(insertP==insertP->parent->left){
				if (node->key > insertP->key) {//II:insert to BRB's right
					node->parent = insertP;
					insertP->right = node;
					leftRotate(node);
					node->left = NIL;
					insertP->left = insertP->right = NIL;
					insertToREDPoint(node, insertP);
				}
				else {//I:insert to BRB's left
					node->parent = insertP;
					insertP->left = node;
					insertP->color = BLACK;
					node->grandparent()->color = RED;
					rightRotate(insertP);
					
				}
			}else{
				if (insertP == insertP->parent->left) {//IV:insert to BBR's left
					insertP->left = node;
					node->parent = insertP;
					rightRotate(node);
					node->right = NIL;
					insertP->left = insertP->right = NIL;
					insertToREDPoint(node, insertP);
				}
				else {
					insertP->right = node;
					node->parent = insertP;
					insertP->color = BLACK;
					node->grandparent()->color = RED;
					leftRotate(insertP);

					//III:insert to BBR's right
				}
			}
			
		}
	}
	void insertRBT(RBTNode *insertP, RBTNode *node) { 
		
		if (node->key > insertP->key) {
			if (insertP->right != NIL) { insertRBT(insertP->right, node); }
			else{
				if (insertP->color == BLACK) { insertToBLACKPoint(insertP, node); }
				if (insertP->color == RED) { insertToREDPoint(insertP, node); }
				return;
				//insert here
			}
		}
		else {
			if (insertP->left != NIL){insertRBT(insertP->left,node);	}
			else {
				if (insertP->color == BLACK) { insertToBLACKPoint(insertP, node); }
				if (insertP->color == RED) { insertToREDPoint(insertP, node); }
				return;
				//insert here
			}
		}
	}
public:
	void insert(int x) {
		NIL->color = BLACK;
		RBTNode * newnode = creatNewNode(x);
		if (root == NULL) { root = newnode; root->color = BLACK; root->left = root->right = NIL; }
		else {
			insertRBT(root, newnode);
		}
	}
	void print(RBTNode *node) {
		if (node == NULL) { cout << "I am an empty tree" << endl; }
		else {
			if (node->left != NIL)	print(node->left);
			cout << node->key << outPutColor(node) << endl;
			if (node->right != NIL)	print(node->right);
		}
	}
	void realPrint() { print(root); }
};


int main() {
	ifstream in("C:\\Users\\Dabney\\Desktop\\DATA.txt");
	int n,c;
	in >> n;
	RBT rbt;
	for (int i = 0; i < n; i++) {
		in >> c;
		rbt.insert(c);
			
	}
	
	rbt.realPrint();
	system("PAUSE");
	return 0;
};
