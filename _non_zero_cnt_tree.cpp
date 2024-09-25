#include <bits/stdc++.h>
using namespace std;

class nnz_seg{
public:
	pair<int,int> seg[1<<19]; // {cnt, nnz}
	nnz_seg(){}

	void build_seg(int idx, int l, int r){
		if(l==r){
			seg[idx].first=seg[idx].second=0;
		}
		else{
			int mid=(l+r)>>1;
			build_seg(2*idx,l,mid);
			build_seg(2*idx+1,mid+1,r);
            seg[idx].first=seg[idx].second=0;
		}
	}
	
	void update_seg(int idx, int l, int r, int t_l, int t_r, int val){
		if(t_l<=l && r<=t_r){
			seg[idx].first+=val;
            if(l==r) seg[idx].second=(seg[idx].first>0);
            else if(seg[idx].first>0) seg[idx].second=r-l+1;
            else seg[idx].second=seg[2*idx].second+seg[2*idx+1].second;
			return;
		}
		int mid=(l+r)>>1;
		if(t_l<=mid) update_seg(2*idx,l,mid,t_l,t_r,val);
		if(t_r>mid) update_seg(2*idx+1,mid+1,r,t_l,t_r,val);
        if(seg[idx].first==0) seg[idx].second=seg[2*idx].second+seg[2*idx+1].second;
	}
	
	int find_seg(int idx, int l, int r, int t_l, int t_r){
		if(t_l<=l && r<=t_r){
			return seg[idx].second;
		}
		int result=0;
		int mid=(l+r)>>1;
        if(seg[idx].first>0) return min(t_r,r)-max(t_l,l)+1; // 이 부분이 이상하다. 왜 지금까지 문제가 없었던 거지???
		if(t_l<=mid) result=(result+find_seg(2*idx,l,mid,t_l,t_r));
		if(t_r>mid) result=(result+find_seg(2*idx+1,mid+1,r,t_l,t_r));
		return result;
	}
};

nnz_seg s;
