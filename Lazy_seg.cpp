// Lazy seg

#include <bits/stdc++.h>
#define INF 1000000007

using namespace std;

// This type is more appropriate when finding max, min value in the range.
// For adding total number, plz check bottom code

class node{
public:
    // Do something!
    node(){}
    //node(int val){this->val=val;}
    node operator+(node b){
        node result;
        result.val=max(val,b.val); // Modify
        return result;
    }
    int val=0, lazy_val=0;
};

class lazy_seg{
public:
	node seg[1<<18];
	
	lazy_seg(){}
	//lazy_seg(int n){}
	
	void build_seg(int idx, int l, int r){
		if(l==r){
			seg[idx].val=0; // seg[idx].val=datas[l];
			seg[idx].lazy_val=0;
		}
		else{
			int mid=(l+r)>>1;
			build_seg(2*idx,l,mid);
			build_seg(2*idx+1,mid+1,r);
			seg[idx]=(seg[2*idx]+seg[2*idx+1]);
		}
	}
	
	void update_down(int idx, int l, int r){
		if(l==r) return;
		int mid=(l+r)>>1;
		// // seg[2*idx], seg[2*idx+1]
		// seg[2*idx].val+=seg[idx].lazy_val;
		// seg[2*idx].lazy_val+=seg[idx].lazy_val;
		// seg[2*idx+1].val+=seg[idx].lazy_val;
		// seg[2*idx+1].lazy_val+=seg[idx].lazy_val;
		// // seg[idx]의 lazy_val초기화
		// seg[idx].lazy_val=0;
	}
	
	void update_seg(int idx, int l, int r, int t_l, int t_r, int val){
		update_down(idx, l, r);
		if(t_l<=l && r<=t_r){
			// // seg[idx].val과 seg[idx].lazy_val업데이트
			// seg[idx].val+=val;
			// seg[idx].lazy_val+=val;
			return;
		}
		int mid=(l+r)>>1;
		if(t_l<=mid) update_seg(2*idx,l,mid,t_l,t_r,val);
		if(t_r>mid) update_seg(2*idx+1,mid+1,r,t_l,t_r,val);
		seg[idx]=(seg[2*idx]+seg[2*idx+1]);
	}
	
	node find_seg(int idx, int l, int r, int t_l, int t_r){
		update_down(idx, l, r);
		if(t_l<=l && r<=t_r){
			return seg[idx];
		}
		node result;
		int mid=(l+r)>>1;
		if(t_l<=mid) result=(result+find_seg(2*idx,l,mid,t_l,t_r));
		if(t_r>mid) result=(result+find_seg(2*idx+1,mid+1,r,t_l,t_r));
		return result;
	}
};

lazy_seg s;


// For sum
/*
class lazy_seg{
public:
	node seg[1<<18];
	lazy_seg(){}
	
	void build_seg(int idx, int l, int r){
		if(l==r){
			seg[idx].val=0;
			seg[idx].lazy_val=0;
		}
		else{
			int mid=(l+r)>>1;
			build_seg(2*idx,l,mid);
			build_seg(2*idx+1,mid+1,r);
			seg[idx]=(seg[2*idx]+seg[2*idx+1]);
		}
	}
	
	void update_down(int idx, int l, int r){
		if(l==r) return;
		int mid=(l+r)>>1;
		// seg[2*idx], seg[2*idx+1]
		seg[2*idx].val+=(mid-l+1)*seg[idx].lazy_val;
		seg[2*idx].lazy_val+=seg[idx].lazy_val;
		seg[2*idx+1].val+=(r-mid)*seg[idx].lazy_val;
		seg[2*idx+1].lazy_val+=seg[idx].lazy_val;
		// seg[idx]의 lazy_val초기화
		seg[idx].lazy_val=0;
	}
	
	void update_seg(int idx, int l, int r, int t_l, int t_r, ll val){
		update_down(idx, l, r);
		if(t_l<=l && r<=t_r){
			seg[idx].val+=(r-l+1)*val;
			seg[idx].lazy_val+=val;
			return;
		}
		int mid=(l+r)>>1;
		if(t_l<=mid) update_seg(2*idx,l,mid,t_l,t_r,val);
		if(t_r>mid) update_seg(2*idx+1,mid+1,r,t_l,t_r,val);
		seg[idx]=(seg[2*idx]+seg[2*idx+1]);
	}
	
	node find_seg(int idx, int l, int r, int t_l, int t_r){
		update_down(idx, l, r);
		if(t_l<=l && r<=t_r){
			return seg[idx];
		}
		node result;
		int mid=(l+r)>>1;
		if(t_l<=mid) result=(result+find_seg(2*idx,l,mid,t_l,t_r));
		if(t_r>mid) result=(result+find_seg(2*idx+1,mid+1,r,t_l,t_r));
		return result;
	}
};
*/