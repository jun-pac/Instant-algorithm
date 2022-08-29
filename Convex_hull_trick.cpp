#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define N 100000
#define INF 1e18+7

using namespace std;

typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

template<typename T>
inline T umax(T &u, T v){return u = max(u, v);}
template<typename T>
inline T umin(T &u, T v){return u = min(u, v);}

ll DP[N];

class CHT{
public:
    // Line : y=Ax+b
    pair<ll,ll> lines[N]; // Line stack : a(slope), b(offset)
    double x_start[N]; // x_start[0] is always -INF
    int l_cnt; // Current # of line in stack
    
    CHT(){
        l_cnt=0;
        // Intialize first line.
        //lines[l_cnt]={2*(com_datas[0].se-com_datas[0].fi),\
        //(com_datas[0].fi-com_datas[0].se)*(com_datas[0].fi-com_datas[0].se)};
        x_start[l_cnt++]=-INF;
    }

    inline ll get_x(int i){
        ll x_i; // Implement
        return x_i;
    }

    inline ll get_y(ll x){
        // Binary search fo find appropriate line segment.
        int num=upper_bound(x_start,x_start+l_cnt,x)-x_start-1;
        ll y_x_num; // Implement
        return y_x_num;
    }

    inline ll get_R(int i){
        ll r_i; // Implement
        return r_i;
    }

    inline ll get_A(int i){
        ll a_i; // Implement
        return a_i;
    }

    inline ll get_B(int i){
        ll b_i; // Implement. Following structure does not necessarily have to be followed.
        if(i==-1) return b_i;
        return DP[i]+b_i;
    }
    
    void push_line(ll A, ll B){
        double x_inter;
        while(true){
            x_inter=((double)B-lines[l_cnt-1].se)/((double)lines[l_cnt-1].fi-A);
            if(l_cnt==1 || x_inter>x_start[l_cnt-1]) break;
            l_cnt--;
        }
        lines[l_cnt]={A,B};
        x_start[l_cnt++]=x_inter;
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    // Prepare data structures for CHT
    int cnt; // # of effective elements. 
    CHT cht=CHT();
    for(int i=0; i<cnt; i++){
        ll x=cht.get_x(i);
        DP[i]=cht.get_y(x)+cht.get_R(i);
        if(i==cnt-1) break;
        ll A=cht.get_A(i), B=cht.get_B(i);
        cht.push_line(A,B);
    }
    return 0;
}
