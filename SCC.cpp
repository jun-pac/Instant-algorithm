// 2-SAT
#include <bits/stdc++.h>
#define N 200000 // Upper bound for number of nodes in graph

using namespace std;

// For scc
vector<int> edges[N]; 
vector<int> r_edges[N];
int scc[N];
int order[N];
bool visited[N];
int cnt, scc_cnt; // Number of SCC's
int n; // Number of actual nodes in graph

// Set n before call init function.
void init_scc(){
    for(int i=0; i<n; i++) {edges[i].clear(), r_edges[i].clear();}
}


void DFS(int idx){
    visited[idx]=true;
    for(int i=0; i<edges[idx].size(); i++) if(!visited[edges[idx][i]]) DFS(edges[idx][i]);
    order[cnt]=idx; cnt++;
}

void r_DFS(int idx){
    visited[idx]=true;
    scc[idx]=cnt;
    for(int i=0; i<r_edges[idx].size(); i++) if(!visited[r_edges[idx][i]]) r_DFS(r_edges[idx][i]);
}

// Kosaraju's algorithm. Set n, edges, r_edges before call this function.
void get_scc(){
    fill(visited, visited+n, false), cnt=0;
    for(int i=0; i<n; i++) if(!visited[i]) DFS(i);
    fill(visited, visited+n, false), cnt=0;
    for(int i=n-1; i>=0; i--) if(!visited[order[i]]) {r_DFS(order[i]); cnt++;}
    scc_cnt=cnt;
}