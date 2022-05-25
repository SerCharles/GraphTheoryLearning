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
#include "USSolver.h"
#include<ostream>
std::ofstream out("data_out.txt");
int get_int(char a[], int i)
{
	int mult = 1,sum=0;
	for (int j = i - 1; j >= 0; j--)
	{
		sum += (a[j]-'0') * mult;
		mult *= 10;
	}
	return sum;
}
class edge
{
public:
	int number, length,max_pt,min_diji;
	int num_of_last, num_of_next, num_of_ancestor;
	int last[110] = { 0 }, next[110] = { 0 };
	int ancestor[110] = { 0 };
public:
	edge(int i,int j):number(i),length(j),num_of_last(0),num_of_next(0),num_of_ancestor(0),max_pt(0),min_diji(2017013569){}
	~edge(){}
	void input(char a[]);
	int judge();
	void renew();
};
int n,flag=0,answer;
int important_route[1100000][110] = { 0 }, queue[1100000] = { 0 }, stop[1100000] = { 0 };
int length_imp_route[110] = { 0 },num_of_imp_route=0;
int time_delay[110] = { 0 };
edge* scan[110];
edge* list[110];
int visit[110] = { 0 }, visit_search[110] = { 0 };
void edge::input(char a[])
{
	int length = strlen(a);
	char c[110] = { 0 };
	strcpy(c, a);
	int flag[101] = { 0 };
	flag[0] = -1;
	c[length] = ',';
	int i,sum=0;
	for (i = 0; i <= length; i++)
	{
		if (c[i] == ',')
		{
			sum++;
			flag[sum] = i;
		}
	}
	num_of_last = sum;
	for (i = 1; i <= sum; i++)
	{
		last[i] = get_int(&c[flag[i - 1] + 1], flag[i] - flag[i - 1] - 1);
	}
}
int edge::judge()
{
	int i, j;
	for (i = 1; i <= num_of_last; i++)
	{
		if (visit[last[i]] == 0) return 0;
	}
	return 1;
}
void sort()
{
	int i,j;
	for (j = 0; j <= n; j++)
	{
		for (i = 0; i <= n; i++)
		{
			if (scan[i]->judge()&&visit[i]==0)
			{
				visit[i] = 1;
				list[j] = scan[i];
				break;
			}
		}
	}
}
void get_next()
{
	int i, j, k;
	for (i = 0; i <= n - 1; i++)
	{
		for (j = 0; j <= n - 1; j++)
		{
			for (k = 1; k <= scan[j]->num_of_last; k++)
			{
				if (scan[j]->last[k] == scan[i]->number)
				{
					scan[i]->num_of_next++;
					scan[i]->next[scan[i]->num_of_next] = scan[j]->number;
				}
			}
		}
	}
}
void edge::renew()
{
	int i;
	for (i = 1; i <= num_of_next; i++)
	{
		int a = length + max_pt;
		if (a > scan[next[i]]->max_pt)
		{
			scan[next[i]]->max_pt = a;
			memset(scan[next[i]]->ancestor, 0, 110);
			scan[next[i]]->num_of_ancestor = 1;
			scan[next[i]]->ancestor[1] = number;
		}
		else if (a == scan[next[i]]->max_pt)
		{
			scan[next[i]]->num_of_ancestor++;
			scan[next[i]]->ancestor[scan[next[i]]->num_of_ancestor] = number;
		}
	}
}
void PTrenew()
{
	int i;
	for (i = 0; i < n; i++) list[i]->renew();
}
void lastrenew()
{
	int i;
	list[n]->min_diji = list[n]->max_pt;
	for (i = n - 1; i >= 0; i--)
	{
		int j;
		for (j = 1; j <= list[i]->num_of_next; j++)
		{
			if (scan[list[i]->next[j]]->min_diji - list[i]->length < list[i]->min_diji) list[i]->min_diji = scan[list[i]->next[j]]->min_diji - list[i]->length;
		}
	}
}
void copy(int receive, int give)
{
	int i;
	for (i = 1; i <= length_imp_route[give]; i++) important_route[receive][i] = important_route[give][i];
}
void search()
{
	int head = 1,tail = 1;
	queue[head] = n;
	important_route[head][1] = n;
	length_imp_route[head] = 1;
	while (head <= tail)
	{
		int i;
		if (scan[queue[head]]->num_of_ancestor == 0) stop[head] = 1;
		for (i = 1; i <= scan[queue[head]]->num_of_ancestor; i++)
		{
			int a = scan[scan[queue[head]]->ancestor[i]]->number;
			tail++; 
			queue[tail] = a;
			copy(tail, head);
			length_imp_route[tail] = length_imp_route[head]+1;
			important_route[tail][length_imp_route[tail]] = queue[tail];
		}
		head++;
	}
	num_of_imp_route = tail;
}
void USSolver::Solve(std::istream &inputStream, std::ostream &outputStream)
{
	inputStream >> n;
	int i;
	for (i = 0; i <= n-1; i++)
	{
		int a, b;
		char c[300],temp;
		inputStream >> a >> b;
		scan[i] = new edge(a, b);
		temp=inputStream.get();
		if (temp != '\n')
		{
			inputStream >> c;
			scan[i]->input(c);
		}
	}
	scan[n] = new edge(n, 0);
	scan[n]->min_diji = 0;
	get_next();
	for (i = 0; i < n; i++)
	{
		if (scan[i]->num_of_next == 0)
		{
			scan[i]->num_of_next = 1;
			scan[i]->next[1] = n;
			scan[n]->num_of_last++;
			scan[n]->last[scan[n]->num_of_last] = i;
		}
	}
	sort();
	PTrenew();
	lastrenew();
	answer = scan[n]->max_pt;
	for (i = 0; i <= n; i++) time_delay[i] = scan[i]->min_diji-scan[i]->max_pt;
	visit_search[n] = 1;
	num_of_imp_route = 1;
	search();

	outputStream << answer << std::endl; out << answer << std::endl;
	for (i = 1; i <= num_of_imp_route; i++)
	{
		if (stop[i] == 1)
		{
			int j;
			outputStream << "["; out << "[";
			for (j = length_imp_route[i]; j >= 2; j--)
			{
				outputStream << important_route[i][j] << " -> "; out << important_route[i][j] << " -> ";
			}
			outputStream << "end]" << std::endl; out << "end]" << std::endl;
		}
	}
	for (i = 0; i < n; i++)
	{
		outputStream << time_delay[i] << std::endl; out << time_delay[i] << std::endl;
	}
}



int main(int argc, char *argv[])
{
	//可在此更改测试文件
    std::string fileName = "Test101.txt"; 
    
    USSolver unofficialSolver(fileName);
    const std::string unofficialAnswer = unofficialSolver.GetAnswer();

    std::cout << "Your Answer:" << unofficialAnswer << std::endl;
}