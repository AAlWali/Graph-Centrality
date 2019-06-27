#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <bits/stdc++.h>

using namespace std;

void Closeness_Centrality();
vector<int> shortest_distance(int src,vector <list<pair<int,int> > > adj_list);

int main()
{
    Closeness_Centrality();
    return 0;
}

void Closeness_Centrality()
{
    int node,edge,src,des,weight;
    cin >> node>>edge;
    vector <list<pair<int,int> > > adj(node,list<pair<int,int> >());
    for(int i=0;i<edge;i++)
    {
        cin >> src >> des >> weight;
        adj[src].push_back({des,weight});
		adj[des].push_back({src,weight});
    }
    vector<int> dess(node);
    for(int i=0;i<node;i++)
    {
        dess = shortest_distance(i,adj);
        cout <<fixed << setprecision(12) << (node-1.0)/(accumulate(dess.begin(), dess.end(), 0))<<"\n";
    }
}

vector<int> shortest_distance(int src,vector <list<pair<int,int> > > adj_list)
{
    priority_queue<pair<int, pair<int, int> >,
				   vector<pair<int, pair<int, int> > >,
				   greater<pair<int, pair<int, int> > > >nodes_q;

	// Create d and p arrays
	int n = adj_list.size();
	vector<int> d(n, 10000000);
	vector<int> p(n, -1);

	nodes_q.push({0, {src, src}});

	while(!nodes_q.empty()){
		pair<int,pair<int, int> > cur_p = nodes_q.top();
		nodes_q.pop();
		int cur_node = cur_p.second.first;
		int cur_prev_node = cur_p.second.second;
		int cur_dis = cur_p.first;

		if (d[cur_node] != 10000000)
			continue;

		d[cur_node] = cur_dis;
		p[cur_node] = cur_prev_node;

		// Add the nodes connected to current one
		for (list<pair<int,int> > ::iterator it = adj_list[cur_node].begin();it != adj_list[cur_node].end();it++)
        {
            int next_node = (*it).first;
			int weight = (*it).second;
			if (d[next_node] != 10000000)
				continue;
			nodes_q.push({cur_dis + weight,
						  {next_node, cur_node}});
        }
	}

	return d;
}
