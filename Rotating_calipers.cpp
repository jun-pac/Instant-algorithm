// Rotating calipers

#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;
typedef long long ll;

#define N 100000

pair<ll,ll> datas[N]; // Vertices // Convex hull algorithm never permute initial vertices.
int sorted_idx[N]; // Idx of 'sorted' datas.
int ans[N]; // Elements of convex hull

inline bool CCW(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& c){
    return (b.fi-a.fi)*(c.se-a.se)-(b.se-a.se)*(c.fi-a.fi)>0; // 변 위의 점도 필요하다면 >=
}

inline bool CCW_4(const pair<ll,ll>& a, const pair<ll,ll>& na, const pair<ll,ll>& b, pair<ll,ll> &nb){
    return (na.fi-a.fi)*(nb.se-b.se)-(na.se-a.se)*(nb.fi-b.fi)>=0;
}

inline long long dist(const pair<ll,ll>& a, const pair<ll,ll>& b){
    return (a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se);
}

class comp_c{
public:
    pair<ll,ll> mp;
    comp_c(pair<ll,ll> minpos){
        mp=minpos;
    }
    bool operator()(int a_idx, int b_idx){
        pair<ll,ll> a=datas[a_idx], b=datas[b_idx];
        ll com=(a.fi-mp.fi)*(b.se-mp.se)-(a.se-mp.se)*(b.fi-mp.fi);
        if(com==0) return dist(a,mp)<dist(b,mp);
        else return com>0;
    }
};

int convex_hull(int n){ // # number of vertices
    // Phase 1: Sort
    int m_idx=0;
    for(int i=1; i<n; i++) if(datas[m_idx]>datas[i]) m_idx=i;
    for(int i=0; i<n; i++) sorted_idx[i]=i;
    swap(sorted_idx[0], sorted_idx[m_idx]);
    sort(sorted_idx,sorted_idx+n,comp_c(datas[m_idx]));
    
    // Phase 2: Get Convexhull
    int st[N]; // Elements of st are the idx of datas 
    int cur=0, st_cnt=0; // cur : # of visited elements of s, st_cnt : # of elements in stack
    while(cur<n){
        while(st_cnt>=2 && !CCW(datas[st[st_cnt-2]],datas[st[st_cnt-1]],datas[sorted_idx[cur]])) st_cnt--;
        st[st_cnt++]=sorted_idx[cur++];
    }
    for(int i=0; i<st_cnt; i++) ans[i]=st[i]; // Counter clockwise, starts with leftmost vertices.
    return st_cnt;
}

pair<int,int> rotating_calipers(int sz_hull){ // # of vertices in convex hull.
    // ans[] must be filled before call this function.
    int mx_a, mx_b; // mx_a and mx_b are the idx of two vertices making the maximum distance.
    long long mx=0;
    for(int a=0, p=0; a<sz_hull; a++){
        while(p+1<sz_hull && CCW_4(datas[ans[a]], datas[ans[a+1]], datas[ans[p]], datas[ans[p+1]])){
            ll temp=dist(datas[ans[a]], datas[ans[p]]);
            if(mx<temp) mx=temp, mx_a=ans[a], mx_b=ans[p];
            p++;
        }
        ll temp=dist(datas[ans[a]], datas[ans[p]]);
        if(mx<temp) mx=temp, mx_a=ans[a], mx_b=ans[p];
    }
    return {mx_a, mx_b}; // Idx of initial vertices. i.e. datas[]
}
