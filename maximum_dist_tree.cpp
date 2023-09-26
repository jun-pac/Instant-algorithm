#include <bits/stdc++.h>
#define endl '\n'
#define cediv(a,b) ((a)%(b)==0?((a)/(b)):((a)/(b))+1)
#define fi first
#define se second
#define pb push_back

using namespace std;

typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

template<typename T>
inline T umax(T &u, T v){return u = max(u, v);}
template<typename T>
inline T umin(T &u, T v){return u = min(u, v);}


vector<int> edges[100010];
int mx_dist[100010];
int mx_idx, mx_depth;

void DFS(int idx, int p=-1, int d=0){
    mx_dist[idx]=max(mx_dist[idx],d);
    if(mx_depth<d){
        mx_idx=idx;
        mx_depth=d;
    }
    for(auto next : edges[idx]){
        if(next!=p) DFS(next,idx,d+1);
    }
}

/*
mx_depth=-1;
DFS(0,-1,0);
mx_depth=-1;
DFS(mx_idx,-1,0);
DFS(mx_idx,-1,0);
*/