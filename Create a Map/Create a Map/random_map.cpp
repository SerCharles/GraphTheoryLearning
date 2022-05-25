#include<iostream>
#include<fstream>
#include"integer_random_render.h"
using namespace std;
ofstream data_file("data.txt");
int n,sum = -1;
int matrix[10010][10100] = { 0 };
int forward_table_v[10010] = { 0 }, forward_table_e[1001000] = { 0 }, forward_table_value[1001000] = { 0 };
void switch_to_forward_table()
{
	int i,j;
	for (i = 1; i <= n; i++)
	{
		forward_table_v[i] = sum;
		int whether = 0;
		for (j = 1; j <= n; j++)
		{
			if (matrix[i][j])
			{
				sum++;
				forward_table_e[sum] = j;
				forward_table_value[sum] = matrix[i][j];
				whether = 1;
			}
		}
		if (whether == 0) forward_table_v[i] = sum;
	}
	forward_table_v[n + 1] = sum;
}
int main()
{
	int i,j;
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			int c = integer_random_render(1, 10000);
			matrix[i][j] = c % 2;
			for (int k = 1; k <= 10000; k++)
			{
				for (int l = 1; l <= 10000; l++);
			}
		}
	}
	switch_to_forward_table();
	data_file << n << " " << sum + 1 << endl;
	for (i = 1; i <= n + 1; i++) data_file << forward_table_v[i]<<" ";
	data_file << "\n";
	for (i = 0; i <= sum; i++) data_file << forward_table_e[i] << " ";
	return 0;
}