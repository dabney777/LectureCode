// OptimalBinarySearchTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <String>
#include <vector>

using namespace std{

class OptimaBST {
private:
	typedef struct MatrixNode {
		int start, end, root;
		double WPL;
	}MatrixNode;
	vector<string> words;
	double *probability;
	double C(int start,int end,MatrixNode **matrix) {
		if (start > end)return 0.0;
		else return matrix[end-start][start].WPL;
	}
	double sigmaWPL(int start, int end, double p[]) {
		double sum=0;
		for (int i = start; i <= end; ++i) {
			sum += p[i];
		}
		return sum;
	}
	MatrixNode** constructTable(vector<string> words, double probability[]) {
		int amount = words.size(),root;
		MatrixNode **matrix = new MatrixNode*[amount];
		double min;
		for (int i = 0; i < amount; i++) {
			matrix[i] = new MatrixNode[amount];
		}
		for (int i = 0; i < amount; i++) {
			for (int j = 0; j < amount; j++) {
				if (j+i > amount - 1 ) continue;
				matrix[i][j].start = j;
				matrix[i][j].end = j + i;//include the endth number and first number like plant-tree problem
				if (i == 0) { 
					matrix[i][j].root = j; 
					matrix[i][j].WPL = probability[j];
				}
				else {
					min = C(matrix[i][j].start+1, matrix[i][j].end, matrix)+ 1;
					for (int k = matrix[i][j].start; k <= matrix[i][j].end; ++k) {
						double tmp=C(matrix[i][j].start, k-1, matrix)+C(k+1,matrix[i][j].end,matrix);
						if (tmp <= min) {
							matrix[i][j].root = k; 
							matrix[i][j].WPL = tmp + sigmaWPL(matrix[i][j].start, matrix[i][j].end, probability);
							min = tmp;
						}
					}
				}
			}
		}
		return matrix;
	}
	int findChild(int start,int end,MatrixNode **matrix){
		if (end - start < 0) return -1;
		return matrix[end - start][start].root;
	}

public:
	typedef struct Tree
	{
		int self;
		Tree *l, *r;
	}Tree;
	
	OptimaBST(vector<string> words, double probability[]) {
		this->words = words;
		this->probability = probability;
	}
	Tree * constructTree(int start,int end) {
		Tree *tRoot = new Tree;
		MatrixNode**matrix = constructTable(words, probability);
		tRoot->self = findChild(start, end, matrix);
		
		if (tRoot->self==-1) return NULL;

		tRoot->l=constructTree(start, tRoot->self - 1);
		
		tRoot->r=constructTree( tRoot->self + 1, end);

		return tRoot;
	}
	void printT(Tree * t,int i,ofstream &out) {
		
		string a;
		a.assign(i, '|');
		if (t == NULL) return;
		printT(t->l,i+1,out);
		if(t!=NULL) out <<a<< words.at(t->self) << endl;
		printT(t->r,i+1,out);
		
	}
	void printBST() {
		ofstream out;
		out.open("DATAOUT.txt", ofstream::out);
		MatrixNode**matrix = constructTable(words, probability);

		int amount = words.size();
		Tree *t=constructTree(0, amount-1);
		printT(t,0,out);
		for (int i = 0; i < amount; i++) {
			for (int j = 0; j < amount; j++) {
				cout << matrix[i][j].WPL << "  ";
			}
			cout << endl;
		}
	
		out.close();
	}
	

};

vector<string> splitString(string s,const string separator) {
	vector <string> result;
	string::size_type pos1, pos2;
	pos2 = s.find(separator);
	pos1 = 0;
	while (string::npos != pos2) {
		result.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + separator.size();
		pos2 = s.find(separator, pos1);
	}
	if (pos1 != s.length()) {
		result.push_back(s.substr(pos1));
	}
	return result;
}

int main()
{
	fstream file("DATA.txt");
	ifstream in;
	in.open("DATA.txt", ifstream::in);
	char line[256];
	in.getline(line, 256, '\n');
	const char *c = " ";
	vector<string> words = splitString(line, c);
	int amount = words.size();
	cout << "The number of words is : " << amount << endl;
	
	double *probability = new double[amount];
	for (int i = 0; i < amount; i++) {
		double tmp;
		in >> tmp;
		probability[i] = tmp;
	}
	OptimaBST *BST = new OptimaBST(words, probability);
	BST->printBST();

	system("pause");
    return 0;
}

}
