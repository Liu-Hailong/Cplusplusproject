#include "kruskal.h"
#include <stdlib.h>
#include <math.h>
#include <QtGlobal>
#include <QTime>

void KRUSKAL::sort()//边的排序
{
	for (int i = 0; i < edgeNum; i++) 
		for (int j = i + 1; j < edgeNum; j++) 
			if (edges[i].weight > edges[j].weight) {
				Edge temp = edges[i];
				edges[i] = edges[j];
				edges[j] = temp;
			}
}

void KRUSKAL::merge(int x, int y)       //合并祖先
{
	int fx = getfather(x);
    int fy = getfather(y);
    dad[fy] = fx;
}

int KRUSKAL::getfather(int x)
{
	return dad[x] == x ? x : getfather(dad[x]);//查找祖先
}

void KRUSKAL::initdad()//初始化祖先数组
{
	for (int i = 0; i < maxNodenum+1; i++) 
		dad[i] = i;
}

void KRUSKAL::initpoint()//正多边形点阵
{
	int longth = 250;
	int longth_ = longth / sqrt(2.);
	allpoint[0].x = longth;
	allpoint[0].y = 0;
	allpoint[0].number = 1;
	allpoint[1].x = longth_;
	allpoint[1].y = longth_;
	allpoint[1].number = 2;
	allpoint[2].x = 0;
	allpoint[2].y = longth;
	allpoint[2].number = 3;
	allpoint[3].x = -longth_;
	allpoint[3].y = longth_;
	allpoint[3].number = 4;
	allpoint[4].x = -longth;
	allpoint[4].y = 0;
	allpoint[4].number = 5;
	allpoint[5].x = -longth_;
	allpoint[5].y = -longth_;
	allpoint[5].number = 6;
	allpoint[6].x = 0;
	allpoint[6].y = -longth;
	allpoint[6].number = 7;
	allpoint[7].x = longth_;
	allpoint[7].y = -longth_;
	allpoint[7].number = 8;
	for (int i = 0; i < maxNodenum; i++)
	{
		allpoint[i].isChoose = false;
	}
}

void KRUSKAL::initedge() {
	int num = 0;
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	for (int i = 0; i < maxNodenum; i++) {
		for (int j = i + 1; j < maxNodenum; j++) {
			edges[num].front = &allpoint[i];
			edges[num].rear = &allpoint[j];
			edges[num].isOpen = false;
			edges[num].isChoose = false;
			int weight = qrand() % maxWeight;
			bool is = rand() % 2;
			if (is)
				edges[num++].weight = weight;
			else
				edges[num++].weight = 0;
		}
	}
}