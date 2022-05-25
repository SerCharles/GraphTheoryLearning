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
struct point
{
	int num, father;
};
int v, e,n;
int list_head[23] = { 0 }, list_tail[55] = { 0 }, list_value[55] = { 0 };
int answer[23]= { 0 },length=0;
int visit[23] = { 0 };
point miniroute[23][23] = { 0 };
int question_head[103] = { 0 }, question_tail[103] = { 0 };
void dijikstra(int i);
int get_min(int i);
void renew(int time, int point);
void get_result(int head, int tail);
void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream)
{
	//读入与初始化
	inputStream >> v>> e;
	int i, j;
	for (i = 0; i <= v ; i++) inputStream >> list_head[i];
	for (i = 0; i < e; i++) inputStream >> list_tail[i];
	for (i = 0; i < e; i++) inputStream >> list_value[i];
	for (i = 0; i < v; i++)
	{
		for (j = 0; j < v; j++)
		{
			miniroute[i][j].num = 2017013569;
		}
	}
	inputStream >> n;
	for (i = 1; i <= n; i++) inputStream >> question_head[i] >> question_tail[i];


	//更新最短路
	for (i = 0; i < v; i++)
	{
		dijikstra(i);
		for (j = 0; j < v; j++)
		{
			visit[j] = 0;
		}
	}

	//输出
	for (j = 1; j <= n; j++)
	{
		if (miniroute[question_head[j]][question_tail[j]].num == 2017013569)
		{
			outputStream << "NO PATH\n";
			//out << "NO PATH\n";
		}
		else
		{
			get_result(question_head[j], question_tail[j]);
			outputStream << "[";
			//out<< "[";
			for (i = length; i >= 1; i--)
			{
				outputStream << answer[i];
				//out << answer[i];
				if (i != 1)
				{
					outputStream << " -> ";
					//out << " -> ";
				}
				else
				{
					outputStream << " " << miniroute[question_head[j]][question_tail[j]].num << "]\n";
					//out << " " << miniroute[question_head[j]][question_tail[j]].num << "]\n";
				}
			}
			for (i = 1; i <= v; i++) answer[i] = 0;
			length = 0;
		}
	}
}
void dijikstra(int i)
{
	miniroute[i][i].num = 0; miniroute[i][i].father = -1;
	int j;
	for (j = 1; j <= v; j++)
	{
		int t=get_min(i);
		renew(i, t);
		visit[t] = 1;
	}
}
void renew(int time, int point)
{
	int h = list_head[point], t = list_head[point + 1] - 1;
	int i;
	for (i = h; i <= t; i++)
	{
		int temp = list_tail[i];
		if (miniroute[time][temp].num > miniroute[time][point].num + list_value[i])
		{
			miniroute[time][temp].num = miniroute[time][point].num + list_value[i];
			miniroute[time][temp].father = point;
		}
	}
}
int get_min(int i)
{
	int j,num=2017013569,mini=-1;
	for (j = 0; j < v; j++)
	{
		if (miniroute[i][j].num < num&&visit[j]==0)
		{
			num = miniroute[i][j].num;
			mini = j;
		}
	}
	return mini;
}
void get_result(int head, int tail)
{
	int now = tail;
	while (now>=0)
	{
		length++;
		answer[length] = now;
		now = miniroute[head][now].father;
	}
}
int main(int argc, char *argv[])
{
	//可在此更改测试文件
    std::string fileName = "test101.txt"; 
    
    USSolver unofficialSolver(fileName);
    const std::string unofficialAnswer = unofficialSolver.GetAnswer();

    std::cout << "Your Answer:" << unofficialAnswer << std::endl;
}