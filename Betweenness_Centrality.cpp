#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <bits/stdc++.h>
 
 
using namespace std;

 
void Betweenness_Centrality();
vector<list<int> > shortest_distance_for_Betweenness(int src, vector <list<pair<int, int> > > adj_list);
 
void rec_func(vector<list<int> >dess, int node, double *size, double *num, int input);
 
 
int main()
{
 
			Betweenness_Centrality();
 
	return 0;
}
 
void Degree_Centrality()
{
	string line, Node, Edge, Src, Des, Weight;
	int i;
	map <string, int> n;
	ifstream myfile("input.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		while (getline(myfile, line))
		{
			Src = line.substr(0, line.find(" "));
			i = line.find(" ");
			Des = line.substr(line.find(" ") + 1, line.find(" ", i + 1) - i - 1);
			n[Src] ++;
			n[Des] ++;
		}
		myfile.close();
	}
	map <string, int> ::iterator it;
	for (it = n.begin(); it != n.end(); it++)
	{
		cout << it->first << " : " << it->second << "\n";
	}
}
 
 
void Betweenness_Centrality()
{
	string line, Node,Src, Des, Weight;
	int i, node, src, des, weight, Edge;
 
 
 
	cin >> node;
	cin >> Edge;
	vector <list<pair<int, int> > > adj(node, list<pair<int, int> >());
 
	for(int i=0;i<Edge;i++)
	{
 
		cin >> src;
		cin >> des;
		cin >> weight;
 
		adj[src].push_back({ des,weight });
		adj[des].push_back({ src,weight });
 
 
	}
 
 
	vector<list<int> > dess(node);
	for (int input = 0; input < node; input++)
	{
 
		double output = 0;
		double c_of;
 
		for (int j = 0; j < node; j++) // from
		{
 
			dess = shortest_distance_for_Betweenness(j, adj); // get shortest paths from source to all next nodes
			double size = 0;
			double num = 0;
 
			for (int i = j + 1; i < node; i++) // to
			{
 
				size = 0;
				num = 0;
				rec_func(dess, i, &size, &num, input);
 
				if (size == 0)
					output = 0;
				else
					output += num / size;
 
 
				c_of = output;
			}
		}
 
		cout.precision(12);
		cout << fixed << c_of ;
 
		if ((input + 1) != node)
			cout << '\n';
 
 
 
	}
}
 
 vector<list<int> > shortest_distance_for_Betweenness(int src, vector <list<pair<int, int> > > adj_list)
{
	priority_queue<pair<int, pair<int, int> >,
		vector<pair<int, pair<int, int> > >,
		greater<pair<int, pair<int, int> > > >nodes_q;
 
	// Create d and p arrays
	int n = adj_list.size();
	vector<int> d(n, 10000000);
	vector<list<int> > p(n, list<int>());
	nodes_q.push({ 0, {src, src} });
 
	while (!nodes_q.empty())
	{
		pair<int, pair<int, int> > cur_p = nodes_q.top();
		nodes_q.pop();
 
		pair<int, pair<int, int> > top;
		if (!nodes_q.empty())
		{
			top = nodes_q.top();
 
		}
 
 
 
		while ((!nodes_q.empty()) && (cur_p.first == top.first) && (cur_p.second.first == top.second.first))//you have the same shortest distances and yous are in the same node
		{
			if (d[cur_p.second.first] > cur_p.first)
			{
				p[cur_p.second.first].push_back(nodes_q.top().second.second); // push parents
			}
			nodes_q.pop();
 
 
 
			if (!nodes_q.empty())
			{
				top = nodes_q.top();
 
			}
		}
 
		int cur_node = cur_p.second.first;
		int cur_prev_node = cur_p.second.second;
		int cur_dis = cur_p.first;
 
		if (d[cur_node] != 10000000)
			continue;
 
		d[cur_node] = cur_dis;
		if (cur_prev_node != src)
			p[cur_node].push_back(cur_prev_node);
 
		// Add the nodes connected to current one
		for (list<pair<int, int> > ::iterator it = adj_list[cur_node].begin(); it != adj_list[cur_node].end(); it++)
		{
			int next_node = (*it).first;
			int weight = (*it).second;
			if (d[next_node] != 10000000)
				continue;
			nodes_q.push({ cur_dis + weight,
						  {next_node, cur_node} });
		}
	}
 
	return p;
}
void rec_func(vector<list<int> >dess, int node, double *size, double *num, int input)
{
 
 
	if (dess[node].empty())
	{
 
		*(size) += 1;
		return;
 
	}
	for (std::list<int>::iterator iterator = dess[node].begin(); iterator != dess[node].end(); ++iterator)
	{
		if (*iterator == input)
		{
			if (dess[*iterator].size() == 0)
				*(num) += 1;
			else
			    *(num) += dess[*iterator].size();
		}
 
		rec_func(dess, *iterator, size, num, input);
 
	}
 
}
