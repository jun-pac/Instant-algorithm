// LCP[1] + ... + LCP[N-1] 은 모든 중복되는 substring의 개수

// result <- result + max(0,prev-LCP[i])
// prev <- LCP[i]
// 이러면 중복되는 substring의 종류를 얻는다.

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

// SA[i]는 정렬된 suffix중 i번째의 것이 원래의 suffix중 몇 번째냐
// order[i]는 SA[i]의 역함수인데, i번째의 원래 suffix가 정렬되면 몇 번째로 들어가냐.

void suffix_sort(const string &s){
    int n=s.size();
    for(int i=0; i<n; i++) sa[i]=i, g[i]=s[i]; // 대소관계만 중요
    g[n]=-1, temp_g[0]=0;
    //fill(temp_g,temp_g+n,0); // temp_g[SA[0]]=0이어야 하는데, 문제는 SA[0]은 이 시점에서는 모른다.
    for(t=1; t<n; t<<=1){
        // sa[i]는 이후에 나올 t개의 문자에 대해 정렬이 보장
        sort(sa,sa+n,compare);
        for(int i=1; i<n; i++){
            // temp_g는 지금까지 밝혀진 정보로도 확실히 크다면 +1, 아니면 이전 값과 동일.
            temp_g[sa[i]]=temp_g[sa[i-1]]+compare(sa[i-1],sa[i]); 
            // SQ[0], SA[1], ... , SA[n-1] 순서대로 업데이트 해주지.
        }
        for(int i=0; i<n; i++) g[i]=temp_g[i];
        // 2t영역에 대해 정렬이 보장.
        // i+t나 j+t가 N이상이 되면 어떡하는가? 그럴리는 없다. 남은 길이가 t개보다 작은 것이 있다는 건데, 
        // 그럼 이미 g[i]와 g[j]를 통해 완벽하게 sort가 된 상태임. (이전 단계에서 temp_g[i], temp_g[j]에다 같은 값을 할당했을리 없음.)
    }
    for(int i=0; i<n; i++) order[sa[i]]=i;
}

void get_lcp(const string &s){
    int n=s.size();
    for(int i=0, j=0; i<n; i++){
        if(order[i]!=0){
            // i는 이제 원래 idx임.
            // sa[order[i]]와 sa[order[i]-1]의 최대 일치 -> LCP[order[i]]
            // 원래 idx i의 정렬했을 때 바로 앞의 suffix의 원래 idx가 pre임.
            // LCP는 늘어나는 건 많이 늘어날 수 있지만, LCP가 줄어드는 일은 최대 1만큼만.
            int pre=sa[order[i]-1];
            while(max(i+j,pre+j)<n && s[i+j]==s[pre+j]) j++;
            LCP[order[i]]=j;
            j=max(j-1,0);
        }
    }
}