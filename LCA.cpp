// LCA (HLD based implementation)

#include <bits/stdc++.h>
#define INF 1000000007
#define N 200000

using namespace std;

vector<int> edges[N], child[N];
int parent[N], depth[N], in[N], top[N];
int sz[N];
int cnt; 

void DFS(int idx, int p){
	child[idx].reserve(edges[idx].size()-1);
	for(int i=0; i<edges[idx].size(); i++){
		int next=edges[idx][i];
		if(next!=p){
			child[idx].push_back(next);
			DFS(next,idx);
		}
	}
}

// parent[루트], top[루트], depth[루트]업데이트 해줘야 함.
void DFS1(int idx=0){
	sz[idx]=1;
	for(int i=0; i<child[idx].size(); i++){
		int next=child[idx][i];
		parent[next]=idx;
		depth[next]=depth[idx]+1;
		DFS1(next);
		sz[idx]+=sz[next];
		if(sz[next]>sz[child[idx][0]]) swap(child[idx][0],child[idx][i]);
	}
}

void DFS2(int idx=0){
	in[idx]=cnt;
	for(int i=0; i<child[idx].size(); i++){
		int next=child[idx][i];
		top[next]=(i==0?top[idx]:next);
		cnt++;
		DFS2(next);
	}
}

int get_LCA(int a,int b){ 
	while(top[a]!=top[b]){
		if(depth[top[a]]<depth[top[b]]) swap(a,b);
		a=parent[top[a]];
	}
	return (in[a]<in[b]?a:b);
}
