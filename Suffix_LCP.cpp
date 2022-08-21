
#include <bits/stdc++.h>
using namespace std;

#define N 200000
string s;
int g[N+1], temp_g[N]; // g[i]는 정렬 전 i번째 접미사가 접근하는 group ordering
int t; // 전역변수
int sa[N], order[N]; // inv_sa==order of suffix array

int LCP[N];

bool compare(int i, int j){
    if(g[i]==g[j]) return g[i+t]<g[j+t];
    else return g[i]<g[j];
}

void suffix_sort(const string &s){
    int n=s.size();
    for(int i=0; i<n; i++) sa[i]=i, g[i]=s[i]; // 대소관계만 중요
    g[n]=-1, temp_g[0]=0;
    for(t=1; t<n; t<<=1){
        sort(sa,sa+n,compare);
        for(int i=1; i<n; i++){
            temp_g[sa[i]]=temp_g[sa[i-1]]+compare(sa[i-1],sa[i]); 
        }
        for(int i=0; i<n; i++) g[i]=temp_g[i];
    }
    for(int i=0; i<n; i++) order[sa[i]]=i;
}

void get_lcp(const string &s){
    int n=s.size();
    for(int i=0, j=0; i<n; i++){
        if(order[i]!=0){
            // sa[order[i]]와 sa[order[i]-1]의 최대 일치 -> LCP[order[i]]
            int pre=sa[order[i]-1];
            while(max(i+j,pre+j)<n && s[i+j]==s[pre+j]) j++;
            LCP[order[i]]=j;
            j=max(j-1,0);
        }
    }
}