#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Flight
{
 	public:
 		string flno;
 		int depcity;
		int arrcity;
		int price;
		int deptime,arrtime;

 		Flight(string fl,int city1,int city2,int pri,int dep,int arr){
 			flno=fl;
 			depcity=city1;
 			arrcity=city2;
 			price=pri;
 			deptime=dep;
 			arrtime=arr;
 		}
 		Flight(){

 		}
};

class Node
{
	public:
		int cost;
		int city;
		int tme;
		vector<Flight> v;
		Node(int i, int c, int t){
			cost = i;
			city = c;
			tme = t;
		}
		Node(){

		}
};

class myComparator
{
	public:
    	int operator() (const Node& f1, const Node& f2)
    	{
        	return f1.cost > f2.cost;
    	}
};

int minutes(int a){
	int x=a%100;
	a/=100;
	int y=a*60;
	return (x+y);
}

int cheapesttrip(vector< vector<Flight> > graph, int source, int destin, int dep, int arr){
	priority_queue<Node, vector<Node>, myComparator > pq;
	map<string, Flight> mp;
	Node node(0,source,dep-30);
	pq.push(node);
	while(!pq.empty()){
		Node n = pq.top();
		int cost_now = n.cost, location = n.city, ti = n.tme;
		vector<Flight> route = n.v;
		pq.pop();
		if (location==destin && ti<=arr)
		{
			return cost_now;
		}
		int earliest_dep = ti+30;
		for (int i = 0; i < graph[location].size(); ++i)
		{
			map<string, Flight> ::iterator it = mp.find(graph[location][i].flno);
			if (graph[location][i].deptime >= earliest_dep && graph[location][i].arrtime <= arr && it==mp.end())
			{
				Node x(cost_now+graph[location][i].price,graph[location][i].arrcity, graph[location][i].arrtime);
				route.push_back(graph[location][i]);
				x.v = route;
				pq.push(x);
				mp[graph[location][i].flno]=graph[location][i];
			}
		}
	}
	return -1;
}

int main()
{
	int nocities;
	cin>>nocities;

	vector< vector<Flight> > graph(nocities+1);

	int noflights;
	cin>>noflights;
	
	while(noflights > 0){
		int city1,city2,pri,dep,arr;
		string fl;
		cin>>city1>>city2>>dep>>arr>>fl>>pri;
		dep=minutes(dep);
		arr=minutes(arr);
		Flight f(fl,city1,city2,pri,dep,arr);
		graph[city1].push_back(f);
		noflights--;
	}

	int queries;
	cin>>queries;
	while(queries > 0){
		int city1,city2,dep,arr;
		cin >> city1 >> city2 >> dep >> arr;
		dep=minutes(dep);
		arr=minutes(arr);
		int ans = cheapesttrip(graph,city1,city2,dep,arr);
		cout << ans << "\n";
		queries--;
	}
	return 0;
}