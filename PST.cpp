// PST

#include <bits/stdc++.h>
using namespace std;

#define N_node 2000000 // V log|Y_RANGE| scale 
#define NX 100001
#define Y_RANGE 100000001 // Could be much larger than this. (Memory&Time complexcities are effeced only logarithmic scale.)

class node{
public:
    node(){}
    node operator+(node b){
        node res;
        // ���ʿ� �������� node�� l_idx, r_idx�� �����Ѵ�.
        res.l_idx=l_idx, res.r_idx=r_idx;
        res.val=val+b.val;
        return res;
    }
    node operator-(node b){
        node res;
        // Implement
        res.l_idx=l_idx, res.r_idx=r_idx;
        res.val=val-b.val;
        return res;
    }
    int l_idx=-1, r_idx=-1; // ���⼭ idx�� ������ idx�� ���Ѵ�.
    long long val=0;    
};

class PST{
public:
    int seg_root[NX]; // X-wise root idx.
    node seg[N_node]; // All node datas
    int cur_x=0, s_cnt=0; // s_cnt�� ������� ����� node�� ����
    PST(){}
    void push(int y_idx, long long y_val){
        // Pusing one element generate anothor root. Regardless of the val x.
        seg_root[cur_x]=s_cnt++;
        update_seg(seg_root[cur_x],(cur_x==0?-1:seg_root[cur_x-1]),0,Y_RANGE-1,y_idx,y_val);
        cur_x++;
    }
    node query(long long x1, long long x2, long long y1, long long y2){
        if(x1==0) return find_seg(seg_root[x2],0,Y_RANGE-1,y1,y2);
        return find_seg(seg_root[x2],0,Y_RANGE-1,y1,y2)-find_seg(seg_root[x1-1],0,Y_RANGE-1,y1,y2);
    }
    void clear(){
        for(int i=0; i<s_cnt; i++) seg[i]=node();
        cur_x=s_cnt=0;
    }

private:
    void update_seg(int idx, int prev_idx, int l, int r, int t_idx, long long val){
        // previous segtree�� idx�� ���� ����. (ù ��° layer�� ���� -1)
        if(l==r){
            // Implement. ������ �����Ϳ� ������ ���� �̺κ��� ����.
            seg[idx].val=val;
            if(prev_idx!=-1) seg[idx]=seg[idx]+seg[prev_idx];
            return;
        }
        int mid=(l+r)>>1;
        if(t_idx<=mid){
            seg[idx].l_idx=s_cnt++;
            seg[idx].r_idx=(prev_idx==-1?-1:seg[prev_idx].r_idx);
            update_seg(seg[idx].l_idx,(prev_idx==-1?-1:seg[prev_idx].l_idx),l,mid,t_idx,val);
        }
        else{
            seg[idx].r_idx=s_cnt++;
            seg[idx].l_idx=(prev_idx==-1?-1:seg[prev_idx].l_idx);
            update_seg(seg[idx].r_idx,(prev_idx==-1?-1:seg[prev_idx].r_idx),mid+1,r,t_idx,val);
        }
        // �Ʒ��� ���������� l_idx�� r_idx�� �����ϱ� ���� ��� 
        if(seg[idx].l_idx!=-1) seg[idx]=seg[idx]+seg[seg[idx].l_idx];
        if(seg[idx].r_idx!=-1) seg[idx]=seg[idx]+seg[seg[idx].r_idx];
    }
    node find_seg(int idx, int l, int r, int t_l, int t_r){
        if(t_l<=l && r<=t_r) return seg[idx];
        int mid=(l+r)>>1;
        node res;
        if(t_l<=mid && seg[idx].l_idx!=-1) res=res+find_seg(seg[idx].l_idx,l,mid,t_l,t_r);
        if(t_r>mid && seg[idx].r_idx!=-1) res=res+find_seg(seg[idx].r_idx,mid+1,r,t_l,t_r);
        return res;
    }
};

PST pst;