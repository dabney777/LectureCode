// Cut-Vertex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "string"
#include <fstream>
#define MAXNODE 100
using namespace std;

//adjacency list for undirected graph
typedef struct ArcNode {									
	int adjvex;
	ArcNode* nextarc;
}ArcNode;

typedef struct VNode {
	string data;
	bool visted;
	bool isCut = false;
	ArcNode* firstarc;
}VNode;

typedef struct GraphAdjcent{											
	VNode adjList[MAXNODE];
	int nodesNum, arcsNum;
}GraphAdjcent;

GraphAdjcent adjGraph;									//adjcentlist is adjgraph.adjList

void CreatGraph() {
	int nodesNum, arcsNum;
	cout << "please input nodes Num:" << endl;
	cin >> nodesNum;
	cout << "please input arcsNum:" << endl;
	cin >> arcsNum;
	
	adjGraph.nodesNum = nodesNum;
	adjGraph.arcsNum = arcsNum;
	for (int i = 0; i < adjGraph.nodesNum; ++i) {		//initialize all Node
		adjGraph.adjList[i].firstarc = NULL;

	}
	
	cout << "plese input nodes information:(here is empty ,do not entry anything now)" << endl;
	for (int i = 0; i < adjGraph.nodesNum; ++i) {
		//cin >> adjcentlist.AdjList[i].data;
		
	}
	cout << "please input arcs informantion using formula like v1,v2:" << endl;
	for (int i = 0; i < adjGraph.arcsNum; ++i) {
		if(i!=0) cout << "then:" << endl;
		cout << ">>";
		int j, k;
		ifstream in("C:\\Users\\Dabney\\Desktop\\graphdataSet.txt");
		//scanf_s("%d,%d",&j,&k);
		
		ArcNode* arcj = (ArcNode*)malloc(sizeof(ArcNode));
		arcj->adjvex = k;
		arcj->nextarc = adjGraph.adjList[j].firstarc;
		adjGraph.adjList[j].firstarc = arcj;					//vertex[i] has been added edge

		ArcNode* arck = (ArcNode*)malloc(sizeof(ArcNode));
		arck->adjvex = j;
		arck->nextarc = adjGraph.adjList[k].firstarc;
		adjGraph.adjList[k].firstarc = arck;					//vertex[k] hase been added edge
	}
}

int DFScount=0;
int visted[MAXNODE];
int low[MAXNODE];
void DFS(GraphAdjcent &g,int v) {
	if (g.adjList[v].firstarc == NULL|| g.adjList[v].visted) return;
	g.adjList[v].visted = true;
	visted[v] = DFScount++;	
	low[v] = visted[v];
	ArcNode* arc = g.adjList[v].firstarc;
	for(;arc!=NULL;arc=arc->nextarc)	DFS(g, arc->adjvex);
	arc = g.adjList[v].firstarc;				//initialize arc for search minimum count
	for (; arc != NULL; arc = arc->nextarc) {
		if (low[arc->adjvex] < low[v]) low[v] = low[arc->adjvex];
	}
	arc = g.adjList[v].firstarc;				//initialize arc for search cut vertex
	for (; arc != NULL; arc = arc->nextarc) {
		if (low[arc->adjvex] >= visted[v])  g.adjList[v].isCut = true; 
	}
	
}
void findCut(GraphAdjcent g, int v,int c[]) {
	DFS(g, v);
	for (int i = 0; i < g.nodesNum; ++i) {
		if (g.adjList[i].isCut) c[i]++;
	}
}

int main()
{
	CreatGraph();
	int cutCount[MAXNODE] = { 0 };
	findCut(adjGraph, 0,cutCount);
	findCut(adjGraph, 1,cutCount);
	for (int i = 0; i < adjGraph.nodesNum; ++i) {
		if (cutCount[i]>1) cout<<"The node ["<<i<<"] is a cut-vertex!"<<endl;
	}

	system("PAUSE");
    return 0;
}