// 에라토스테네스의 체

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

#define N_PRIME 1000010

bool is_prime[N_PRIME];
vector<int> primes;

void build_prime(int n){
    // n<N_PRIME
    fill(is_prime+2,is_prime+n+1,true);
    for(int i=2; i<=n; i++){
        if(!is_prime[i]) continue;
        for(int j=2; i*j<=n; j++) is_prime[i*j]=false;
    }
    for(int i=2; i<=n; i++) if(is_prime[i]) primes.push_back(i);
}

// 소인수분해 코드
int datas[100000];
int cnt[100000]; // 1~1e6까지 소수가 약 7만개 수준 1~1e7까지는 70만개 수준

int main(){
    int n;
    cin>>n;
    for(int i=0; i<n; i++) cin>>datas[i];

    // 다음의 코드는 datas[0]*datas[1]*...*datas[n-1]의 소인수분해를 해뿐다.
    // behavior를 바꾸고 싶으면 cnt[j]값을 더하는 대신에 cnt[i].push_back(j); 등으로 바꾸면 됨.
    for(int i=0; i<n; i++){
        int temp=datas[i];
        for(int j=0; j<primes.size(); j++){
            if(primes[j]>sqrt(temp) || primes[j]>=temp) break;
            while(temp>primes[j] && temp%primes[j]==0){
                temp/=primes[j];
                cnt[j]++;
            }
        }
        // 그럼 이제 지금 temp는 소수인 상황
        int idx=lower_bound(primes.begin(), primes.end(), temp)-primes.begin();
        cnt[idx]++;
    }
    return 0;
}