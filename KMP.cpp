#include <bits/stdc++.h>
using namespace std;

#define N 2020202
string s_ref;
string s_sni;
int phi[N];
vector<int> match_res;

void get_phi(){
    int m=s_sni.size();
    phi[0]=0;
    for(int i=1, j=0; i<m; i++){
        while(j>0 && s_sni[i]!=s_sni[j]) j=phi[j-1];
        if(s_sni[i]==s_sni[j]) j++;
        phi[i]=j;
    }
}

void KMP(){
    int n=s_ref.size(), m=s_sni.size();
    match_res.clear();
    for(int i=0, j=0; i<n; i++){
        while(j!=0 && s_ref[i]!=s_sni[j]) j=phi[j-1];
        if(s_ref[i]==s_sni[j]) j++;
        if(j==m) match_res.push_back(i+1-m), j=phi[j-1];
    }
}