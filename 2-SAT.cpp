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

// For 2-SAT
vector<int> r_scc_edges[N]; // reverse edges connecting sccs (in scc index)
vector<int> scc_element[N]; // Nodes of each scc
bool scc_fixed[N]; // whether the value of scc determined (initially set false)
bool scc_state[N]; // Determined scc value 
inline int t_idx(int i){return i<<1;}
inline int f_idx(int i){return (i<<1)+1;}
inline int inv_idx(int i){return i^1;}

// Set n before call init function.
void init_scc(){
    for(int i=0; i<n; i++) {edges[i].clear(), r_edges[i].clear();}
}

void init_sat(){
    init_scc();
    for(int i=0; i<n; i++) {r_scc_edges[i].clear(), scc_element[i].clear();}
    fill(scc_fixed, scc_fixed+n, false);
    fill(scc_fixed, scc_fixed+n, true);
}

// Build SAT edge for prop A or B // a=t_idx(A). b=t_idx(B);
// A and B could be same. Which means A is true.  
// Manually insert edges[b].push_back(inv_idx(b)); where B is false and b=t_idx(B)
void sat_edge(int a, int b){
    edges[inv_idx(a)].push_back(b);
    r_edges[b].push_back(inv_idx(a));
    if(a!=b){
        edges[inv_idx(b)].push_back(a);
        r_edges[a].push_back(inv_idx(b));
    }
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

// Update answers of 2-sat to scc_state. 
// fill(visited, visited+scc_cnt, false); before call this function.
// Set scc_cnt, r_scc_edges and scc_element before call this function.
bool r_scc_DFS(int idx, bool state){
    visited[idx]=true;
    bool new_state=false;
    for(int i=0; i<r_scc_edges[idx].size(); i++){
        if(!visited[r_scc_edges[idx][i]]){
            new_state=new_state||r_scc_DFS(r_scc_edges[idx][i], state);
        }
    }
    if(!scc_fixed[idx]){
        scc_fixed[idx]=true;
        scc_state[idx]=new_state;
    }
    else new_state=scc_state[idx];

    for(int i=0; i<scc_element[idx].size(); i++){
        int cur=scc_element[idx][i];
        int inv_scc=scc[inv_idx(cur)];
        scc_fixed[inv_scc]=true;
        scc_state[inv_scc]=!scc_state[idx];
    }
    return new_state;
}

