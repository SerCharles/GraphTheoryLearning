/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2014, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    main.cpp
 * @brief   Write your own code here.
 * 
 * @version 1.1
 * @author  Jackie Pang
 * @e-mail: 15pengyi@gmail.com
 * @date    2012/10/11
 * @reviser	Gong Chao
 * @date	2014/10/13
 * @e-mail:	gcdofree@gmail.com
 */

#include <iostream>
#include<ostream>
#include "USSolver.h"
std::ofstream out("data_out.txt"); 
class edge
{
public:
	int point1, point2;
	int value;
public:
	edge() :point1(-1), point2(-1), value(0){}
	~edge(){}
	void set(int p1,int p2,int vl);
};
void edge::set(int p1, int p2, int vl)
{
	point1 = p1; point2 = p2; value = vl;
}
int v, e, ans = 0, ans_edge[60] = { 0 };
int list_v[60] = { 0 }, list_e[60] = { 0 }, list_value[60] = { 0 };
edge map[60];
bool visit[60] = { 0 };
int get_min()
{
	int i,min=2017013569,min_nm;
	for (i = 0; i < e; i++)
	{
		bool i1 = visit[map[i].point1], i2 = visit[map[i].point2];
		bool i3 = i1 & i2, i4 = i1 | i2;
		if (i3 == 0 && i4 == 1 && map[i].value < min)
		{
			min = map[i].value;
			min_nm = i;
		}
	}
	return min_nm;
}
void prim()
{
	visit[0] = 1;
	int i,min;
	for (i = 1; i <= v - 1; i++)
	{
		min = get_min();
		int i1 = map[min].point1, i2 = map[min].point2;
		visit[i1] = 1; visit[i2] = 1;
		ans += map[min].value;
		ans_edge[i] = min;
	}
}
void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream)
{
	inputStream >> v >> e;
	int i,j;
	for (i = 0; i <= v; i++) inputStream >> list_v[i];
	for (i = 0; i < e; i++) inputStream >> list_e[i];
	for (i = 0; i < e; i++) inputStream >> list_value[i];
	for (i = 0; i < v; i++)
	{
		for (j = list_v[i]; j < list_v[i + 1]; j++)
		{
			map[j].set(i, list_e[j], list_value[j]);
		}
	}
	prim();
	for (i = 1; i <= v - 1; i++)
	{
		outputStream << "[" << map[ans_edge[i]].point1 << " -> " << map[ans_edge[i]].point2 << "]";
		out<< "[" << map[ans_edge[i]].point1 << " -> " << map[ans_edge[i]].point2 << "]";
	}
	outputStream << " " << ans<<"\n";
	out << " " << ans<<"\n";
}



int main(int argc, char *argv[])
{
	//可在此更改测试文件
    std::string fileName = "test101.txt"; 
    
    USSolver unofficialSolver(fileName);
    const std::string unofficialAnswer = unofficialSolver.GetAnswer();

    std::cout << "Your Answer:" << unofficialAnswer << std::endl;
}