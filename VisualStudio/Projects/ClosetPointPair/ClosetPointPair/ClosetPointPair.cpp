// ClosetPointPair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

template<typename T> void swapPoint(T &a, T &b) {
	T tmp = b;
	b = a;
	a = tmp;
}

class point {
public:
	double x=0, y=0, z=0;
	point() {};
	point(double a, double b,double c) {
		x = a;
		y = b;
		z = c;
	}
	point(const point &p) {						//copy constructor
		x = p.x;
		y = p.y;
		z = p.z;
	}
};

double distance(point a, point b) {
	return ((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z)); //distance's sqare 
}


int partition(point* p, int start, int end) {
	if (start >= end) return start;
	int i = start, j = end;
	double pivot = p[start].x;
	while (i < j) {
		while (p[j].x > pivot&&i<j)--j;
		while (p[i].x <= pivot&&i<j)++i;
		swapPoint<point>(p[i], p[j]);
	}
	return i;
}
void quickSort(point* p, int start, int end) {
	if (start >= end)return;
	int x = partition(p, start, end);
	quickSort(p, start, x - 1);
	quickSort(p, x + 1, end);

}
double findClosetPair(point* p, int start, int end) {
	
	if (end - start == 1) return distance(p[start], p[end]);
	if (end - start <= 0) return (double)999;
	int mid = start + (end - start) / 2;
	double left = findClosetPair(p, start, mid-1);
	double right = findClosetPair(p, mid, end);
	double segmentaryMin = left < right ? left : right;
	double x1 = p[mid].x - segmentaryMin, x2 = p[mid].x + segmentaryMin;
	int i, j;							//judeg point that in range or not
	for (i = start; p[i].x < x1&&i<end + 1; i++);
	for (j = i; p[j].x < x2&&j<end+1; j++);
	for(int k =i;k<j;k++)
	for (int l=i; l < j; l++) {
		if (distance(p[k], p[l] ) < segmentaryMin && k != l) segmentaryMin = distance(p[k], p[l]);
	}
	
	return segmentaryMin;
}
/*Data format:
*number of point /n
*firstpoint.x firstpoint.y firstpoint z /n
*then secondpoint.x,y,zetc*/
int main()
{	
	ifstream in("C:\\Users\\Dabney\\Desktop\\3DdataSet.txt");
	int pointNum;
	in >> pointNum;
	point* p = new point[pointNum];
	for (int i = 0; i < pointNum; i++) {	//creat point list
		double a, b, c;
		in >> a; in >> b; in >> c;
		p[i].x = a;
		p[i].y = b;
		p[i].z = c;
		
	}
	quickSort(p, 0 ,pointNum-1);
	cout<<"The closet distance in those points is :"<<sqrt( findClosetPair(p, 0, pointNum-1))<<endl;
	system("PAUSE");
    return 0;
}

