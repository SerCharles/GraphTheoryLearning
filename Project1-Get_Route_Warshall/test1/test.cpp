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
 * @reviser	Zhang Mingdong
 * @date	2017/10/10
 * @e-mail:	zhangmd14@mails.tsinghua.edu.cn
 */
#include <iostream>
#include <cstdio>
#include "USSolver.h"
#include<fstream>
std::ofstream data("out.txt");
int n,v,e;
int test_start[110] = { 0 }, test_end[110] = { 0 };
int forward_table_v[105] = { 0 }, forward_table_e[10010] = { 0 }, forward_table_value[10010] = { 0 }, matrix[105][105] = { 0 };
int route[105][10010][105] = { 0 }, route_sum[105] = { 0 }, route_end[105][10010] = { 0 },route_length[105][10010] = { 0 };
bool visit[105][10010][105] = { 0 }, valid[105][10010] = { 0 };
void copy(int i1, int j1, int i2, int j2)
{
	int i;
	for (i = 1; i <= route_length[i1][j1]; i++)
	{
		route[i2][j2][i] = route[i1][j1][i];
		visit[i2][j2][route[i1][j1][i]] = 1;
	}
	route_length[i2][j2] = route_length[i1][j1];
	route_end[i2][j2] = route_end[i1][j1];
}
void merge(int i1,int j1,int i2,int j2)
{
	int i,t=route_length[i1][j1];
	for (i = 2; i <= route_length[i2][j2]; i++)
	{
		int present = route[i2][j2][i];
		if (visit[i1][j1][present] != 0)
		{
			if (present == i1&& visit[i1][j1][present]==1)
			{
					route_length[i1][j1]++;
					route[i1][j1][route_length[i1][j1]] = i1;
					route_end[i1][j1] = i1;
					visit[i1][j1][present]++;
			}
			valid[i1][j1] = 1;
			break;
		}
		else
		{
			route_length[i1][j1]++;
			route[i1][j1][route_length[i1][j1]] = present;
			route_end[i1][j1] = present;
			visit[i1][j1][present] = 1;
		}
	}
}
void Floyd()
{
	int i, j, k,w;
	for (i = 0; i < v; i++)
	{
		for (j = 0; j < v; j++)
		{
			for (k = 1; k <= route_sum[j]; k++)
			{
				if (route_end[j][k] == i&&valid[j][k]==0)
				{
					for (w = 1; w <= route_sum[i]; w++)
					{
						if (w != route_sum[i])
						{
							route_sum[j]++;
							copy(j, k, j, route_sum[j]);
							merge(j, route_sum[j], i, w );
						}
						else merge(j, k, i, w);
					}
				}
			}
		}
	}

}
void print(int begin, int edge, int num)
{
	data << "[";
	int i;
	for (i = 1; i <= num; i++)
	{
		if (i != num)
		{
			data << route[begin][edge][i] << " -> ";
		}
		else
		{
			data << route[begin][edge][i] << "]";
		}
	}
}
int judge(int begin, int edge, int num)
{
	int i, j;
	for (i = 1; i < edge; i++)
	{
		int whether = 0;
		for (j = 1; j <= num; j++)
		{
			if (route[begin][edge][j] != route[begin][i][j]) whether = 1;
		}
		if (whether == 0) return 0;
	}
	return 1;
}
void get_result(int a, int b)
{
	int i,j,whether=0;
	for (i = 1; i <= route_sum[a]; i++)
	{
		for (j = 1; j <= route_length[a][i]; j++)
		{
			if (j != 1 && route[a][i][j] == b)
			{
				if (judge(a, i, j))
				{
					print(a, i, j);
					whether = 1;
				}
				break;
			}
		}
	}
	if (whether == 0) data << "NO PATH" << std::endl;
	else data << "\n";
}
void switch_to_matrix()
{
	int i, j = 0;
	for (i = 0; i < e; i++)
	{
		while (1)
		{
			if (i < forward_table_v[j + 1])
			{
				matrix[j][forward_table_e[i]] = forward_table_value[i];
				break;
			}
			else j++;
		}
	}
}
void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream)
{
	//读入，预处理
	{
		int a, b, i,j;
		inputStream >> v >> e;
		for (i = 0; i <= v; i++)
		{
			int p;
			inputStream>>p;
            forward_table_v[i] = p;
		}
		for (i = 0; i < e; i++)
		{
			int p;
			inputStream >> p;
			forward_table_e[i] = p;
			forward_table_value[i] = 1;
		}
			switch_to_matrix();
		inputStream >> n;
		for (i = 1; i <= n; i++)
		{
			inputStream >> test_start[i] >> test_end[i];
		}
		for (i = 1; i <= v; i++) matrix[i][i] = 0;
		memset(route, -1, sizeof(route));
		for (i = 0; i < v; i++)
		{
			for (j = 0; j < v; j++)
			{
				if (matrix[i][j] == 1)
				{
					route_sum[i]++;
					route[i][route_sum[i]][1] = i; route[i][route_sum[i]][2] = j;
					route_length[i][route_sum[i]] = 2;
					route_end[i][route_sum[i]] = j;
					visit[i][route_sum[i]][i] = 1;
					visit[i][route_sum[i]][j] = 1;
				}
			}
		}
	}
	//warshell
	Floyd();
	//得到结果
	int i, j, k;
	for (i = 1; i <= n; i++) get_result(test_start[i], test_end[i]);
}



int main(int argc, char *argv[])
{
	//可在此更改测试文件
    std::string fileName = "Test101.txt"; 
    
    USSolver unofficialSolver(fileName);
    const std::string unofficialAnswer = unofficialSolver.GetAnswer();

    //std::cout << "Your Answer:" << unofficialAnswer << std::endl;
	//while (1);
	return 0;
}