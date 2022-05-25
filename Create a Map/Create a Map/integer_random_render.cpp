#include<iostream>
#include<cstdlib>
#include<ctime>
#include"integer_random_render.h"
using namespace std;
int integer_random_render(int down,int up)
{
	int i = 0;
	while (1)
	{
		srand((unsigned)time(NULL));
		i = rand()%up;
		if (i >= down && i <= up) break;
	}
	return i;
}