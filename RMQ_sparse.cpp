

#include <bits/stdc++.h>
using namespace std;
#define N 300030
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
/*
#define N 100010
#define LOG2 18 // (1<<18) > N
typedef long long ll;

int datas[N];
int sp_table[LOG2][N]; // NlogN size sparse table
int LG[N+1]; // LG[idx]=floor(log_2[idx]) 
// Note that sp_table RMQ if fast(O(1) for each query), but it is immutable

void build_sparse(int n){
    for(int i=0; i<n; i++) sp_table[0][i]=datas[i];
    for(int idx=1; (1<<idx)<=n; idx++){
        for(int i=0; i+(1<<idx)<=n; i++){
            //cover하는 범위는 [i,i+(1<<idx)) 입니다.
            sp_table[idx][i]=min(sp_table[idx-1][i],sp_table[idx-1][i+(1<<(idx-1))]);
        }   
    }
    LG[1]=0;
    for(int i=2; i<=n; i++) LG[i]=LG[i/2]+1;
}

inline int RMQ(int a, int b){
    // [a,b] minimum query
    int lgn=LG[b-a+1];
    return min(sp_table[lgn][a],sp_table[lgn][b-(1<<lgn)+1]);
}*/


/*
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0; i<n; i++) cin>>datas[i];
    build_sparse(n);
    for(int i=1; i<n+1; i++) cout<<i<<' '<<LG[i]<<endl;
    int a,b;
    for(int i=0; i<m; i++){
        cin>>a>>b;
        cout<<RMQ(a-1,b-1)<<endl;
    }
    return 0;
}
*/
