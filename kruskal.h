#pragma once
#define MAXN 2000
#define INF 99999999
#include <QString.h>
typedef struct {
	int x;
	int y;
	int number;
	bool isChoose;
}point;

typedef struct {
	int weight;
	bool isOpen;//是否开放
	bool isChoose;//是否被选择
	point* front;
	point* rear;
}Edge;

#define maxWeight 50
#define minWeight 0
#define maxNodenum 8
#define edgeNum 28

class KRUSKAL 
{
public:
	int dad[maxNodenum+1];
	Edge edges[edgeNum];
	point allpoint[maxNodenum];

	void sort();
	void merge(int x, int y);
	int getfather(int x);
	void initdad();
	void initpoint();
	void initedge();
};