#include <iostream>
#include <map>
#include <string>

using namespace std;

void Degree_Centrality();


int main()
{
    Degree_Centrality();
    return 0;
}

void Degree_Centrality()
{
    int Node,Edge,Src,Des,Weight;
    map <int,int> n;
    cin >> Node>>Edge;
    for (int i=0;i<Edge;i++)
    {
        cin >> Src >> Des >> Weight;
        n[Src] ++;
        n[Des] ++;
    }
    map <int,int> ::iterator it;
    for (it = n.begin();it != n.end();it++)
    {
            cout << it -> second<<"\n";
    }
}