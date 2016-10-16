// TestingBipartiteness.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<string>

#define MAXNODE 100 
#define MAXARC 200


using namespace std;

typedef struct ArcNode {
	int adjvex = 0;
	ArcNode* next=NULL;
}ArcNode;

typedef struct VNode {
	string data;
	int color;//0 is blue,1 is red
	ArcNode* fistArc = NULL;
}VNode;

typedef struct AdjcentGraph {
	VNode node[MAXNODE];
	ArcNode arc[MAXARC];
	int numOfNode = 0, numOfArc = 0;
}AdjcentGraph;
AdjcentGraph graph;

//int blue[MAXNODE], red[MAXNODE];

						/*Data format: [numofnode] [numofarc] 
					 	 *[information about node]						   | here is no information
					 	 *[information about arc:start vertex ,end vertex] | no square bracket*/

void creatGraph() {
	ifstream in("C:\\Users\\Dabney\\Documents\\WorkPlace\\TestCase\\Bipartiteness.txt");
	in >> graph.numOfNode >> graph.numOfArc;
	for (int i = 0; i < graph.numOfNode; i++) {
		graph.node[i].fistArc = NULL;
		graph.node[i].color = 2;
	}
	for (int i = 0; i < graph.numOfArc; i++) {
		int head=0, tail=0;
		in >> head >> tail;
		ArcNode *arc = (ArcNode*)malloc(sizeof(ArcNode));
		arc->next = graph.node[head].fistArc;
		graph.node[head].fistArc = arc;
		arc->adjvex = tail;
		arc = (ArcNode*)malloc(sizeof(ArcNode));
		arc->next = graph.node[tail].fistArc;
		graph.node[tail].fistArc = arc;
		arc->adjvex = head;
	}
}
bool visted[MAXNODE] = { false };

void BFS(AdjcentGraph &g, int start) {
	VNode *queue[MAXNODE];
	queue[0] = &g.node[start];
	int tail = 1, head = 0;		//tail point to an empty postion
	
	queue[0]->color = 0;
	while (tail > head) { 
		ArcNode *tmp;
		tmp = queue[head]->fistArc;
		while (tmp != NULL) {
			if (visted[tmp->adjvex] == true) {			//is bipartiteness?
				switch (queue[head]->color) {
				case 0:if (g.node[tmp->adjvex].color == 0) {
					cout << "this is not a bipartitioness graph!" << endl;
					return;
				}; break;
				case 1:if (g.node[tmp->adjvex].color == 1) {
					cout << "this is not a bipartitioness graph!" << endl;
					return;
				}; break;
				default:cout << "There is a mistake" << endl;
				}
			}
			if (visted[tmp->adjvex] == false) {
				visted[tmp->adjvex] = true;
				switch (queue[head]->color) {
					case 0:g.node[tmp->adjvex].color = 1; break;
					case 1:g.node[tmp->adjvex].color = 0; break;
					default:cout << "There is a mistake" << endl;
					}
				queue[tail++] = &g.node[tmp->adjvex];
			}
			tmp = tmp->next;
		}
		head++;
	}	
}



int main()
{
	creatGraph();
	for (int i = 0; i < graph.numOfNode ;i++) {
		if(visted[i]==false)
		BFS(graph, i);
	}
	string color;
	for (int i = 0; i < graph.numOfNode; i++) {
		switch (graph.node[i].color){
		case 0:color = "Blue"; break;
		case 1:color = "Red"; break;
		default:cout << "i am not a bipartiteness graph!";
			system("PAUSE");
			return 0;
		}
		cout <<i << " belong to " << color << endl;
	}
	system("PAUSE");
    return 0;
}

