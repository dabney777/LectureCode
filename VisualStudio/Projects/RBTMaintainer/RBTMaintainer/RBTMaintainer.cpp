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
			if (parent == NULL)return NULL;
			if (parent->right == this) return parent->left;
			return parent->right;
		}
		
	};
	RBTNode *root=NULL, *NIL=new RBTNode();
	void colorChange(RBTNode *a, RBTNode*b) {
		bool tmp = a->color;
		a->color = b->color;
		b->color = tmp;

	}
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
	RBTNode *brother(RBTNode *node) {
		RBTNode *b;
		if (node->parent == NULL) return NULL;
		if (node->parent->left == node) b = node->parent->right; else b = node->parent->left;
		return b;
	}
	void doubleRED(RBTNode* node) {
		RBTNode *parentNode = node->parent;
		if (parentNode != RED)return;
		RBTNode *bro = brother(parentNode);
		if (bro->color == RED) {
			
			bro->color = BLACK;
			parentNode->color = BLACK;
			parentNode->parent->color = RED;
			doubleRED(parentNode->parent);
			return;
		}
		//if (node->parent->color == RED) { doubleRED(node->parent); return; }
		colorChange(parentNode, parentNode->parent);
		if (parentNode == parentNode->parent->left) {
			rightRotate(parentNode);	
		}
		else { leftRotate(parentNode); }

		if (parentNode == root) {
			parentNode->color = BLACK;
			flipcolor(parentNode);
			return;
		}
	
		if(parentNode->parent->color!=BLACK) doubleRED(parentNode);


	}

	void flipcolor(RBTNode *node) {
		RBTNode *nodeGrandpa = node->parent->parent;
		if (nodeGrandpa==NULL)
		{
			return;

		}
		if (nodeGrandpa->left->color == RED&&nodeGrandpa->right->color == RED)
		{
			nodeGrandpa->left->color = BLACK;
			nodeGrandpa->right->color = BLACK;
			if (nodeGrandpa != root) {
				nodeGrandpa->color = RED;
				
				if (nodeGrandpa->parent->color == RED) { 
					flipcolor(nodeGrandpa);
					
					//node->parent->color = BLACK;
					//if (node == node->parent->left) node->parent->right->color = RED; else node->parent->left->color = RED;
				}
			}
			return;
		}
		if (nodeGrandpa->left->color != nodeGrandpa->right->color) {
			if (node->key > nodeGrandpa->key) {//node和他的parent在右侧
				if (node->key > node->parent->key) {
					node->parent->color = BLACK;
					nodeGrandpa->color = RED;
					leftRotate(node->parent);
				}
				else {
					rightRotate(node);
					flipcolor(node->right);
				}
			}
			else {//在左侧
				if (node->key > node->parent->key) { leftRotate(node); 
				flipcolor(node->left);
				}
				else {
					node->parent->color = BLACK;
					nodeGrandpa->color = RED;
					rightRotate(node->parent);
				}
			}
		
		}


	}
	string outPutColor(RBTNode *node) {
		if (node != NULL)
		{
			return node->color ? "BLACK" : "RED";
		}
		else {
			return "I am NULL";
		}
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
		if (node->key > insertP->key) insertP->right = node; else insertP->left = node;
		node->parent = insertP;
		flipcolor(node);//insertP's parent must be BLACK unless it is root
			
			/*
			if (insertP->color == BLACK) { insertToBLACKPoint(insertP, node); }
		else {//Black Nil Uncle
			if(insertP==insertP->parent->left){
				if (node->key > insertP->key) {//II:insert to RBN's right
					node->parent = insertP;
					insertP->right = node;
					leftRotate(node);
					node->left = NIL;
					insertP->left = insertP->right = NIL;
					insertToREDPoint(node, insertP);
				}
				else {//I:insert to RBN's left
					node->parent = insertP;
					insertP->left = node;
					insertP->color = BLACK;
					node->grandparent()->color = RED;
					rightRotate(insertP);
					
				}
			}else{
				if (node->key > insertP->key) {//III:insert to BBR's right
					insertP->right = node;
					node->parent = insertP;
					insertP->color = BLACK;
					node->grandparent()->color = RED;
					leftRotate(insertP);
				}
				else {
					insertP->left = node;
					node->parent = insertP;
					rightRotate(node);
					node->right = NIL;
					insertP->left = insertP->right = NIL;
					insertToREDPoint(node, insertP);
					//IV:insert to BBR's left
				}
			}
			
		}*/
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
	RBTNode* search(int key,RBTNode *tree) {
		if (tree == NULL) return NULL;
		if (tree->key == key) return tree;
		if (key > tree->key) {//all comparision like this is > and <=
			if (tree->right == NIL) {
				return  NULL;
			}
			else { return search(key, tree->right); }
		}
		else
		{
			if (tree->left == NIL) {
				return NULL;
			}
			else {
				return search(key, tree->left);
			}
		}


	}
	RBTNode *findMaxNode(RBTNode *node){
		if (node->right == NIL) { return node; }
		else {
			return findMaxNode(node->right);
		}
	}
	RBTNode *findMinimumNode(RBTNode *node){
		if (node->left == NIL) { return node; }
		else {
			return findMinimumNode(node->left);
		}
	}
	RBTNode *findPrecursor(RBTNode *node) {
		if (node->left == NIL) { return NULL; }
		return findMaxNode(node->left);
	}
	RBTNode *findSucceed(RBTNode *node){
		if (node->right == NIL) { return NULL; }
		return findMinimumNode(node->right);
	}
	RBTNode *findBrother(RBTNode *node) {
		if (node->parent == NULL) return NULL; else {
			if (node->parent->left == node) {
				return node->parent->right;
			}
			else {//node->parent->right == node
				return node->parent->left;
			}
		}
	}
	void deleteDoubleNILBLACKNode(RBTNode *node) {
		RBTNode *pa = node->parent, *br = findBrother(node);
		if (br == NULL) return;
		if (br->color == RED&&br!=NIL) {
			br->color = pa->color;
			pa->color = BLACK;
			if (node == pa->left) {
				pa->left = NIL;
				leftRotate(br);//与node所在位置相同
			}
			else {//node == pa->right
				pa->right = NIL;
				rightRotate(br);
			}
			
		}
		else {//br->color == BLACK
			br->color = RED;
			if (pa->color == RED) { pa->color = BLACK; return; }
			else {
				deleteDoubleNILBLACKNode(pa);
			}

		}


	}
	void delete1SonNode(RBTNode *node) {
		RBTNode *child=NULL;
		if (node->left != NIL) {
			child = node->left;
		}
		if (node->right != NIL) {
			child = node->right;
		}
		if (child == NULL) {
		
		}
		else {
			if (child->color == RED) {
				child->color = BLACK;
				child->parent = node->parent;
				if (node->parent->left == node) {
					node->parent->left = child;
				}
				else {//node->parent->right == node
					node->parent->right = child;
				}
				free(node);
			}
			else {//child->color == BLACK
				cout << "I have a wrong" << endl;
			}
		}
		}
	void delete0SonNode(RBTNode *node) {
		if (node->color == RED) {
			//do nothing
		}
		else {//node->color == BLACK
			deleteDoubleNILBLACKNode(node);
		}
		
		if (node->parent->left == node) {
			node->parent->left = NIL;
		}
		if (node->parent->right == node){
			node->parent->right = NIL;
		}

		}
	void deleteNode(int data) {
		RBTNode *node = search(data, root), *dead;
		if (node == NULL) {
			cout << "Iam running!" << endl;
			return;
		}

		if (node->left != NIL) { 
			dead = findPrecursor(node); 
			node->key = dead->key;
			if (dead->left != NIL) { delete1SonNode(dead); }
			else { delete0SonNode(dead); }
		}
		else {//node->left == NIL
			if (node->right != NIL) {
				dead = findSucceed(node);
				node->key = dead->key;
				if (dead->right != NIL) { delete1SonNode(dead); }
				else { delete0SonNode(dead); }
			}
			else {//node->right ==NIL
				if (node == root) { root = NULL; return ; }
				delete0SonNode(node);
			}
		}


	}
public:
	RBTNode *RBTSearch(int key) {
		return search(key, root);
	}
	void insert(int x) {
		NIL->color = BLACK;
		RBTNode * newnode = creatNewNode(x);
		if (root == NULL) { root = newnode; root->color = BLACK; root->left = root->right = NIL; }
		else {
			insertRBT(root, newnode);
		}
	}
	void deleteRBTNode(int x) {

		deleteNode(x);
	}

	void print(RBTNode *node,ofstream &out) {
		if (node == NULL) { cout << "I am an empty tree" << endl; }
		else {
			
			
			if (node->right != NIL)	print(node->right, out);

			RBTNode *i = node->parent;
			while (i != NULL) { out << "|\t"; i = i->parent; }
			out << node->key << "\t" << outPutColor(node) << "\t";
			if (node->parent != NULL) out << endl; else out << "\t\t\t\tI am ROOT" << endl;


			
			if (node->left != NIL)	print(node->left, out);
			
		}
	}
	void RBTPrint(ofstream &out) {
		
		print(root,out); }
};

	

int main() {
	ifstream in(".\\DATA.txt");
	ofstream out;
	out.open(".\\DATAOUT.txt");
	int n,c;
	in >> n;
	RBT rbt;
	for (int i = 0; i < n; i++) {
		in >> c;
		
		rbt.insert(c);
	}
	rbt.RBTPrint(out);
	cout << "--------------------------------------------------" << endl;
	cout << "IF you want TEST delete function" ;
	in.close();
	system("PAUSE");
	/*for (int i = 0; i < 800; i++) {
		for(int j =0;j<35;j++)//用于删除重复值
		rbt.deleteRBTNode(i);
	}*/
	rbt.deleteRBTNode(7);
	rbt.deleteRBTNode(17);
	rbt.deleteRBTNode(1);
	out.close();
	out.open(".\\DATAafterDelete.txt");
	out << "\n\n======================================\n删除7,17,1之后：\n";
	rbt.RBTPrint(out);
	
	system("PAUSE");
	return 0;
};
