// 금광 + HLD아니냐
//./F<test

#include <bits/stdc++.h>
#define endl '\n'
#define fi first
#define se second
#define pb push_back

using namespace std;

typedef long long ll;


#define N 200020

vector<pair<pair<int,int>,int>> qs;
int datas[N];

vector<int> edges[N], child[N];
int parent[N], depth[N], in[N], top[N];
int sz[N], inv_in[N]; // HLD내부적으로 필요. inv_in은 seg의 초기화에 필요.
int n, cnt; 

void DFS(int idx, int p){
	//child[idx].reserve(edges[idx].size()-1);
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
    inv_in[cnt]=idx;
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
    node(int val){
        l_mn=r_mn=t_mn=min(0,val);
        l_mx=r_mx=t_mx=max(0,val);
        sum=val;
    }
    node operator+(node b){
        node result;
        result.l_mn=min(l_mn,sum+b.l_mn);
        result.l_mx=max(l_mx,sum+b.l_mx);
        result.r_mn=min(b.r_mn,b.sum+r_mn);
        result.r_mx=max(b.r_mx,b.sum+r_mx);
        result.t_mn=min(min(t_mn, b.t_mn), r_mn+b.l_mn);
        result.t_mx=max(max(t_mx, b.t_mx), r_mx+b.l_mx);
        result.sum=sum+b.sum;
        return result;
    }
    int l_mn, l_mx, r_mn, r_mx, t_mn, t_mx, sum;
};

class lazy_seg{
public:
	node seg[1<<19];
	lazy_seg(){}
	
	void build_seg(int idx, int l, int r){
		if(l==r){
			seg[idx]=node(datas[inv_in[l]]);
		}
		else{
			int mid=(l+r)>>1;
			build_seg(2*idx,l,mid);
			build_seg(2*idx+1,mid+1,r);
			seg[idx]=seg[2*idx]+seg[2*idx+1];
		}
	}
    
	node find_seg(int idx, int l, int r, int t_l, int t_r){
		if(t_l<=l && r<=t_r){
			return seg[idx];
		}
		node result(0);
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
	node result_l(0); // 금광세그의 특수성 때문이다.
    node result_r(0);
    while(top[a]!=top[b]){
		if(depth[top[a]]<depth[top[b]]){
            result_r=s.find_seg(1,0,n-1,in[top[b]],in[b])+result_r;
            b=parent[top[b]];
        }
		else{
            result_l=s.find_seg(1,0,n-1,in[top[a]],in[a])+result_l;
		    a=parent[top[a]];
        }
	}
	if(in[a]<in[b]) result_r=s.find_seg(1,0,n-1,in[a],in[b])+result_r;
	else result_l=s.find_seg(1,0,n-1,in[b],in[a])+result_l;
    // 반전 해줘야 함.
    swap(result_l.l_mn,result_l.r_mn);
    swap(result_l.l_mx,result_l.r_mx);
    return result_l+result_r;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        int a,b,c;
        char mode;
        int nn;
        cin>>nn;
        
        n=1;
        datas[0]=1;
        for(int i=0; i<nn; i++){
            cin>>mode;
            if(mode=='+'){
                n++;
                cin>>a>>b;
                datas[n-1]=b;
                edges[n-1].push_back(a-1);
                edges[a-1].push_back(n-1);
            }
            else{
                cin>>a>>b>>c;
                if(a<b) swap(a,b);
                qs.push_back({{a-1,b-1},c});
            }
        }

        cnt=0;
        parent[0]=-1;
        top[0]=depth[0]=0;
        DFS(0,-1);
        DFS1(0);
        DFS2(0);
        s.build_seg(1,0,n-1);
        //cout<<"n in this : "<<n<<endl;
        for(int i=0; i<qs.size(); i++){
            auto res=query(qs[i].fi.fi,qs[i].fi.se);
            //cout<<"query "<<qs[i].fi.fi<<' '<<qs[i].fi.se<<" : "<<res.t_mn<<' '<<res.t_mx<<endl;
            if(res.t_mn<=qs[i].se && res.t_mx>=qs[i].se) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
        for(int i=0; i<n; i++) edges[i].clear();
        for(int i=0; i<n; i++) child[i].clear();
        qs.clear();
    }
    return 0;
}