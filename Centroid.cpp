// Centroid
#include <bits/stdc++.h>
#define N 200000
using namespace std;
 
vector<int> edges[N];
bool visited[N];
int sub_sz[N];
long long cnt;

int sz_DFS(int idx, int p){
	int result=1;
	for(int i=0; i<edges[idx].size(); i++){
		if(edges[idx][i]!=p && !visited[edges[idx][i]]){
			result+=sz_DFS(edges[idx][i], idx);
		}
	}
	return sub_sz[idx]=result;
}

int find_centroid(int idx, int p, int tot_sz){
	int result=idx;
	for(int i=0; i<edges[idx].size(); i++){
		int next=edges[idx][i];
		if(next!=p && !visited[edges[idx][i]] && sub_sz[next]>tot_sz/2){
			result=find_centroid(next,idx,tot_sz);
			break;
		}
	}
	return result;
}

void main_DFS(int idx, int p){
	int tot_sz=sz_DFS(idx,p);
	if(tot_sz==1) return;
	int cent=find_centroid(idx,p,tot_sz);
	visited[cent]=true;
	
	// Do something!
	
	for(int i=0; i<edges[cent].size(); i++){
		int next=edges[cent][i];
		if(!visited[next]) main_DFS(next,cent);
	}
	return;
}
