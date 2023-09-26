// �����佺�׳׽��� ü

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

// ���μ����� �ڵ�
int datas[100000];
int cnt[100000]; // 1~1e6���� �Ҽ��� �� 7���� ���� 1~1e7������ 70���� ����

int main(){
    int n;
    cin>>n;
    for(int i=0; i<n; i++) cin>>datas[i];

    // ������ �ڵ�� datas[0]*datas[1]*...*datas[n-1]�� ���μ����ظ� �ػӴ�.
    // behavior�� �ٲٰ� ������ cnt[j]���� ���ϴ� ��ſ� cnt[i].push_back(j); ������ �ٲٸ� ��.
    for(int i=0; i<n; i++){
        int temp=datas[i];
        for(int j=0; j<primes.size(); j++){
            if(primes[j]>sqrt(temp) || primes[j]>=temp) break;
            while(temp>primes[j] && temp%primes[j]==0){
                temp/=primes[j];
                cnt[j]++;
            }
        }
        // �׷� ���� ���� temp�� �Ҽ��� ��Ȳ
        int idx=lower_bound(primes.begin(), primes.end(), temp)-primes.begin();
        cnt[idx]++;
    }
    return 0;
}