// LCA(sparse table)

#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

#define N 100100
#define MAX 20 // Should satisfy (1<<(MAX-1)) >= N 

vector<int> edges[N];
int sparse[N][MAX];
int level[N];

void DFS_init(int idx, int p){
    sparse[idx][0]=p;
    for(int i=0; i<edges[idx].size(); i++){
        int next=edges[idx][i];
        if(next!=p){
            level[next]=level[idx]+1;
            DFS_init(next,idx);
        }
    }
}

void sparse_init(int s){
    level[s]=0;
    DFS_init(s,-1);
    for(int r=1; r<MAX; r++){
        for(int i=0; i<N; i++){
            if(sparse[i][r-1]==-1) sparse[i][r]=-1;
            else sparse[i][r]=sparse[sparse[i][r-1]][r-1];
        }
    }
}

int get_LCA(int a, int b){
    if(level[a]>level[b]) swap(a,b);
    for(int r=MAX-1; r>=0; r--){
        if(sparse[b][r]!=-1 && level[a]<=level[sparse[b][r]]) b=sparse[b][r];
    }
    if(a==b) return a;
    for(int r=MAX-1; r>=0; r--){
        if(sparse[a][r]!=-1 && sparse[b][r]!=-1 && sparse[b][r]!=sparse[a][r]){
            a=sparse[a][r], b=sparse[b][r]; 
        }
    }
    return sparse[a][0];
}


int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n,m,a,b;
    cin>>n;
    for(int i=0; i<n-1; i++){
        cin>>a>>b;
        a--, b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    sparse_init(0);
    cin>>m;
    for(int i=0; i<m; i++){
        cin>>a>>b;
        cout<<get_LCA(a-1,b-1)+1<<endl;
    }
}   