
#include "stdafx.h"
#include <fstream>
#include <iostream>

#include <stdio.h>

#include <queue>

#include <vector>

#include <string.h>

#define inf 1000000





using namespace std;

#define INT_MAX 9998

int nextEdge[1000], firstEdge[1000], visited[1000], preEdge[1000], dis[1000], flow[1000];
bool vis[1000];
typedef struct edge {
	int from, to, cost, capacity;
	edge() {}
	edge(int from_, int to_, int cost_, int capacity_) :from(from_), to(to_), cost(cost_), capacity(capacity_) {}
}edge;
edge E[1000];
int edgeNum = 0;
void init() {
	memset(firstEdge, -1, sizeof(int));
	memset(nextEdge, -1, sizeof(int));
	memset(flow, 0, 1000 * sizeof(int));
}
void addEdge(int from_, int to_, int cost_, int capacity_) {
	nextEdge[edgeNum] = firstEdge[from_]; firstEdge[from_] = edgeNum; flow[edgeNum] = capacity_;
	E[edgeNum++] = edge(from_, to_, cost_, capacity_);
	nextEdge[edgeNum] = firstEdge[to_]; firstEdge[to_] = edgeNum; flow[edgeNum] = 0;
	E[edgeNum++] = edge(to_, from_, (-1)*cost_, 0);
}

bool SPFA(int s, int t, int nodeNum) {
	queue<int> q;
	q.push(s);
	int antenna;
	for (int i = 0; i < nodeNum; i++) {
		dis[i] = INT_MAX; vis[i] = false;
	}
	dis[s] = 0, preEdge[s] = -1, preEdge[t] = -1;
	while (!q.empty()) {
		antenna = q.front();
		q.pop();
		vis[antenna] = false;
		for (int i = firstEdge[antenna]; i != -1; i = nextEdge[i]) {
			int node = E[i].to;
			if (flow[i] > 0 && dis[node] > dis[antenna] + E[i].cost) {
				dis[node] = dis[antenna] + E[i].cost;
				preEdge[node] = i ^ 1;
				if (!vis[node]) {
					q.push(node);
					vis[node] = true;
				}

			}
		}

	}
	return preEdge[t] >= 0;
}


void main() {
	init();
	ifstream in;
	in.open("DATA.txt", ifstream::in);
	int dayNum, consume[1000], napkinPrice, fastTime, fastPrice, slowTime, slowPrice;
	in >> dayNum;
	cout << "总天数:" << dayNum << endl;
	for (int i = 0; i < dayNum; i++) {
		in >> consume[i];
		cout << "The " << i << "th day consumption: " << consume[i] << endl;
	}
	in >> napkinPrice >> fastTime >> fastPrice >> slowTime >> slowPrice;
	cout << "napkin price : " << napkinPrice << "\nfast time: " << fastTime << "\nfast price: " << fastPrice << "\nslow time: " << slowTime << "\nslow price : " << slowPrice << endl;
	int nodeNum = 2 * dayNum + 2;
	int source = 0, terminal = nodeNum - 1;
	for (int i = 1; i < dayNum + 1; i++) {
		//add X's edge
		if (i + fastTime < 2 * dayNum) {
			addEdge(source, i, 0, consume[i - 1]);
			if (i<dayNum + 1 - fastTime) addEdge(i, i + dayNum + fastTime, fastPrice, INT_MAX);
			if (i<dayNum + 1 - slowTime)addEdge(i, i + dayNum + slowTime, slowPrice, INT_MAX);
			if (i<dayNum) addEdge(i, i + 1, 0, INT_MAX);
		}
		//add Y's edge
		addEdge(source, i + dayNum, napkinPrice, INT_MAX);
		addEdge(i + dayNum, terminal, 0, consume[i - 1]);
	}
	int fee = 0;
	while (SPFA(source, terminal, nodeNum)) {
		/*for (int i = preEdge[terminal]; i != -1; i = preEdge[E[i].to]) {
		*	cout << E[i].from << "  " << E[i].to << endl;
		*	//if (E[i].from == 1) break;
		*	}
		*/
		int MIN = INT_MAX;
		for (int i = preEdge[terminal]; i != -1; i = preEdge[E[i].to]) {
			if (flow[i ^ 1]< MIN) {
				MIN = flow[i ^ 1];
			}
		}
		for (int i = preEdge[terminal]; i != -1; i = preEdge[E[i].to]) {
			//回边
			flow[i] += MIN;
			//去边
			flow[i ^ 1] -= MIN;

		}
		cout << "MIN: " << MIN << "  cost: " << dis[terminal] << endl;
		fee += dis[terminal] * MIN;
	}
	for (int i = 0; i < edgeNum; i++) {
		if (E[i].to == terminal) cout << "第" << E[i].from - 7 << "天使用了" << E[i].capacity - flow[i] << "张卫生纸;" << endl;

	}
	for (int i = 0; i < edgeNum; i++) {
		if (E[i].to <2 * dayNum + 1 && E[i].to>dayNum&&E[i].capacity>0 && E[i].from == source)cout << "第" << E[i].to - 7 << "天购买了" << E[i].capacity - flow[i] << "张卫生纸;" << endl;
	}
	for (int i = 0; i < edgeNum; i++) {
		if (E[i].to < dayNum + 1 && E[i].capacity - flow[i]>0) cout << "第" << E[i].to << "天送洗了" << E[i].capacity - flow[i] << "张卫生纸;" << endl;
	}
	for (int i = 0; i < edgeNum; i++) {
		if (E[i].from < 1 + dayNum && E[i].from>0)
			if (E[i].to < 1 + dayNum && E[i].to>0)
				if (E[i].from < E[i].to)
					cout << "第" << E[i].from << "天，保存了" << flow[i ^ 1] << "条毛巾" << endl;
	}
	for (int i = 0; i < edgeNum; i++) {
		if (E[i].from < 1 + dayNum && E[i].from>0 && E[i].to<2 * dayNum + 1 && E[i].to>dayNum&&E[i].cost == slowPrice)
			cout << "第" << E[i].from << "天，慢洗了" << flow[i ^ 1] << "个毛巾" << endl;
		if (E[i].from < 1 + dayNum && E[i].from>0 && E[i].to<2 * dayNum + 1 && E[i].to>dayNum&&E[i].cost == fastPrice)
			cout << "第" << E[i].from << "天，快洗了" << flow[i ^ 1] << "个毛巾" << endl;
	}



	cout << "总费用是" << fee;


	system("PAUSE");
}
