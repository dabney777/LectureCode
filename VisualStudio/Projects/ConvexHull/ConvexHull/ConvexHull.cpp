#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#include<fstream>
using namespace std;
#define PR 1e-7
#define N 25000
struct HullPoint
{
	double x, y, z;
	HullPoint() {}
	HullPoint(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {}
	HullPoint operator-(const HullPoint p) { return HullPoint(x - p.x, y - p.y, z - p.z); }
	HullPoint operator*(const HullPoint p) { return HullPoint(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x); }//vector product
	double operator^(const HullPoint p) { return x*p.x + y*p.y + z*p.z; }//dot product
};
struct fac
{
	int a, b, c;// num of 3 point in the same plain in convexhull
	bool ok;//is the plain is the final plain in convexhull
};
typedef struct T3dhull
{
	int n=-1;//初始点数
	HullPoint ply[N];//初始点
	int trianglecnt;//凸包上三角形数
	fac tri[N];//凸包三角形
	int vis[N][N];//点i到点j是属于哪个面
	double dist(HullPoint a) { return sqrt(a.x*a.x + a.y*a.y + a.z*a.z); }//两点长度
	double volume(HullPoint a, HullPoint b, HullPoint c, HullPoint d) { return (b - a)*(c - a) ^ (d - a); }//四面体有向体积*6
	double ptoplane(HullPoint &p, fac &f)//正：点在面同向
	{
		HullPoint m = ply[f.b] - ply[f.a], n = ply[f.c] - ply[f.a], t = p - ply[f.a];
		return (m*n) ^ t;
	}
	void deal(int p, int a, int b)
	{
		int f = vis[a][b];
		fac add;
		if (tri[f].ok)
		{
			if ((ptoplane(ply[p], tri[f]))>PR) dfs(p, f);
			else
			{
				add.a = b, add.b = a, add.c = p, add.ok = 1;
				vis[p][b] = vis[a][p] = vis[b][a] = trianglecnt;
				tri[trianglecnt++] = add;
			}
		}
	}
	void dfs(int p, int cnt)//维护凸包，如果点p在凸包外更新凸包
	{
		tri[cnt].ok = 0;
		deal(p, tri[cnt].b, tri[cnt].a);
		deal(p, tri[cnt].c, tri[cnt].b);
		deal(p, tri[cnt].a, tri[cnt].c);
	}
	bool same(int s, int e)//判断两个面是否为同一面
	{
		HullPoint a = ply[tri[s].a], b = ply[tri[s].b], c = ply[tri[s].c];
		return fabs(volume(a, b, c, ply[tri[e].a]))<PR
			&&fabs(volume(a, b, c, ply[tri[e].b]))<PR
			&&fabs(volume(a, b, c, ply[tri[e].c]))<PR;
	}
	void construct()//构建凸包
	{
		int i, j;
		trianglecnt = 0;
		if (n<4) return;
		bool tmp = true;
		for (i = 1; i<n; i++)//前两点不共点
		{
			if ((dist(ply[0] - ply[i]))>PR)
			{
				swap(ply[1], ply[i]); tmp = false; break;
			}
		}
		if (tmp) return;
		tmp = true;
		for (i = 3; i<n; i++)//前四点不共面
		{
			if (fabs((ply[0] - ply[1])*(ply[1] - ply[2]) ^ (ply[0] - ply[i]))>PR)
			{
				swap(ply[3], ply[i]); tmp = false; break;
			}
		}
		if (tmp) return;
		tmp = true;
		for (i = 2; i<n; i++)//前三点不共线
		{
			if ((dist((ply[0] - ply[1])*(ply[1] - ply[i])))>PR)
			{
				swap(ply[2], ply[i]); tmp = false; break;
			}
		}
		if (tmp) return;
		
		fac add;
		for (i = 0; i<4; i++)//构建初始四面体
		{
			add.a = (i + 1) % 4, add.b = (i + 2) % 4, add.c = (i + 3) % 4, add.ok = 1;
			if ((ptoplane(ply[i], add))>0) swap(add.b, add.c);
			vis[add.a][add.b] = vis[add.b][add.c] = vis[add.c][add.a] = trianglecnt;
			tri[trianglecnt++] = add;
		}
		for (i = 4; i<n; i++)//构建更新凸包
		{
			for (j = 0; j<trianglecnt; j++)
			{
				if (tri[j].ok && (ptoplane(ply[i], tri[j]))>PR)
				{
					dfs(i, j); break;
				}
			}
		}
		int cnt = trianglecnt;
		trianglecnt = 0;
		for (i = 0; i<cnt; i++)
		{
			if (tri[i].ok)
				tri[trianglecnt++] = tri[i];
		}
	}

}ConvexHull;

int main()
{
	
	cout << "please input point num"<<endl;
	ConvexHull hull;
	scanf_s("%d", &hull.n);
	
		int i;
		cout << "please input point's x,y,z:0;" << endl;
		for (i = 0; i < hull.n; i++)
			scanf_s("%lf,%lf,%lf", &hull.ply[i].x, &hull.ply[i].y, &hull.ply[i].z);
	
		hull.construct();
		cout << "The triangle in convexHull are:" << endl;
		for (i = 0; i < hull.trianglecnt; i++)cout << "(" << hull.tri[i].a << "," << hull.tri[i].b << "," << hull.tri[i].c << ")"<<endl;
		system("PAUSE");
	return 0;
}