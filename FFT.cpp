
#include <bits/stdc++.h>

using namespace std;
 
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