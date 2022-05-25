#include<iostream>
#include<vector>
using namespace std;
#define MAX 201400226
int min(int a, int b)
{
	if (a < b) return a;
	return b;
}
class edge
{
public:
	int begin, end, max, flow,type;
	edge():flow(0),type(1) {}
	~edge() {}
};
class point
{
public:
	int num;
	bool whether_end,visit;
	vector<edge*> link;
	point() :whether_end(0),visit(0) {}
	~point(){}
};
vector<edge*> route;
int n, s, t,num_edge,ans=0,m;
point v[1020];
edge e[2020];
void network_flow(int now)
{
	int i;
	if (now == t)
	{
		int i,min=MAX;
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
			else route[i]->flow-=min;
		}
	}
	for (i = 0; i < v[now].link.size(); i++)
	{
		int c_forth = v[now].link[i]->max - v[now].link[i]->flow;
		int c_back = v[now].link[i]->flow;
		int c_begin = v[now].link[i]->begin;
		int c_end= v[now].link[i]->end;
		if (now == c_begin&&v[c_end].visit==0&&c_forth>0)
		{
			int nova = c_end;
			v[nova].visit = 1;
			v[now].link[i]->type = 1;
			route.push_back(v[now].link[i]);
			network_flow(nova);
			v[nova].visit = 0;
			route.pop_back();
		}
		else if(now==c_end&&v[c_begin].visit==0&&c_back>0)
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
int main()
{
	cin >> n >>m>>s>>t;
	num_edge = m;
	int i;
	for (i = 1; i <= n; i++)
	{
		v[i].num = i;
	}
	for (i = 1; i <= m; i++)
	{
		cin >> e[i].begin >> e[i].end >> e[i].max;
		v[e[i].begin].whether_end = 1;
		v[e[i].begin].link.push_back(&e[i]);
		v[e[i].end].link.push_back(&e[i]);
	}
	for (i = 1; i <= n; i++)
	{
		if (v[i].whether_end == 0&&i!=t)
		{
			num_edge++;
			e[num_edge].begin = i;
			e[num_edge].end = t;
			e[num_edge].max = MAX;
			v[i].link.push_back(&e[num_edge]);
			v[t].link.push_back(&e[num_edge]);
		}
	}
	v[s].visit = 1;
	network_flow(s);
	for (i = 0; i < v[s].link.size(); i++)
	{
		ans += v[s].link[i]->flow;
	}
	cout << ans<<endl;
	for (i = 1; i <= m; i++) cout << e[i].begin << " " << e[i].end << " " << e[i].flow << endl;
	while (1);
	return 0;
}