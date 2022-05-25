#ifndef EDGE_H
#define EDGE_H

class edge
{
public:
	int point_1, point_2;
	int value;
public:
	edge(int i,int j,int k):point_1(i),point_2(j),value(k){}
	~edge(){}
};
#endif
