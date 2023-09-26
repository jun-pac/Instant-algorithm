// 
// NTT

#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

typedef long long ll;

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
    ll MOD = (ver?MOD1:MOD2);
    for(ll i=0; i<MAX_DIGIT; i++){
        if((MOD-2)&(1LL<<i)){
            res=(res*mult)%MOD;
        }
        mult=(mult*mult)%MOD;
    }
    return res;
}


void NTT(ll g[], bool ver, bool inv=false){
    ll MOD=(ver?MOD1:MOD2), AA=(ver?AA1:AA2), BB=(ver?BB1:BB2), PR=(ver?PR1:PR2);
    ll n = SZ;
    ll w_pow[n+1];
    ll bit_cnt=0;
    for(; bit_cnt<=BB; bit_cnt++){
        if((n>>bit_cnt) == 1) break;
    }
    assert ((n>>bit_cnt)==1);

    // w^n % MOD == 1 이어야 함.
    // w = PR^((p-1) / n) = PR ^ (a*2^(b-bit_cnt))
    ll w = 1;
    ll pow = AA<<(BB-bit_cnt);
    ll mul = PR;
    for(int i=0; i<MAX_DIGIT; i++){
        if(pow&(1LL<<i)) w=(w*mul)%MOD;
        mul=(mul*mul)%MOD;
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
        ll ww = w; // ww^(2*k) % MOD == 1 이어야 함. ww=w^(n/(2*k))=w^(2^(bit_cnt-cnt))
        for(ll i=0; i<bit_cnt-cnt; i++) ww=(ww*ww)%MOD;
        for(ll i=0; i<k; i++) w_pow[i]=(i==0?1:(w_pow[i-1]*ww)%MOD);
        for(ll i = 0; i < n; i += k*2){
            ll wp = 1;
            for(ll j = 0; j < k; ++j){
                ll x = g[i+j], y = g[i+j+k]*w_pow[j];
                g[i+j] = (x + y); // MOD*MOD+MOD가 ll로 표현된다면 중간과정에서 %MOD 필요없음.
                g[i+j+k] = (x - y);
            }
        }
        for(int i=0; i<n; i++) g[i]%=MOD; // 위의 for문 동안 한 번만 방문
    }
    if(inv){
        ll ari_n = ari_inv(n,ver);
        for(ll i = 0; i < n; ++i)
            g[i] = (g[i]*ari_n)%MOD;
    }
}

inline ll large_mul(ll a, ll b){
    // 이것 때문에 TLE가 뜨진 않는다.
    ll MOD=(MOD1*MOD2);
    a=(a%MOD+MOD)%MOD;
    b=(b%MOD+MOD)%MOD;
    ll mul=a;
    ll res=0;
    for(int i=0; i<MAX_DIGIT; i++){
        if(b & (1LL<<i)) res=(res+mul)%MOD;
        mul=(mul+mul)%MOD;
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