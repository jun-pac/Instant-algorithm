
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define cediv(a,b) ((a)%(b)==0?((a)/(b)):((a)/(b))+1)
#define rng(i,a,b) for(int i=int(a);i<=int(b);i++)
#define rep(i,b) rng(i,0,b-1)  
#define gnr(i,b,a) for(int i=int(b);i>=int(a);i--)
#define per(i,b) gnr(i,b-1,0)
#define pb push_back
#define eb emplace_back
#define bg begin()
#define ed end()
#define all(x) x.bg,x.ed
#define si(x) int(x.size())
template<class t> using vc=vector<t>;
template<class t> using vvc=vc<vc<t>>;
typedef long long ll;
using pii=pair<int,int>;
using vi=vc<int>;
using uint=unsigned;
using ull=unsigned long long;
using pil=pair<int,ll>;
using pli=pair<ll,int>;
using pll=pair<ll,ll>;
using t3=tuple<int,int,int>;

#define N 300030
#define MOD 998244353
#define INF 1000000007 
__attribute__((optimize("Ofast,unroll-loops"),target("avx,avx2,fma")))


vector<pair<int,double>> edges[18]; // {next, dist}
double DP[18][1<<18]; // [last_idx][visited] // must be initialized with INF
// DP[last_idx][visited] indicates that "Minimum TSP excluding the set {visited}, which ended with last_idx"
int n;

// Re-visit already visited vertices are prohibited.
double TSP_DFS(int idx, int visit){ // idx is already included in visit, and DP[idx][visit] is minimum cost to traverse vertices excluding visit.
    if(visit==(1<<n)-1) return DP[idx][visit]=0;
    if(DP[idx][visit]!=INF) return DP[idx][visit];
    for(auto temp : edges[idx]){
        int next=temp.first;
        double dist=temp.second;
        if(visit&(1<<next)) continue;
        DP[idx][visit]=min(DP[idx][visit],TSP_DFS(next,visit|(1<<next))+dist);
    }
    return DP[idx][visit];
}

/*
double mn=INF;
rng(i,0,n-1) fill(DP[i],DP[i]+(1<<n),INF);
rng(i,0,n-1) mn=min(mn,TSP_DFS(i,(1<<i)));
*/