#include <bits/stdc++.h>

#define N 1000
#define INF 1000000007

using namespace std;

vector<pair<int,int>> edges[N]; // next, cost. // Must initialize after each testcase
int capa[N][N];
int flow[N][N];
bool inQ[N]; // (inQ[i]) means dist[i] changed ans need to be visited.
int pre[N];
int dist[N];

void add_edge(int a, int b, int w, int f){
    // a->b cost:w capa:f (Reverse edge has negative weight)
    edges[a].push_back({b,w}); capa[a][b]=f; flow[a][b]=0;
    edges[b].push_back({a,-w}); capa[b][a]=0; flow[b][a]=0;
}

void floyd_warshall(int s){ // maximum O(n*min(n,m))
    // Use floyd-warshall instead of dijkstra is because, negative weight edges exist
    // Only update pre[], dist[] 
    fill(inQ, inQ+N, false);
    fill(dist, dist+N, INF);
    queue<int> q;
    q.push(s);
    inQ[s]=true; // To maintain light queue
    dist[s]=0;
    while(!q.empty()){
        int idx=q.front(); inQ[idx]=false;
        q.pop();
        for(int i=0; i<edges[idx].size(); i++){
            int next=edges[idx][i].first, w=edges[idx][i].second; 
            if(capa[idx][next]-flow[idx][next]>0 && dist[idx]+w<dist[next]){
                dist[next]=dist[idx]+w;
                pre[next]=idx;
                if(!inQ[next]) q.push(next);
                inQ[next]=true;
            }
        }
        
    }
}

int MCMF(int s, int t){
    // Return minimum cost for maximum flow
    int res=0;
    while(true){
        floyd_warshall(s);
        if(dist[t]==INF) break;
        // Get flow
        int cur=t, ff=INF;
        while(cur!=s){
            ff=min(ff,capa[pre[cur]][cur]-flow[pre[cur]][cur]);
            cur=pre[cur];
        }
        // Flow update
        cur=t;
        while(cur!=s){
            flow[pre[cur]][cur]+=ff;
            flow[cur][pre[cur]]-=ff;
            cur=pre[cur];
        }
        res+=dist[t]*ff;
    }
    return res;
}