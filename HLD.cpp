// HLD

#include <bits/stdc++.h>
#define INF 1000000007
#define N 200000

using namespace std;

vector<int> edges[N], child[N];
int parent[N], depth[N], in[N], top[N];
int sz[N], inv_in[N]; // HLD내부적으로 필요. inv_in은 seg의 초기화에 필요.
int n, cnt; 

void DFS(int idx, int p){
	child[idx].reserve(edges[idx].size()-1);
	for(int i=0; i<edges[idx].size(); i++){
		int next=edges[idx][i];
		if(next!=p){
			child[idx].push_back(next);
			DFS(next,idx);
		}
	}
}

// parent[루트], top[루트], depth[루트]업데이트 해줘야 함.
void DFS1(int idx=0){
	sz[idx]=1;
	for(int i=0; i<child[idx].size(); i++){
		int next=child[idx][i];
		parent[next]=idx;
		depth[next]=depth[idx]+1;
		DFS1(next);
		sz[idx]+=sz[next];
		if(sz[next]>sz[child[idx][0]]) swap(child[idx][0],child[idx][i]);
	}
}

void DFS2(int idx=0){
	in[idx]=cnt;
	for(int i=0; i<child[idx].size(); i++){
		int next=child[idx][i];
		top[next]=(i==0?top[idx]:next);
		cnt++;
		DFS2(next);
	}
}

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
		if(t_l<=l && r<=t_r){
			// seg[idx].val과 seg[idx].lazy_val업데이트
			return;
		}
		update_down(idx, l, r);
		int mid=(l+r)>>1;
		if(t_l<=mid) update_seg(2*idx,l,mid,t_l,t_r,val);
		if(t_r>mid) update_seg(2*idx+1,mid+1,r,t_l,t_r,val);
		seg[idx]=seg[2*idx]+seg[2*idx+1];
	}
	
	node find_seg(int idx, int l, int r, int t_l, int t_r){
		if(t_l<=l && r<=t_r){
			return seg[idx];
		}
		update_down(idx, l, r);
		node result;
		int mid=(l+r)>>1;
		if(t_l<=mid) result=result+find_seg(2*idx,l,mid,t_l,t_r);
		if(t_r>mid) result=result+find_seg(2*idx+1,mid+1,r,t_l,t_r);
		return result;
	}
};

lazy_seg s;

int get_LCA(int a,int b){ 
	while(top[a]!=top[b]){
		if(depth[top[a]]<depth[top[b]]) swap(a,b);
		a=parent[top[a]];
	}
	return (in[a]<in[b]?a:b);
}

node query(int a, int b){
	node result;
	while(top[a]!=top[b]){
		if(depth[top[a]]<depth[top[b]]) swap(a,b);
		result=result+s.find_seg(1,0,n-1,in[top[a]],in[a]); // 더하는 순서가 중요하다면 잘 확인할 것
		a=parent[top[a]];
	}
	result=result+s.find_seg(1,0,n-1,min(in[a],in[b]),max(in[a],in[b]));
	return result;
}

void update_query(int a, int b, int val){
	while(top[a]!=top[b]){
		if(depth[top[a]]<depth[top[b]]) swap(a,b);
		s.update_seg(1,0,n-1,in[top[a]],in[a],val);
		a=parent[top[a]];
	}
	s.update_seg(1,0,n-1,min(in[a],in[b]),max(in[a],in[b]),val);
}