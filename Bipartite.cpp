// Bipartite matching

#include <bits/stdc++.h>
using namespace std;

#define N 100000

vector<int> edges[N];
vector<int> rev_edges[N]; // To find maximum independent set.
int pre[N];
bool visited[N];

bool DFS(int idx){
    // Bipartite matching
    if(visited[idx]) return false;
    visited[idx]=true;
    for(int i=0; i<edges[idx].size(); i++){
        int next=edges[idx][i];
        if(pre[next]==-1 || (!visited[pre[next]] && DFS(pre[next]))){
            pre[next]=idx;
            return true;
        }
    }
    return false;
}

// fill(visited, visited+n, 0); 을 매번 해줘야 한다. N^2이 나오는 게 정상
// if(DFS(i)) result++; 이렇게 유량을 구함.