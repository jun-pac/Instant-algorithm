#include <bits/stdc++.h>

using namespace std;

#define INF 1000000007
#define N 10000

vector<int> edges[N];
int flow[N][N]; // Use map if N is larger than 20000
int capa[N][N];
int levels[N];
bool visited[N];
int work[N];
 
void add_edge(int a, int b, int c){ // edge a->b (c)
    // this is NOT bidirectional!
	edges[a].push_back(b); flow[a][b]=0; capa[a][b]=c;
	edges[b].push_back(a); flow[b][a]=0; capa[b][a]=0;
	// If capa accumulate, 
    //edges[a].push_back(b); flow[a][b]=0; capa[a][b]=c;
	//edges[b].push_back(a); flow[b][a]=0; capa[b][a]=0;
}
 
void level_BFS(int s){
	fill(visited,visited+N,false);
	queue<pair<int,int>> q;
	q.push({s,0});
	while(!q.empty()){
		int idx=q.front().first;
		int level=q.front().second;
		q.pop();
		if(visited[idx]) continue;
		levels[idx]=level;
		visited[idx]=true;
		for(int i=0; i<edges[idx].size(); i++){
			int next=edges[idx][i];
			if(!visited[next] && capa[idx][next]>flow[idx][next]){
				q.push({next,level+1});
			}
		}
	}
}
 
int main_DFS(int idx, int f, int t){
	visited[idx]=true;
	if(idx==t || f==0) return f;
	for(int &i=work[idx]; i<edges[idx].size(); i++){
		int next=edges[idx][i];
		if(!visited[next] && levels[next]==levels[idx]+1 && capa[idx][next]>flow[idx][next]){
			int f_temp=main_DFS(next,min(f,capa[idx][next]-flow[idx][next]),t);
			if(f_temp==0) continue;
			flow[idx][next]+=f_temp;
			flow[next][idx]-=f_temp;
			return f_temp;
		}
	}
	return 0;
}
 
int DINIC(int s, int t){
	int result=0;
	while(true){
		levels[t]=-1;
		level_BFS(s);
		if(levels[t]==-1) break;
 
		fill(work,work+N,0);
		while(true){
			fill(visited,visited+N,false);
			int f_temp=main_DFS(s,INF,t);
			if(f_temp==0) break;
			result+=f_temp;
		}
	}
	return result;
}
 
// 유량이 남은 모든 정점을 탐색
void cut_DFS(int idx){
	if(visited[idx]) return;
	visited[idx]=true;
	for(int i=0; i<edges[idx].size(); i++){
		int next=edges[idx][i];
		if(!visited[next] && capa[idx][next]>flow[idx][next]) cut_DFS(next);
	}
}