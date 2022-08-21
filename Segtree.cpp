// Segtree

#include <bits/stdc++.h>
#define INF 1000000007

using namespace std;

int seg[1<<18];

void build_seg(int idx, int l, int r){
    if(l==r){
        // seg[idx]=
        return;
    }
    int mid=(l+r)>>1;
    build_seg(2*idx,l,mid);
    build_seg(2*idx+1,mid+1,r);
    //seg[idx]=min(seg[2*idx],seg[2*idx+1]); // Some other operation
}

// 원소를 찾으면 disable도 같이 해주면 될 거 같음
void update_seg(int idx, int l, int r, int t_idx){
    if(l==r){
        seg[idx]=INF;
        return;
    }
    int mid=(l+r)>>1;
    if(t_idx<=mid) update_seg(2*idx,l,mid,t_idx);
    else update_seg(2*idx+1,mid+1,r,t_idx);
    //seg[idx]=min(seg[2*idx],seg[2*idx+1]);
}

int find_seg(int idx, int l, int r, int t_l, int t_r){
    if(t_l<=l && r<=t_r) return seg[idx];
    int mid=(l+r)>>1, ans=INF;
    if(t_l<=mid) //ans=min(ans,find_seg(2*idx,l,mid,t_l,t_r));
    if(t_r>mid) //ans=min(ans,find_seg(2*idx+1,mid+1,r,t_l,t_r));
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    return 0;
}



