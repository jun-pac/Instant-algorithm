// Dijkstra algorithm

#include <bits/stdc++.h>

using namespace std;

#define N 200000

vector<pair<int,int>> edges[N]; // {idx, dist}
int min_dist[N];

void dijkstra(int s){
    priority_queue<pair<int,int>> pq;
    fill(min_dist,min_dist+N,-1);
	pq.push({0,s});
    while(!pq.empty()){
		int dist=-pq.top().first, idx=pq.top().second;
		pq.pop();
		if(min_dist[idx]!=-1) continue;
		min_dist[idx]=dist;
		for(int i=0; i<edges[idx].size(); i++){
			int next=edges[idx][i].first, n_dist=dist+edges[idx][i].second;
			if(min_dist[next]==-1) pq.push({-n_dist,next});
		}
	}
}

