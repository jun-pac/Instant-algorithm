
#include <bits/stdc++.h>
using namespace std;

#define N_node 9000000 // V log|X_RANGE| scale 

class node{
public:
    node(){}
    int l_idx=-1, r_idx=-1; // 여기서 idx는 본인의 idx를 말한다.
    int val=0;    
};

class PST{
public:
    node seg[N_node]; // All node datas // About 100MB
    int s_cnt=2; // 현재까지 사용한 node의 개수. 0 is not used, 1 is reserved for convention (for convention)
    void clear(){
        for(int i=0; i<s_cnt; i++) seg[i]=node();
        s_cnt=2; 
    }

    void update_seg(int idx, int l, int r, int t_idx, int val){
        if(l==r){
            seg[idx].val=val;
            return;
        }
        int mid=(l+r)>>1;
        if(t_idx<=mid){
            if(seg[idx].l_idx==-1){
                seg[idx].l_idx=s_cnt;
                seg[s_cnt]=node();
                s_cnt++;
            }
            update_seg(seg[idx].l_idx,l,mid,t_idx,val);
        }
        else{
            if(seg[idx].r_idx==-1){
                seg[idx].r_idx=s_cnt;
                seg[s_cnt]=node();
                s_cnt++;
            }
            update_seg(seg[idx].r_idx,mid+1,r,t_idx,val);
        }
        int temp=0;
        if(seg[idx].l_idx!=-1) temp+=seg[seg[idx].l_idx].val;
        if(seg[idx].r_idx!=-1) temp+=seg[seg[idx].r_idx].val;
        seg[idx].val=temp;
    }
    int find_seg(int idx, int l, int r, int t_l, int t_r){
        if(t_l<=l && r<=t_r){
            return seg[idx].val;
        }
        int mid=(l+r)>>1;
        int res=0;
        if(t_l<=mid && seg[idx].l_idx!=-1) res=res+find_seg(seg[idx].l_idx,l,mid,t_l,t_r);
        if(t_r>mid && seg[idx].r_idx!=-1) res=res+find_seg(seg[idx].r_idx,mid+1,r,t_l,t_r);
        return res;
    }
};

PST pst;
