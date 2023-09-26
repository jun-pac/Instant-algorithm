// I : 안테나 설치 (Seg beats)
// Seg beats가 다른 게 아니라 기존의 lazy seg의 종료조건에서 더 내려가는데, 그 내려가는 횟수가 bound되는 것이지요
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;

ll datas[500005];
ll DP[500005]; // cur max
ll mx_seg[1<<20];
#define INF 10000000000000007

void mx_build_seg(int idx, int l, int r){
    if(l==r){
        mx_seg[idx]=datas[l];
        return;
    }
    int mid=(l+r)>>1;
    mx_build_seg(2*idx,l,mid);
    mx_build_seg(2*idx+1,mid+1,r);
    mx_seg[idx]=max(mx_seg[2*idx],mx_seg[2*idx+1]); // Some other operation
}

ll mx_find_seg(int idx, int l, int r, int t_l, int t_r){
    if(t_l<=l && r<=t_r) return mx_seg[idx];
    ll mid=(l+r)>>1, ans=0;
    if(t_l<=mid) ans=max(ans,mx_find_seg(2*idx,l,mid,t_l,t_r));
    if(t_r>mid) ans=max(ans,mx_find_seg(2*idx+1,mid+1,r,t_l,t_r));
    return ans;
}


class node{
public:
    node(){}
    node(ll val, ll mx_val){
        this->val = val;
        this->mx_val = mx_val; // lazy val과는 다르게 따로 업데이트 X. flag true일 때만 의미가짐.
        this->lazy_val=0;
        same_flag=true;
    }
    node operator+(node b){
        node result;
        // same_flag는 둘 다 똑같을 경우에만
        result.val=min(val, b.val);
        result.mx_val=min(mx_val,b.mx_val);
        result.lazy_val=0;
        result.same_flag=(same_flag && b.same_flag && mx_val==b.mx_val);
        return result;
    }
    ll val=INF, mx_val=0, lazy_val=0; // mx_val은 서브트리의 mx_val중 최소값을 가져야 한다.
    bool same_flag=false;
};

class lazy_seg{
public:
	node seg[1<<20];
	
	lazy_seg(){}
	
	void build_seg(int idx, int l, int r){
		if(l==r){
			seg[idx].val=INF;
            seg[idx].lazy_val=0;
            seg[idx].mx_val=0;
		}
		else{
			int mid=(l+r)>>1;
			build_seg(2*idx,l,mid);
			build_seg(2*idx+1,mid+1,r);
			seg[idx]=seg[2*idx]+seg[2*idx+1];
		}
	}
	
	void update_down(int idx, int l, int r){
        if(l==r || seg[idx].lazy_val==0) return;
        int mid=(l+r)>>1;
        seg[2*idx].lazy_val+=seg[idx].lazy_val;
        seg[2*idx].val+=seg[idx].lazy_val;
        seg[2*idx].mx_val+=seg[idx].lazy_val;
        seg[2*idx+1].lazy_val+=seg[idx].lazy_val;
        seg[2*idx+1].val+=seg[idx].lazy_val;
        seg[2*idx+1].mx_val+=seg[idx].lazy_val;
        seg[idx].lazy_val=0;
    }
	
    void update_seg(int idx, int l, int r, int t_idx, ll val, ll mx_val){
        update_down(idx, l, r);
        if(l==r){
			seg[idx]=node(val, mx_val);
            return;
		}
        int mid=(l+r)>>1;
		if(t_idx<=mid) update_seg(2*idx,l,mid,t_idx,val, mx_val);
		if(t_idx>mid) update_seg(2*idx+1,mid+1,r,t_idx,val, mx_val);
		seg[idx]=seg[2*idx]+seg[2*idx+1];
	}

	void update_mx(int idx, int l, int r, int t_l, int t_r, ll mx_val){
		update_down(idx, l, r);
        if(seg[idx].mx_val>=mx_val) return;
		if(t_l<=l && r<=t_r && seg[idx].same_flag){
            // end조건은 범위를 만족하고, same_flag인 지점임.
            seg[idx].lazy_val+=mx_val-seg[idx].mx_val;
            seg[idx].val+=mx_val-seg[idx].mx_val;
            seg[idx].mx_val=mx_val;
            return;
		}
        int mid=(l+r)>>1;
		if(t_l<=mid) update_mx(2*idx,l,mid,t_l,t_r,mx_val);
		if(t_r>mid) update_mx(2*idx+1,mid+1,r,t_l,t_r,mx_val);
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

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n,p;
    cin>>n>>p;
    for(int i=0; i<n; i++){
        cin>>datas[i];
    }
    mx_build_seg(1,0,n-1); // 단순히 구간의 mx값을 구하는 용도
    DP[0]=datas[0]-1;
    s.update_seg(1,0,n-1,0,datas[0],datas[0]);
    int l=0,r;
    for(int i=1; i<n; i++){
        // DP[i]를 seg에 넣는 update
        s.update_seg(1,0,n-1,i,DP[i-1]+datas[i],datas[i]);

        // max값에 a_i를 추가로 넣는 과정
        s.update_mx(1,0,n-1,0,i,datas[i]);
        
        // DP[i]를 구하는 과정 
        while(l<i && mx_find_seg(1,0,n-1,l,i)+(i-l)>p) l++;
        DP[i]=s.find_seg(1,0,n-1,l,i).val-1; // -1은 밖에서 처리를 해주는게 깔끔하다.
    }
    cout<<DP[n-1]+n<<endl;
    return 0;
}