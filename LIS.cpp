// LIS

#include <bits/stdc++.h>
using namespace std;

#define N 100001
#define INF 1000000007
int datas[N];
int DP[N];
int LIS(int datas[], int n){
    fill(DP,DP+n,INF);
    int mx=0;
    // ����������(��, ���Ƶ� �Ǹ�) upper_bound�� ����, �׷��� ������ lower_bound
    for(int i=0; i<n; i++){
        int idx=upper_bound(DP,DP+n,datas[i])-DP;
        DP[idx]=datas[i];
        mx=max(mx,idx+1);
    }
    return mx;
}