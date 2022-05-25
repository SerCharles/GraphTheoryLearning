#include<iostream>
#include<cmath>
#include"edge.h"
#include<fstream>
using namespace std;
int n, sum = 0,ans=2017013569;
int matrix[101][101] = { 0 };
int best[101] = { 0 };
int flag[101] = { 0 };
edge* routes[5001] ;
void scan_and_switch();
void search(int t);
int judge_hamilton();
int get_answer();
int min(int a, int b);
ifstream data_in ("data_in.txt");
ofstream data_out("data_out.txt");
int main(int argv, char* argc[])
{
	scan_and_switch();
	search(n);
	data_out << ans << endl;
	for (int i = 1; i <= n; i++) data_out << "[" << routes[best[i]]->point_1 << "," << routes[best[i]]->point_2 << "] ";
	return 0;
}
void scan_and_switch()
{
	data_in >> n;
	int i,j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			data_in >> matrix[i][j];
		}
	}
	for (i = 1; i < n; i++)
	{
		for (j = i + 1; j <= n; j++)
		{
			sum++;
			routes[sum] = new edge(i, j, matrix[i][j]);
		}
	}
	for (i = 1; i <= sum; i++)
	{
		for (j = i+1; j <= sum; j++)
		{
			if (routes[i]->value > routes[j]->value)
			{
				edge* temp = new edge(0,0,0);
				temp = routes[i];
				routes[i] = routes[j];
				routes[j] = temp;
			}
		}
	}
	for (i = 1; i <= n; i++) flag[i] = i;
}
void search(int t)
{
	flag[t]++;
	for (int i = t + 1; i <= n; i++) flag[i] = flag[t] + i - t;
	int a = get_answer();
	if (judge_hamilton())
	{
		if (ans > a)
		{
			ans = a;
			for (int i = 1; i <= n; i++) best[i] = flag[i];
		}
	}
	if (a>ans||flag[t]+n-t>=sum)
	{
		if (t == 1) return;
		else search(t - 1);
	}
	else
	{
		search(n);
	}
}
int judge_hamilton()
{
	int times[101] = { 0 };
	for (int i = 1; i <= n; i++)
	{
		times[routes[flag[i]]->point_1]++;
		times[routes[flag[i]]->point_2]++;
	}
	for (int i = 1; i <= n; i++)
	{
		if (times[i] != 2) return 0;
	}
	return 1;
}
int min(int a, int b)
{
	if (a < b) return a;
	else return b;
}
int get_answer()
{
	int num = 0;
	for (int i = 1; i <= n; i++) num += routes[flag[i]]->value;
	return num;
}
