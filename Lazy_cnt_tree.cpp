// Lazy count tree. Update down이 필요없는 아주 단순한 형태의 lazy_seg

#include <iostream>
using namespace std;

long long seg[800000];

void update_seg(int idx, int l, int r, int t_l, int t_r, long long val){
    if(t_l<=l && r<=t_r){
        seg[idx]+=val;
        return;
    }
    int mid=(l+r)>>1;
    if(t_l<=mid) update_seg(2*idx,l,mid,t_l,t_r,val);
    if(t_r>mid) update_seg(2*idx+1,mid+1,r,t_l,t_r,val);
}

long long find_seg(int idx, int l, int r, int t_idx){
    if(l==r) return seg[idx];
    long long res=seg[idx];
    int mid=(l+r)>>1;
    if(t_idx<=mid) res=res+find_seg(2*idx,l,mid,t_idx);
    if(t_idx>mid) res=res+find_seg(2*idx+1,mid+1,r,t_idx);
    return res;
}