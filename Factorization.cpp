// Factorization

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
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    return 0;
}