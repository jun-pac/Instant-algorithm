// All algotithm (240719)

// 2-SAT
#include <bits/stdc++.h>
using namespace std;
#define N 300030
#define MOD 998244353
#define INF 1000000007
#define MAX_DIGIT 62
#define fi first
#define se second
typedef long long ll;


//=== SCC & 2-SAT ===
// For SCC
vector<int> edges[N]; 
vector<int> r_edges[N];
int scc[N];
int order[N];
bool visited[N];
int cnt, scc_cnt; // Number of SCC's
int n; // Number of actual nodes in graph

// For 2-SAT
vector<int> r_scc_edges[N]; // reverse edges connecting sccs (in scc index)
vector<int> scc_element[N]; // Nodes of each scc
bool scc_fixed[N]; // whether the value of scc determined (initially set false)
bool scc_state[N]; // Determined scc value 
inline int t_idx(int i){return i<<1;}
inline int f_idx(int i){return (i<<1)+1;}
inline int inv_idx(int i){return i^1;}

void init_scc(){
    for(int i=0; i<n; i++) {edges[i].clear(), r_edges[i].clear();}
}

void init_sat(){
    init_scc();
    for(int i=0; i<n; i++) {r_scc_edges[i].clear(), scc_element[i].clear();}
    fill(scc_fixed, scc_fixed+n, false);
    fill(scc_fixed, scc_fixed+n, true);
}

void sat_edge(int a, int b){
    edges[inv_idx(a)].push_back(b);
    r_edges[b].push_back(inv_idx(a));
    if(a!=b){
        edges[inv_idx(b)].push_back(a);
        r_edges[a].push_back(inv_idx(b));
    }
}

void DFS_SCC(int idx){
    visited[idx]=true;
    for(int i=0; i<edges[idx].size(); i++) if(!visited[edges[idx][i]]) DFS_SCC(edges[idx][i]);
    order[cnt]=idx; cnt++;
}

void r_DFS_SCC(int idx){
    visited[idx]=true;
    scc[idx]=cnt;
    for(int i=0; i<r_edges[idx].size(); i++) if(!visited[r_edges[idx][i]]) r_DFS_SCC(r_edges[idx][i]);
}

void get_scc(){ 
    fill(visited, visited+n, false), cnt=0;
    for(int i=0; i<n; i++) if(!visited[i]) DFS_SCC(i);
    fill(visited, visited+n, false), cnt=0;
    for(int i=n-1; i>=0; i--) if(!visited[order[i]]) {r_DFS_SCC(order[i]); cnt++;}
    scc_cnt=cnt;
}

bool r_sat_DFS(int idx, bool state){
    visited[idx]=true;
    bool new_state=false;
    for(int i=0; i<r_scc_edges[idx].size(); i++){
        if(!visited[r_scc_edges[idx][i]]){
            new_state=new_state||r_sat_DFS(r_scc_edges[idx][i], state);
        }
    }
    if(!scc_fixed[idx]){
        scc_fixed[idx]=true;
        scc_state[idx]=new_state;
    }
    else new_state=scc_state[idx];

    for(int i=0; i<scc_element[idx].size(); i++){
        int cur=scc_element[idx][i];
        int inv_scc=scc[inv_idx(cur)];
        scc_fixed[inv_scc]=true;
        scc_state[inv_scc]=!scc_state[idx];
    }
    return new_state;
}





//=== Aho-corasic ===
// Aho-corasic
// Upper-case code임에 주의.

#include <bits/stdc++.h>
using namespace std;

#define NUM_ALPHA 26
#define N 10000

class node_aho{
public:
    node_aho* next[NUM_ALPHA]={NULL,};
    node_aho* pphi; // parent of phi ; i.e. 최대 접미사의 가장 마지막 노드. 다음 원소는 직접 찾아야 함.
    int val; // 부모를 통해 찾아줘도 된다. // 0-based idx of character
    bool end_of_snippet=false; // End node of snippet. Propagated in BFS phase.
    int length_of_snippet; // Only valid of end of snippet is true. Propagated in BFS phase.
    int depth=0; // Actual length of the sequence
    bool end=true; // All next pointers are NULL
    node_aho(){}
    node_aho(int v){
        val=v; 
    }
};

class aho_trie{
public:
    node_aho* root= new node_aho();
    aho_trie(){}
    bool is_s(string &s){
        return is_re(root, 0, s);
    }
    void insert_s(string &s){
        insert_re(root, 0, s);
    }
    void clear(){ // clear_all
        clear_re(root);
        for(int i=0; i<NUM_ALPHA; i++) root->next[i]=NULL;
    }
    void get_phi(){
        queue<pair<node_aho*,node_aho*>> phi_q; // cur_pos, pphi
        phi_q.push({root,root});
        while(!phi_q.empty()){
            pair<node_aho*,node_aho*> temp=phi_q.front();
            phi_q.pop();
            node_aho* cur=temp.first;
            node_aho* ptar=temp.second;
            if(cur->depth>1){ // To prevent phi[self]=self
                while(ptar!=root && (ptar->next[cur->val]==NULL)) ptar=ptar->pphi;
                if(ptar->next[cur->val]!=NULL) ptar=ptar->next[cur->val];
            }
            cur->pphi=ptar;
            if(!cur->end_of_snippet && ptar->end_of_snippet){
                cur->end_of_snippet=true;
                cur->length_of_snippet=ptar->length_of_snippet;
            }

            for(int i=0; i<NUM_ALPHA; i++){
                if((cur->next[i])!=NULL){
                    phi_q.push({cur->next[i],ptar});
                }
            }
        }
    }
    void find_matching(string &s_ref, vector<int> &ans){
        int n=s_ref.size();
        ans.clear();
        node_aho* ptar=root;
        for(int i=0; i<n; i++){
            int cur=s_ref[i]-'A'; // transition function
            while(ptar!=root && ptar->next[cur]==NULL) ptar=ptar->pphi;
            if(ptar->next[cur]!=NULL) ptar=ptar->next[cur];
            //cout<<(char)(ptar->val+'A')<<' '<<ptar->cnt<<' '<<ptar->depth<<endl;
            if(ptar->end_of_snippet) ans.push_back(i+1-(ptar->length_of_snippet));
            if(ptar->end) ptar=ptar->pphi;
        }
    }

private: 
    bool is_re(node_aho *cur, int idx, string &s){
        if(idx==s.size()) return (cur->end_of_snippet);
        if((cur->next[s[idx]-'A'])==NULL) return false;
        return is_re(cur->next[s[idx]-'A'],idx+1,s);
    }
    void insert_re(node_aho* cur, int idx, string &s){
        if(idx==s.size()){
            cur->end_of_snippet=true;
            cur->length_of_snippet=s.size();
            return;
        }
        cur->end=false;
        if((cur->next[s[idx]-'A'])==NULL){
            cur->next[s[idx]-'A']=new node_aho(s[idx]-'A');
            cur->next[s[idx]-'A']->depth=idx+1;
        }
        insert_re(cur->next[s[idx]-'A'],idx+1,s);
    }
    void clear_re(node_aho* cur){
        for(int i=0; i<NUM_ALPHA; i++){
            if((cur->next[i])!=NULL){
                clear_re(cur->next[i]);
                delete cur->next[i];
            }
        }
    }
};

aho_trie aho;




//=== Arithmethic inverse ===
#define MOD 998244353
#define MAX_DIGIT 62

// (ak)*(bk)^(-1) = a*b^(-1) = (ak%P)*(bk%P)^(-1) (mod P)
long long ari_inv(long long num){
    // Calculate num^(MOD-2)
    long long res=1, mult=num;
    for(int i=0; i<MAX_DIGIT; i++){
        if((MOD-2)&(1LL<<i)){
            res=(res*mult)%MOD;
        }
        mult=(mult*mult)%MOD;
    }
    return res;
}




// Bipartite matching
vector<int> edges[N];
vector<int> rev_edges[N]; // To find maximum independent set.
int pre[N];
bool visited[N];

bool DFS_Bipartite(int idx){
    // Bipartite matching
    if(visited[idx]) return false;
    visited[idx]=true;
    for(int i=0; i<edges[idx].size(); i++){
        int next=edges[idx][i];
        if(pre[next]==-1 || (!visited[pre[next]] && DFS_Bipartite(pre[next]))){
            pre[next]=idx;
            return true;
        }
    }
    return false;
}

// fill(visited, visited+n, 0); //for each iteration
// if(DFS(i)) result++; 




//=== Centroid ===
vector<int> edges[N];
bool visited[N];
int sub_sz[N];
long long cnt;

int sz_DFS(int idx, int p){
	int result=1;
	for(int i=0; i<edges[idx].size(); i++){
		if(edges[idx][i]!=p && !visited[edges[idx][i]]){
			result+=sz_DFS(edges[idx][i], idx);
		}
	}
	return sub_sz[idx]=result;
}

int find_centroid(int idx, int p, int tot_sz){
	int result=idx;
	for(int i=0; i<edges[idx].size(); i++){
		int next=edges[idx][i];
		if(next!=p && !visited[edges[idx][i]] && sub_sz[next]>tot_sz/2){
			result=find_centroid(next,idx,tot_sz);
			break;
		}
	}
	return result;
}

void main_DFS_centroid(int idx, int p){
	int tot_sz=sz_DFS(idx,p);
	if(tot_sz==1) return;
	int cent=find_centroid(idx,p,tot_sz);
	visited[cent]=true;
	
	// Do something!
	
	for(int i=0; i<edges[cent].size(); i++){
		int next=edges[cent][i];
		if(!visited[next]) main_DFS_centroid(next,cent);
	}
	return;
}



//=== Convex hull ===
pair<ll,ll> datas[N]; // Vertices // Convex hull algorithm never permute initial vertices.
int sorted_idx[N]; // Idx of 'sorted' datas.
int ans[N]; // Elements of convex hull

inline bool CCW(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& c){
    return (b.fi-a.fi)*(c.se-a.se)-(b.se-a.se)*(c.fi-a.fi)>0; // 변 위의 점도 필요하다면 >=
}

inline long long distance(const pair<ll,ll>& a, const pair<ll,ll>& b){
    return (a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se);
}

class comp_c{
public:
    pair<ll,ll> mp;
    comp_c(pair<ll,ll> minpos){
        mp=minpos;
    }
    bool operator()(int a_idx, int b_idx){
        pair<ll,ll> a=datas[a_idx], b=datas[b_idx];
        ll com=(a.fi-mp.fi)*(b.se-mp.se)-(a.se-mp.se)*(b.fi-mp.fi);
        if(com==0) return distance(a,mp)<distance(b,mp);
        else return com>0;
    }
};

int convex_hull(int n){ // # number of vertices
    // Phase 1: Sort
    int m_idx=0;
    for(int i=1; i<n; i++) if(datas[m_idx]>datas[i]) m_idx=i;
    for(int i=0; i<n; i++) sorted_idx[i]=i;
    swap(sorted_idx[0], sorted_idx[m_idx]);
    sort(sorted_idx,sorted_idx+n,comp_c(datas[m_idx]));
    
    // Phase 2: Get Convexhull
    int st[N]; // Elements of st are the idx of datas 
    int cur=0, st_cnt=0; // cur : # of visited elements of s, st_cnt : # of elements in stack
    while(cur<n){
        while(st_cnt>=2 && !CCW(datas[st[st_cnt-2]],datas[st[st_cnt-1]],datas[sorted_idx[cur]])) st_cnt--;
        st[st_cnt++]=sorted_idx[cur++];
    }
    for(int i=0; i<st_cnt; i++) ans[i]=st[i]; // Counter clockwise, starts with leftmost vertices.
    return st_cnt;
}




//=== Dijkstra ===
vector<pair<long long,long long>> edges_d[N]; // {idx, dist}
long long min_dist[N];

void dijkstra(int s){
    priority_queue<pair<long long,long long>> pq;
    fill(min_dist,min_dist+N,-1);
	pq.push({0,s});
    while(!pq.empty()){
		long long dist=-pq.top().first, idx=pq.top().second;
		pq.pop();
		if(min_dist[idx]!=-1) continue;
		min_dist[idx]=dist;
		for(int i=0; i<edges_d[idx].size(); i++){
			long long next=edges_d[idx][i].first, n_dist=dist+edges_d[idx][i].second;
			if(min_dist[next]==-1) pq.push({-n_dist,next});
		}
	}
}




//=== Dinic ===
vector<int> edges[N];
int flow[N][N]; // Use map if N is larger than 20000
int capa[N][N];
int levels[N];
bool visited[N];
int work[N];
 
void add_edge(int a, int b, int c){ // edge a->b (c)
    // this is NOT bidirectional!
	edges[a].push_back(b); flow[a][b]=0; capa[a][b]=c;
	edges[b].push_back(a); flow[b][a]=0; capa[b][a]=0;
	// If capa accumulate, 
    //edges[a].push_back(b); flow[a][b]=0; capa[a][b]=c;
	//edges[b].push_back(a); flow[b][a]=0; capa[b][a]=0;
}
 
void level_BFS(int s){
	fill(visited,visited+N,false);
	queue<pair<int,int>> q;
	q.push({s,0});
	while(!q.empty()){
		int idx=q.front().first;
		int level=q.front().second;
		q.pop();
		if(visited[idx]) continue;
		levels[idx]=level;
		visited[idx]=true;
		for(int i=0; i<edges[idx].size(); i++){
			int next=edges[idx][i];
			if(!visited[next] && capa[idx][next]>flow[idx][next]){
				q.push({next,level+1});
			}
		}
	}
}
 
int main_DFS(int idx, int f, int t){
	visited[idx]=true;
	if(idx==t || f==0) return f;
	for(int &i=work[idx]; i<edges[idx].size(); i++){
		int next=edges[idx][i];
		if(!visited[next] && levels[next]==levels[idx]+1 && capa[idx][next]>flow[idx][next]){
			int f_temp=main_DFS(next,min(f,capa[idx][next]-flow[idx][next]),t);
			if(f_temp==0) continue;
			flow[idx][next]+=f_temp;
			flow[next][idx]-=f_temp;
			return f_temp;
		}
	}
	return 0;
}
 
int DINIC(int s, int t){
	int result=0;
	while(true){
		levels[t]=-1;
		level_BFS(s);
		if(levels[t]==-1) break;
 
		fill(work,work+N,0);
		while(true){
			fill(visited,visited+N,false);
			int f_temp=main_DFS(s,INF,t);
			if(f_temp==0) break;
			result+=f_temp;
		}
	}
	return result;
}
 
// 유량이 남은 모든 정점을 탐색
void cut_DFS(int idx){
	if(visited[idx]) return;
	visited[idx]=true;
	for(int i=0; i<edges[idx].size(); i++){
		int next=edges[idx][i];
		if(!visited[next] && capa[idx][next]>flow[idx][next]) cut_DFS(next);
	}
}




//=== DSU ===
int parent[300030];
int find(int idx){
	if(idx==parent[idx]) return idx;
	return parent[idx]=find(parent[idx]);
}
void c_union(int a, int b){
	a=find(a), b=find(b);
	parent[b]=a;
}



//=== Dynamic segtree (PST) ===
#define N_node 9000000 // V log|X_RANGE| scale 

class node_pst{
public:
    node_pst(){}
    int l_idx=-1, r_idx=-1; // 여기서 idx는 본인의 idx를 말한다.
    int val=0;    
};

class PST{
public:
    node_pst seg[N_node]; // All node datas // About 100MB
    int s_cnt=2; // 현재까지 사용한 node의 개수. 0 is not used, 1 is reserved for convention (for convention)
    void clear(){
        for(int i=0; i<s_cnt; i++) seg[i]=node_pst();
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
                seg[s_cnt]=node_pst();
                s_cnt++;
            }
            update_seg(seg[idx].l_idx,l,mid,t_idx,val);
        }
        else{
            if(seg[idx].r_idx==-1){
                seg[idx].r_idx=s_cnt;
                seg[s_cnt]=node_pst();
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




//=== Prime ===
#define N_PRIME 1000010
vector<int> prime;
bool is_prime[N_PRIME];

void build_prime(int n){
    // n<N_PRIME
    fill(is_prime+2,is_prime+n+1,true);
    for(int i=2; i<=n; i++){
        if(!is_prime[i]) continue;
        for(int j=2; i*j<=n; j++) is_prime[i*j]=false;
    }
    for(int i=2; i<=n; i++) if(is_prime[i]) prime.push_back(i);
}




//=== Factorization === 
vector<int> prime;
int prime_cnt[100];

void ppush(int num){
    if(prime.size()==0) prime.push_back(num);
    else if(prime[prime.size()-1]!=num) prime.push_back(num);
    prime_cnt[prime.size()-1]++;
}
void factorize(ll temp){
    while(temp!=1){
        ll end=sqrt(temp)+1;
        bool flag=false;
        for(int i=2; i<=end; i++){
            if(temp%i==0){
                ppush(i);
                temp=temp/i;
                flag=true;
                break;
            }
        }
        if(!flag){
            ppush(temp);
            break;
        }
    }
}




//=== FFT ===
 
typedef complex<double> cpx;
const int SZ = 1048576;


void FFT(cpx g[], bool inv = false){
    int n = SZ;
    for(int i = 1, j = 0; i < n; ++i){
        // j : bitwise reverse of i (10110 -> 01101)
        int b = n/2;
        while(!((j ^= b) & b)) b /= 2; // find left-most 1 bit of j, then reverse all the visited bit.
        if(i < j) swap(g[i], g[j]);
    }
    for(int k = 1; k < n; k *= 2){
        double a = (inv ? M_PI/k : -M_PI/k);
        cpx w(cos(a), sin(a));
        for(int i = 0; i < n; i += k*2){
            cpx wp(1, 0);
            for(int j = 0; j < k; ++j){
                cpx x = g[i+j], y = g[i+j+k] * wp;
                g[i+j] = x + y;
                g[i+j+k] = x - y;
                wp *= w;
            }
        }
    }
    if(inv){
        for(int i = 0; i < n; ++i)
            g[i] /= n;
    }
}

/*
//Simple implementation of bitwise reverse
//But relatively bad time performance. (616ms -> 880ms)
int temp=i;
int mul=(N>>1), j=0;
while(mul!=0){
    res+=mul*(temp%2);
    mul>>=1;
    temp>>=1;
}
*/




//=== Graph Coloring ===
// O(3^n)
vector<int> edges[100];
#define INF 100

int chromatic_number(int n){ // n is # of vertices of the graph
    // Minimum number of colors require to satisty "Graph Coloring Problem"
    assert(n<20); // O(3^N) algorithm
    int DP[(1<<n)];
    DP[0]=1; // Convinient in DP process 
    for(int k=0; k<n; k++){
        for(int j=0; j<(1<<k); j++){
            int num=(1<<k)+j, res=INF; // num indicates current subset
            bool indep=0;
            if(DP[j]==1){ // Check independence
                indep=1;
                for(auto next : edges[k]){
                    if(j&(1<<next)){
                        indep=0;
                        break;
                    }
                }
            }
            if(indep) res=1;
            else{
                for(int t=num; t>0; t=(t-1)&num){
                    // t swaps all the subsets of num
                    if(num==t) continue;
                    res=min(res, DP[t]+DP[num-t]);   
                }
            }
            DP[num]=res;
        }
    }
    return DP[(1<<n)-1];
}




//=== HLD and lazy seg ===
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

/*
int main(){
	// initialize n
	cnt=0;
	parent[0]=-1, top[0]=depth[0]=0;
	DFS(0,-1);
	DFS1(0);
	DFS2(0);
	s.build_seg(1,0,n-1);

	return 0;
}
*/




//=== KMP ===
string s_ref;
string s_sni;
int phi[N];
vector<int> match_res;

void get_phi(){
    int m=s_sni.size();
    phi[0]=0;
    for(int i=1, j=0; i<m; i++){
        while(j>0 && s_sni[i]!=s_sni[j]) j=phi[j-1];
        if(s_sni[i]==s_sni[j]) j++;
        phi[i]=j;
    }
}

void KMP(){
    int n=s_ref.size(), m=s_sni.size();
    match_res.clear();
    for(int i=0, j=0; i<n; i++){
        while(j!=0 && s_ref[i]!=s_sni[j]) j=phi[j-1];
        if(s_ref[i]==s_sni[j]) j++;
        if(j==m) match_res.push_back(i+1-m), j=phi[j-1];
    }
}



//=== Lazy cnt tree ===
class lazy_cnt_tree{
public:
	lazy_cnt_tree(){}
	long long seg[1<<19];
	void build_seg(int idx, int l, int r){
		if(l==r){
			// seg[idx]=datas[l];
			return;
		}
		int mid=(l+r)>>1;
		build_seg(2*idx,l,mid);
		build_seg(2*idx+1,mid+1,r);
		seg[idx]=0; // For multiple use
	}
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
};

lazy_cnt_tree lct;




//=== LCA_sparse ===
#define MAX 20 // Should satisfy (1<<(MAX-1)) >= N 

vector<int> edges[N];
int sparse[N][MAX];
int level[N];

void DFS_init(int idx, int p){
    sparse[idx][0]=p;
    for(int i=0; i<edges[idx].size(); i++){
        int next=edges[idx][i];
        if(next!=p){
            level[next]=level[idx]+1;
            DFS_init(next,idx);
        }
    }
}

void sparse_init(int s){
    level[s]=0;
    DFS_init(s,-1);
    for(int r=1; r<MAX; r++){
        for(int i=0; i<N; i++){
            if(sparse[i][r-1]==-1) sparse[i][r]=-1;
            else sparse[i][r]=sparse[sparse[i][r-1]][r-1];
        }
    }
}

int get_LCA(int a, int b){
    if(level[a]>level[b]) swap(a,b);
    for(int r=MAX-1; r>=0; r--){
        if(sparse[b][r]!=-1 && level[a]<=level[sparse[b][r]]) b=sparse[b][r];
    }
    if(a==b) return a;
    for(int r=MAX-1; r>=0; r--){
        if(sparse[a][r]!=-1 && sparse[b][r]!=-1 && sparse[b][r]!=sparse[a][r]){
            a=sparse[a][r], b=sparse[b][r]; 
        }
    }
    return sparse[a][0];
}


// int main(){
//     ios_base::sync_with_stdio(false); cin.tie(NULL);
//     int n,m,a,b;
//     cin>>n;
//     for(int i=0; i<n-1; i++){
//         cin>>a>>b;
//         a--, b--;
//         edges[a].push_back(b);
//         edges[b].push_back(a);
//     }
//     sparse_init(0);
//     cin>>m;
//     for(int i=0; i<m; i++){
//         cin>>a>>b;
//         cout<<get_LCA(a-1,b-1)+1<<endl;
//     }
// }   




//=== MCMF ===
vector<pair<int,int>> edges_d[N]; // next, cost. // Must initialize after each testcase
int capa[N][N];
int flow[N][N];
bool inQ[N]; // (inQ[i]) means dist[i] changed ans need to be visited.
int pre[N];
int dist[N];

void add_edge(int a, int b, int w, int f){
    // a->b cost:w capa:f (Reverse edge has negative weight)
    edges_d[a].push_back({b,w}); capa[a][b]=f; flow[a][b]=0;
    edges_d[b].push_back({a,-w}); capa[b][a]=0; flow[b][a]=0;
}

void floyd_warshall(int s){
    // Only update pre[], dist[] 
    fill(inQ, inQ+N, false);
    fill(dist, dist+N, INF);
    int ff=INF;
    queue<int> q;
    q.push(s);
    inQ[s]=true; // To maintain light queue
    dist[s]=0;
    while(!q.empty()){
        int idx=q.front(); inQ[idx]=false;
        q.pop();
        for(int i=0; i<edges_d[idx].size(); i++){
            int next=edges_d[idx][i].first, w=edges_d[idx][i].second; 
            if(capa[idx][next]-flow[idx][next]>0 && dist[idx]+w<dist[next]){
                dist[next]=dist[idx]+w;
                pre[next]=idx;
                if(!inQ[next]) q.push(next);
                inQ[next]=true;
            }
        }
        
    }
}

int MCMF(int s, int t){
    // Return minimum cost for maximum flow
    int res=0;
    while(true){
        floyd_warshall(s);
        if(dist[t]==INF) break;
        // Get flow
        int cur=t, ff=INF;
        while(cur!=s){
            ff=min(ff,capa[pre[cur]][cur]-flow[pre[cur]][cur]);
            cur=pre[cur];
        }
        // Flow update
        cur=t;
        while(cur!=s){
            flow[pre[cur]][cur]+=ff;
            flow[cur][pre[cur]]-=ff;
            cur=pre[cur];
        }
        res+=dist[t]*ff;
    }
    return res;
}




//=== Mo's algorithm ===
int sqrtN=400;

class Query{
public:
	int idx, s, e;
	bool operator < (Query &x){
		if(s/sqrtN != x.s/sqrtN) return s/sqrtN < x.s/sqrtN;
		return e < x.e;
	}
};

Query qs[N];
int ans[N];

void go(int idx){

}

void back(int idx){

}

// int main(){
//     ios_base::sync_with_stdio(false); cin.tie(NULL);
//     int q; // number of q
//     int s = qs[0].s, e = qs[0].e;
// 	for(int i=s; i<=e; i++){
// 		go(i);
// 	}
//     //ans[qs[0].idx] = ;

// 	for(int i=1; i<q; i++){
// 		while(s > qs[i].s) go(--s);
//         while(e < qs[i].e) go(++e);
//         while(s < qs[i].s) back(s++);
// 		while(e > qs[i].e) back(e--);
//         //ans[qs[i].idx] = ;
// 	}
// 	for(int i=0; i<q; i++) cout << ans[i] << endl;

//     return 0;
// }




//=== nCr ===
long long fact[N], f_inv[N];

void fill_fact(){
    fact[0]=1;
    for(int i=1; i<N; i++) fact[i]=fact[i-1]*i%MOD;
    fill(f_inv,f_inv+N,1);
    for(int k=0; k<30; k++){
        for(int i=0; i<N; i++){
            f_inv[i]=f_inv[i]*f_inv[i]%MOD;
            if((MOD-2)&(1<<(29-k))) f_inv[i]=f_inv[i]*fact[i]%MOD;
        }
    }
}

long long nCr(int n, int r){
    return ((fact[n]*f_inv[r])%MOD)*f_inv[n-r]%MOD;
}




//=== Count nonzero seg (nnz_seg) === // 화성지도 line swipping
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
        if(seg[idx].first>0) return r-l+1;
		if(t_l<=mid) result=(result+find_seg(2*idx,l,mid,t_l,t_r));
		if(t_r>mid) result=(result+find_seg(2*idx+1,mid+1,r,t_l,t_r));
		return result;
	}
};

nnz_seg s;




//=== NTT chinese ===

/* MOD = a 2^b + 1 일 때, [a, b, Primitive root] 순서쌍
N으로 사용하는 값이 2^b보다 크면 사용할 수 없다.
998244353 [119, 23, 3]
2281701377 [17, 27, 3]
2483027969 [37, 26, 3]
2113929217 [63, 25, 5]
104857601 [25, 22, 3]
1092616193 [521, 21, 3]
*/

ll SZ=1<<18;
#define MOD1 998244353
#define AA1 119
#define BB1 23
#define PR1 3
#define MOD2 2483027969
#define AA2 37
#define BB2 26
#define PR2 3
#define MAX_DIGIT 62

long long ari_inv(long long num, bool ver){
    long long res=1, mult=num;
    ll mod_c = (ver?MOD1:MOD2);
    for(ll i=0; i<MAX_DIGIT; i++){
        if((mod_c-2)&(1LL<<i)){
            res=(res*mult)%mod_c;
        }
        mult=(mult*mult)%mod_c;
    }
    return res;
}


void NTT(ll g[], bool ver, bool inv=false){
    ll mod_c=(ver?MOD1:MOD2), AA=(ver?AA1:AA2), BB=(ver?BB1:BB2), PR=(ver?PR1:PR2);
    ll n = SZ;
    ll w_pow[n+1];
    ll bit_cnt=0;
    for(; bit_cnt<=BB; bit_cnt++){
        if((n>>bit_cnt) == 1) break;
    }
    assert ((n>>bit_cnt)==1);

    // w^n % mod_c == 1 이어야 함.
    // w = PR^((p-1) / n) = PR ^ (a*2^(b-bit_cnt))
    ll w = 1;
    ll pow = AA<<(BB-bit_cnt);
    ll mul = PR;
    for(int i=0; i<MAX_DIGIT; i++){
        if(pow&(1LL<<i)) w=(w*mul)%mod_c;
        mul=(mul*mul)%mod_c;
    }
    w = (inv ? w : ari_inv(w,ver));
    
    for(ll i = 1, j = 0; i < n; ++i){
        ll b = n/2;
        while(!((j ^= b) & b)) b /= 2;
        if(i < j) swap(g[i], g[j]);
    }

    ll cnt=0;
    for(ll k = 1; k < n; k *= 2){
        cnt++;
        ll ww = w; // ww^(2*k) % mod_c == 1 이어야 함. ww=w^(n/(2*k))=w^(2^(bit_cnt-cnt))
        for(ll i=0; i<bit_cnt-cnt; i++) ww=(ww*ww)%mod_c;
        for(ll i=0; i<k; i++) w_pow[i]=(i==0?1:(w_pow[i-1]*ww)%mod_c);
        for(ll i = 0; i < n; i += k*2){
            ll wp = 1;
            for(ll j = 0; j < k; ++j){
                ll x = g[i+j], y = g[i+j+k]*w_pow[j];
                g[i+j] = (x + y); // mod_c*mod_c+mod_c가 ll로 표현된다면 중간과정에서 %MOD 필요없음.
                g[i+j+k] = (x - y);
            }
        }
        for(int i=0; i<n; i++) g[i]%=mod_c; // 위의 for문 동안 한 번만 방문
    }
    if(inv){
        ll ari_n = ari_inv(n,ver);
        for(ll i = 0; i < n; ++i)
            g[i] = (g[i]*ari_n)%mod_c;
    }
}

inline ll large_mul(ll a, ll b){
    // 이것 때문에 TLE가 뜨진 않는다.
    ll mod_c=(MOD1*MOD2);
    a=(a%mod_c+mod_c)%mod_c;
    b=(b%mod_c+mod_c)%mod_c;
    ll mul=a;
    ll res=0;
    for(int i=0; i<MAX_DIGIT; i++){
        if(b & (1LL<<i)) res=(res+mul)%mod_c;
        mul=(mul+mul)%mod_c;
    }
    return res;
}

/*
// for MOD1
NTT(datas1_M1, true, false);
NTT(datas2_M1, true, false);
for(ll i=0; i<SZ; i++) datas1_M1[i]=(datas1_M1[i]*datas2_M1[i])%MOD1;
NTT(datas1_M1, true, true);

// for MOD2
NTT(datas1_M2, false, false);
NTT(datas2_M2, false, false);
for(ll i=0; i<SZ; i++) datas1_M2[i]=(datas1_M2[i]*datas2_M2[i])%MOD2;
NTT(datas1_M2, false, true);

// Chinese Theorem
ll n1 = MOD2, n2=MOD1, MOD=(MOD1*MOD2);
ll s1 = ari_inv(MOD2, true), s2=ari_inv(MOD1, false);
for(int i=0; i<2*l; i++){
    datas1_M1[i] = (large_mul(datas1_M1[i]*n1,s1) + large_mul(datas1_M2[i]*n2,s2)) % MOD;
}
*/



//=== RMQ_sparse (Range Minimum Query) ===
#define LOG2 20

class RMQ{
public:
	long long sp_table[LOG2][N]; // NlogN size sparse table
	long long LG[N+1]; // LG[idx]=floor(log_2[idx]) 
	// Note that sp_table RMQ if fast(O(1) for each query), but it is immutable
	int info;
	void build_sparse(int n){
		//for(int i=0; i<n; i++) sp_table[0][i]=datas[i];
		for(int idx=1; (1<<idx)<=n; idx++){
			for(int i=0; i+(1<<idx)<=n; i++){
				sp_table[idx][i]=min(sp_table[idx-1][i],sp_table[idx-1][i+(1<<(idx-1))]);
			}   
		}
		LG[1]=0;
		for(int i=2; i<=n; i++) LG[i]=LG[i/2]+1;
	}
	long long query(int a, int b){
		// [a,b] minimum query
		assert(a<=b);
		int lgn=LG[b-a+1];
		return min(sp_table[lgn][a],sp_table[lgn][b-(1<<lgn)+1]);
	}
};
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);}





//=== Rotating Calipers (and Convex hull) ===
pair<ll,ll> datas[N]; // Vertices // Convex hull algorithm never permute initial vertices.
int sorted_idx[N]; // Idx of 'sorted' datas.
int ans[N]; // Elements of convex hull

inline bool CCW(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& c){
    return (b.fi-a.fi)*(c.se-a.se)-(b.se-a.se)*(c.fi-a.fi)>0; // 변 위의 점도 필요하다면 >=
}

inline bool CCW_4(const pair<ll,ll>& a, const pair<ll,ll>& na, const pair<ll,ll>& b, pair<ll,ll> &nb){
    return (na.fi-a.fi)*(nb.se-b.se)-(na.se-a.se)*(nb.fi-b.fi)>=0;
}

inline long long dist_2d(const pair<ll,ll>& a, const pair<ll,ll>& b){
    return (a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se);
}

class comp_c{
public:
    pair<ll,ll> mp;
    comp_c(pair<ll,ll> minpos){
        mp=minpos;
    }
    bool operator()(int a_idx, int b_idx){
        pair<ll,ll> a=datas[a_idx], b=datas[b_idx];
        ll com=(a.fi-mp.fi)*(b.se-mp.se)-(a.se-mp.se)*(b.fi-mp.fi);
        if(com==0) return dist_2d(a,mp)<dist_2d(b,mp);
        else return com>0;
    }
};

int convex_hull(int n){ // # number of vertices
    // Phase 1: Sort
    int m_idx=0;
    for(int i=1; i<n; i++) if(datas[m_idx]>datas[i]) m_idx=i;
    for(int i=0; i<n; i++) sorted_idx[i]=i;
    swap(sorted_idx[0], sorted_idx[m_idx]);
    sort(sorted_idx,sorted_idx+n,comp_c(datas[m_idx]));
    
    // Phase 2: Get Convexhull
    int st[N]; // Elements of st are the idx of datas 
    int cur=0, st_cnt=0; // cur : # of visited elements of s, st_cnt : # of elements in stack
    while(cur<n){
        while(st_cnt>=2 && !CCW(datas[st[st_cnt-2]],datas[st[st_cnt-1]],datas[sorted_idx[cur]])) st_cnt--;
        st[st_cnt++]=sorted_idx[cur++];
    }
    for(int i=0; i<st_cnt; i++) ans[i]=st[i]; // Counter clockwise, starts with leftmost vertices.
    return st_cnt;
}

pair<int,int> rotating_calipers(int sz_hull){ // # of vertices in convex hull.
    // ans[] must be filled before call this function.
    int mx_a, mx_b; // mx_a and mx_b are the idx of two vertices making the maximum distance.
    long long mx=0;
    for(int a=0, p=0; a<sz_hull; a++){
        while(p+1<sz_hull && CCW_4(datas[ans[a]], datas[ans[a+1]], datas[ans[p]], datas[ans[p+1]])){
            ll temp=dist_2d(datas[ans[a]], datas[ans[p]]);
            if(mx<temp) mx=temp, mx_a=ans[a], mx_b=ans[p];
            p++;
        }
        ll temp=dist_2d(datas[ans[a]], datas[ans[p]]);
        if(mx<temp) mx=temp, mx_a=ans[a], mx_b=ans[p];
    }
    return {mx_a, mx_b}; // Idx of initial vertices. i.e. datas[]
}




//=== SCC ===
vector<int> edges[N]; 
vector<int> r_edges[N];
int scc[N];
int order[N];
bool visited[N];
int cnt, scc_cnt; // Number of SCC's
int n; // Number of actual nodes in graph

// Set n before call init function.
void init_scc(){
    for(int i=0; i<n; i++) {edges[i].clear(), r_edges[i].clear();}
}


void DFS(int idx){
    visited[idx]=true;
    for(int i=0; i<edges[idx].size(); i++) if(!visited[edges[idx][i]]) DFS(edges[idx][i]);
    order[cnt]=idx; cnt++;
}

void r_DFS(int idx){
    visited[idx]=true;
    scc[idx]=cnt;
    for(int i=0; i<r_edges[idx].size(); i++) if(!visited[r_edges[idx][i]]) r_DFS(r_edges[idx][i]);
}

// Kosaraju's algorithm. Set n, edges, r_edges before call this function.
void get_scc(){
    fill(visited, visited+n, false), cnt=0;
    for(int i=0; i<n; i++) if(!visited[i]) DFS(i);
    fill(visited, visited+n, false), cnt=0;
    for(int i=n-1; i>=0; i--) if(!visited[order[i]]) {r_DFS(order[i]); cnt++;}
    scc_cnt=cnt;
}




//=== Segtree (Vanilla) ===
class segtree{
public:	
	int seg[1<<19];
	int info;
	segtree(){}
	segtree(int n){}
	
	void build_seg(int idx, int l, int r){
		if(l==r){
			// seg[idx]=datas[l];
			return;
		}
		int mid=(l+r)>>1;
		build_seg(2*idx,l,mid);
		build_seg(2*idx+1,mid+1,r);
		seg[idx]=(seg[2*idx]+seg[2*idx+1]); // Modify
	}

	void update_seg(int idx, int l, int r, int t_idx, int val){
		if(l==r){
			seg[idx]=val; // Modify
			return;
		}
		int mid=(l+r)>>1;
		if(t_idx<=mid) update_seg(2*idx,l,mid,t_idx, val);
		else update_seg(2*idx+1,mid+1,r,t_idx, val);
		seg[idx]=(seg[2*idx]+seg[2*idx+1]); // Modify
	}

	int find_seg(int idx, int l, int r, int t_l, int t_r){
		if(t_l<=l && r<=t_r) return seg[idx];
		int mid=(l+r)>>1, ans=0;
		if(t_l<=mid) ans=(ans+find_seg(2*idx,l,mid,t_l,t_r)); // Modify
		if(t_r>mid) ans=(ans+find_seg(2*idx+1,mid+1,r,t_l,t_r)); // Modify
		return ans;
	}
};

segtree seg;




//=== Suffix array & LCP ===
string s;
int g[N+1], temp_g[N]; // g[i]는 정렬 전 i번째 접미사가 접근하는 group ordering
int t; // 전역변수
int sa[N], order[N]; // inv_sa==order of suffix array

int LCP[N];

bool compare(int i, int j){
    if(g[i]==g[j]) return g[i+t]<g[j+t];
    else return g[i]<g[j];
}

// SA[i]는 정렬된 suffix중 i번째의 것이 원래의 suffix중 몇 번째냐
// order[i]는 SA[i]의 역함수인데, i번째의 원래 suffix가 정렬되면 몇 번째로 들어가냐.

void suffix_sort(const string &s){
    int n=s.size();
    for(int i=0; i<n; i++) sa[i]=i, g[i]=s[i]; // 대소관계만 중요
    g[n]=-1, temp_g[0]=0;
    //fill(temp_g,temp_g+n,0); // temp_g[SA[0]]=0이어야 하는데, 문제는 SA[0]은 이 시점에서는 모른다.
    for(t=1; t<n; t<<=1){
        // sa[i]는 이후에 나올 t개의 문자에 대해 정렬이 보장
        sort(sa,sa+n,compare);
        for(int i=1; i<n; i++){
            // temp_g는 지금까지 밝혀진 정보로도 확실히 크다면 +1, 아니면 이전 값과 동일.
            temp_g[sa[i]]=temp_g[sa[i-1]]+compare(sa[i-1],sa[i]); 
            // SQ[0], SA[1], ... , SA[n-1] 순서대로 업데이트 해주지.
        }
        for(int i=0; i<n; i++) g[i]=temp_g[i];
        // 2t영역에 대해 정렬이 보장.
        // i+t나 j+t가 N이상이 되면 어떡하는가? 그럴리는 없다. 남은 길이가 t개보다 작은 것이 있다는 건데, 
        // 그럼 이미 g[i]와 g[j]를 통해 완벽하게 sort가 된 상태임. (이전 단계에서 temp_g[i], temp_g[j]에다 같은 값을 할당했을리 없음.)
    }
    for(int i=0; i<n; i++) order[sa[i]]=i;
}

void get_lcp(const string &s){
    int n=s.size();
    for(int i=0, j=0; i<n; i++){
        if(order[i]!=0){
            // i는 이제 원래 idx임.
            // sa[order[i]]와 sa[order[i]-1]의 최대 일치 -> LCP[order[i]]
            // 원래 idx i의 정렬했을 때 바로 앞의 suffix의 원래 idx가 pre임.
            // LCP는 늘어나는 건 많이 늘어날 수 있지만, LCP가 줄어드는 일은 최대 1만큼만.
            int pre=sa[order[i]-1];
            while(max(i+j,pre+j)<n && s[i+j]==s[pre+j]) j++;
            LCP[order[i]]=j;
            j=max(j-1,0);
        }
    }
}



//=== trie ===
#define INF 1e18

long long f(long long x){
    long long res;
    // calculate f(x)
    return res;
}

long long ternary(long long s, long long e){
    // Return smallest x if there are multiple minimum values.
    while(3<=e-s){
        long long l=(s+s+e)/3, r=(s+e+e)/3;
        if(f(l)>f(r)) s=l;
        else e=r;
    }
    long long mx=INF, res;
    for(long long i=s; i<=e; i++){
        long long temp=f(i);
        if(mx>temp) mx=temp, res=i;
    }
    return res;
}





//=== Trie ===
#define NUM_ALPHA 26

class node_trie{
public:
    node_trie* next[NUM_ALPHA]={NULL,};
    char val; // 대부분 필요없다.
    int cnt=0; // 여기서 끝나는 단어들의 개수
    node_trie(){}
    node_trie(char c){
        val=c; 
    }
};

class trie{
public:
    node_trie* root= new node_trie();
    trie(){}
    bool is_s(string &s){
        return is_re(root, 0, s);
    }
    void insert_s(string &s){
        insert_re(root, 0, s);
    }
    void clear(){ // clear_all
        clear_re(root);
        for(int i=0; i<NUM_ALPHA; i++) root->next[i]=NULL;
    }

private: 
    bool is_re(node_trie *cur, int idx, string &s){
        if(idx==s.size()) return ((cur->cnt)>=1); // 여기까지 왔으면 그냥 true해도 되지 않나? 처음에 들어올 때 때문인가
        if((cur->next[s[idx]-'A'])==NULL) return false;
        return is_re(cur->next[s[idx]-'A'],idx+1,s);
    }
    void insert_re(node_trie* cur, int idx, string &s){
        if(idx==s.size()){
            cur->cnt++;
            return;
        }
        if((cur->next[s[idx]-'A'])==NULL) cur->next[s[idx]-'A']=new node_trie(s[idx]);
        insert_re(cur->next[s[idx]-'A'],idx+1,s);
    }
    void clear_re(node_trie* cur){
        for(int i=0; i<NUM_ALPHA; i++){
            if((cur->next[i])!=NULL){
                clear_re(cur->next[i]);
                delete cur->next[i];
            }
        }
    }
};

trie tr;





//=== TSP ===
vector<pair<int,double>> edges_d[12]; // {next, dist}
double DP[12][1<<12]; // [last_idx][visited] // must be initialized with INF
// DP[last_idx][visited] indicates that "Minimum TSP excluding the set {visited}, which ended with last_idx"
int n;

double TSP_DFS(int idx, int visit){
    if(visit==(1<<n)-1) return DP[idx][visit]=0;
    if(DP[idx][visit]!=INF) return DP[idx][visit];
    for(auto temp : edges_d[idx]){
        int next=temp.first;
        double dist=temp.second;
        if(visit&(1<<next)) continue;
        DP[idx][visit]=min(DP[idx][visit],TSP_DFS(next,visit|(1<<next))+dist);
    }
    return DP[idx][visit];
}
