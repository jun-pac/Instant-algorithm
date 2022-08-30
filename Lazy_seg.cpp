// Lazy seg

#include <bits/stdc++.h>
#define INF 1000000007

using namespace std;

class node{
public:
    // Do something!
    node(){}
    node(){
        
    }
    node operator+(node b){
        node result;
        // Do something!
        return result;
    }
    // int val, lazy_val;
};

class lazy_seg{
public:
	node seg[1<<18];
	
	lazy_seg(){}
	lazy_seg(int n){
	    //fill(seg,seg+n,node());
	}
	
	void build_seg(int idx, int l, int r){
		if(l==r){
			// Do something!
		}
		else{
			int mid=(l+r)>>1;
			build_seg(2*idx,l,mid);
			build_seg(2*idx+1,mid+1,r);
			seg[idx]=seg[2*idx]+seg[2*idx+1];
		}
	}
	
	void update_down(int idx, int l, int r){
		if(l==r) return;
		int mid=(l+r)>>1;
		// seg[2*idx], seg[2*idx+1]
		
		// seg[idx]의 lazy_val초기화
		
	}
	
	void update_seg(int idx, int l, int r, int t_l, int t_r, int val){
		update_down(idx, l, r);
		if(t_l<=l && r<=t_r){
			// seg[idx].val과 seg[idx].lazy_val업데이트
			return;
		}
		int mid=(l+r)>>1;
		if(t_l<=mid) update_seg(2*idx,l,mid,t_l,t_r,val);
		if(t_r>mid) update_seg(2*idx+1,mid+1,r,t_l,t_r,val);
		seg[idx]=seg[2*idx]+seg[2*idx+1];
	}
	
	node find_seg(int idx, int l, int r, int t_l, int t_r){
		update_down(idx, l, r);
		if(t_l<=l && r<=t_r){
			return seg[idx];
		}
		node result;
		int mid=(l+r)>>1;
		if(t_l<=mid) result=result+find_seg(2*idx,l,mid,t_l,t_r);
		if(t_r>mid) result=result+find_seg(2*idx+1,mid+1,r,t_l,t_r);
		return result;
	}
};

lazy_seg s;