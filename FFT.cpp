
#include <bits/stdc++.h>

using namespace std;
 
typedef complex<double> cpx;
const int SZ = 1048576;
 
void FFT(cpx f[], bool inv = false){
    int n = SZ;
    for(int i = 1, j = 0; i < n; ++i){
        int b = n/2;
        while(!((j ^= b) & b)) b /= 2;
        if(i < j) swap(f[i], f[j]);
    }
    for(int k = 1; k < n; k *= 2){
        double a = (inv ? M_PI/k : -M_PI/k);
        cpx w(cos(a), sin(a));
        for(int i = 0; i < n; i += k*2){
            cpx wp(1, 0);
            for(int j = 0; j < k; ++j){
                cpx x = f[i+j], y = f[i+j+k] * wp;
                f[i+j] = x + y;
                f[i+j+k] = x - y;
                wp *= w;
            }
        }
    }
    if(inv){
        for(int i = 0; i < n; ++i)
            f[i] /= n;
    }
}
