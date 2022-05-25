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
#include<iostream>
#include<vector>
#include<fstream>
#include "USSolver.h"
#define MAX 201400226
int min(int a, int b)
{
	if (a < b) return a;
	return b;
}
class edge
{
public:
	int begin, end, max, flow, type;
	edge() :flow(0), type(1) {}
	~edge() {}
};
class point
{
public:
	int num;
	bool whether_end, visit;
	std::vector<edge*> link;
	point() :whether_end(0), visit(0) {}
	~point() {}
};
std::vector<edge*> route;
int n, s, t, num_edge, ans = 0, m;
point v[110];
edge e[3000];
void network_flow(int now)
{
	int i;
	if (now == t)
	{
		int i, min = MAX;
		for (i = 0; i < route.size(); i++)
		{
			int c;
			if (route[i]->type == 1) c = route[i]->max - route[i]->flow;
			else c = route[i]->flow;
			if (c < min) min = c;
		}
		for (i = 0; i < route.size(); i++)
		{
			if (route[i]->type == 1) route[i]->flow += min;
			else route[i]->flow -= min;
		}
	}
	for (i = 0; i < v[now].link.size(); i++)
	{
		int c_forth = v[now].link[i]->max - v[now].link[i]->flow;
		int c_back = v[now].link[i]->flow;
		int c_begin = v[now].link[i]->begin;
		int c_end = v[now].link[i]->end;
		if (now == c_begin && v[c_end].visit == 0 && c_forth>0)
		{
			int nova = c_end;
			v[nova].visit = 1;
			v[now].link[i]->type = 1;
			route.push_back(v[now].link[i]);
			network_flow(nova);
			v[nova].visit = 0;
			route.pop_back();
		}
		else if (now == c_end && v[c_begin].visit == 0 && c_back>0)
		{
			int nova = c_begin;
			v[nova].visit = 1;
			v[now].link[i]->type = -1;
			route.push_back(v[now].link[i]);
			network_flow(nova);
			v[nova].visit = 0;
			route.pop_back();
		}
	}
}
void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream)
{
	int a[60], b[60], maxa = 0, maxb = 0;
	inputStream >> n;
	int i;
	for (i = 1; i <= n; i++)
	{
		inputStream >> a[i] >> b[i];
		if (a[i] > maxa) maxa = a[i];
		if (b[i] > maxb) maxb = b[i];
	}
	for (i = 0; i < maxa + maxb + 2; i++)
	{
		v[i].num = i;
	}
	for (i = 1; i <= n; i++)
	{
		e[i].begin = a[i];
		e[i].end = maxa + b[i] + 1;
		e[i].max = 1;
		v[a[i]].link.push_back(&e[i]);
		v[maxa+b[i]+1].link.push_back(&e[i]);
	}
	s = maxa + maxb + 2;
	t = maxa + maxb + 3;
	v[s].num = s; v[t].num = t;
	for (i = 0; i <= maxa; i++)
	{
		n++;
		e[n].begin = s; e[n].end = i; e[n].max = 1;
		v[s].link.push_back(&e[n]);
		v[i].link.push_back(&e[n]);
	}
	for (i = maxa + 1; i <= maxa + maxb + 1; i++)
	{
		n++;
		e[n].begin = i; e[n].end = t; e[n].max = 1;
		v[t].link.push_back(&e[n]);
		v[i].link.push_back(&e[n]);
	}
	v[s].visit = 1;
	network_flow(s);
	for (i = 0; i < v[s].link.size(); i++) ans += v[s].link[i]->flow;

	for (i = 1; i <= n; i++)
	{
		if (e[i].flow == 1&&e[i].begin!=s&&e[i].end!=t&&e[i].end!=s&&e[i].end!=t)
		{
			outputStream << e[i].begin << " ";
			outputStream << e[i].end - 1 - maxa << "\n";
		}
	}
}



int main(int argc, char *argv[])
{
	//可在此更改测试文件
	std::string fileName = "test101.txt";

	USSolver unofficialSolver(fileName);
	const std::string unofficialAnswer = unofficialSolver.GetAnswer();

	std::cout << "Your Answer:" << unofficialAnswer << std::endl;
	while (1);
}