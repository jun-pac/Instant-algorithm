// 
//./F<test

#include <bits/stdc++.h>
#define endl '\n'
#define cediv(a,b) ((a)%(b)==0?((a)/(b)):((a)/(b))+1)
#define fi first
#define se second
#define pb push_back

using namespace std;

typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

template<typename T>
inline T umax(T &u, T v){return u = max(u, v);}
template<typename T>
inline T umin(T &u, T v){return u = min(u, v);}

#define INF 1000000007

int sqrtN;

class Query{
public:
	int idx, s, e;
	bool operator < (Query &x){
		if(s/sqrtN != x.s/sqrtN) return s/sqrtN < x.s/sqrtN;
		return e < x.e;
	}
};

Query qs[1000000];
int ans[1000000];

void go(int idx){

}

void back(int idx){

}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; // number of q
    int s = qs[0].s, e = qs[0].e;
	for(int i=s; i<=e; i++){
		go(i);
	}
    //ans[qs[0].idx] = ;

	for(int i=1; i<q; i++){
		while(s < qs[i].s) back(s++);
		while(s > qs[i].s) go(--s);
		while(e < qs[i].e) go(++e);
		while(e > qs[i].e) back(e--);
        //ans[qs[i].idx] = ;
	}
	for(int i=0; i<q; i++) cout << ans[i] << endl;

    return 0;
}