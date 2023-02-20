// Ancestor_set

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

#define  N 300030

vector<int> A_child[N], B_child[N];
int cnt, mx;
int in[N], out[N];
set<pair<int, int>> ss;

void DFS1(int idx){
    in[idx]=cnt++;
    for(int next : B_child[idx]){
        DFS1(next);
    }
    out[idx]=cnt;
}

void DFS2(int idx){
    // idx가 누군가의 조상이다 -> 아무것도 안함
    // idx의 조상이 존재한다(조상은 최대 1개 존재) -> 그 조상을 제거하고 내가 들어간다. 조상을 기억.
    // 두 경우 모두 아님 -> 나를 집어넣는다.
    // DFS2가 끝날 때는 나를 넣었다면 반드시 빼줘야 한다.
    bool is_insert=false, is_delete=false;
    pair<int,int> deleted;
    pair<int,int> cur={in[idx], out[idx]};
    auto it=ss.upper_bound(cur);
    if(it==ss.end() || (*it).second>=cur.second){
        is_insert=true;
        if(it!=ss.begin() && (*(--it)).second>=cur.second){
            is_delete=true;
            deleted=(*it); 
            ss.erase(it);
       }
        ss.insert(cur);
    }
    mx=max(mx,(int)ss.size());
    for(int next : A_child[idx]){
        DFS2(next);
    }
    if(is_delete) ss.insert(deleted);
    if(is_insert) ss.erase(ss.find(cur));
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        int n,p;
        cin>>n;
        for(int i=0; i<n; i++) A_child[i].clear(), B_child[i].clear();
        for(int i=1; i<n; i++){
            cin>>p;
            A_child[p-1].push_back(i);
        }
        for(int i=1; i<n; i++){
            cin>>p;
            B_child[p-1].push_back(i);
        }
        ss.clear(), cnt=0, mx=0;
        DFS1(0);
        DFS2(0);
        cout<<mx<<endl;
    }
    return 0;
}