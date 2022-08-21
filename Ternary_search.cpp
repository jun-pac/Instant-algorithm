// Ternary search

#include <bits/stdc++.h>
using namespace std;

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