// LCP[1] + ... + LCP[N-1] �� ��� �ߺ��Ǵ� substring�� ����

// result <- result + max(0,prev-LCP[i])
// prev <- LCP[i]
// �̷��� �ߺ��Ǵ� substring�� ������ ��´�.

#include <bits/stdc++.h>
using namespace std;

#define N 200000
string s;
int g[N+1], temp_g[N]; // g[i]�� ���� �� i��° ���̻簡 �����ϴ� group ordering
int t; // ��������
int sa[N], order[N]; // inv_sa==order of suffix array

int LCP[N];

bool compare(int i, int j){
    if(g[i]==g[j]) return g[i+t]<g[j+t];
    else return g[i]<g[j];
}

// SA[i]�� ���ĵ� suffix�� i��°�� ���� ������ suffix�� �� ��°��
// order[i]�� SA[i]�� ���Լ��ε�, i��°�� ���� suffix�� ���ĵǸ� �� ��°�� ����.

void suffix_sort(const string &s){
    int n=s.size();
    for(int i=0; i<n; i++) sa[i]=i, g[i]=s[i]; // ��Ұ��踸 �߿�
    g[n]=-1, temp_g[0]=0;
    //fill(temp_g,temp_g+n,0); // temp_g[SA[0]]=0�̾�� �ϴµ�, ������ SA[0]�� �� ���������� �𸥴�.
    for(t=1; t<n; t<<=1){
        // sa[i]�� ���Ŀ� ���� t���� ���ڿ� ���� ������ ����
        sort(sa,sa+n,compare);
        for(int i=1; i<n; i++){
            // temp_g�� ���ݱ��� ������ �����ε� Ȯ���� ũ�ٸ� +1, �ƴϸ� ���� ���� ����.
            temp_g[sa[i]]=temp_g[sa[i-1]]+compare(sa[i-1],sa[i]); 
            // SQ[0], SA[1], ... , SA[n-1] ������� ������Ʈ ������.
        }
        for(int i=0; i<n; i++) g[i]=temp_g[i];
        // 2t������ ���� ������ ����.
        // i+t�� j+t�� N�̻��� �Ǹ� ��ϴ°�? �׷����� ����. ���� ���̰� t������ ���� ���� �ִٴ� �ǵ�, 
        // �׷� �̹� g[i]�� g[j]�� ���� �Ϻ��ϰ� sort�� �� ������. (���� �ܰ迡�� temp_g[i], temp_g[j]���� ���� ���� �Ҵ������� ����.)
    }
    for(int i=0; i<n; i++) order[sa[i]]=i;
}

void get_lcp(const string &s){
    int n=s.size();
    for(int i=0, j=0; i<n; i++){
        if(order[i]!=0){
            // i�� ���� ���� idx��.
            // sa[order[i]]�� sa[order[i]-1]�� �ִ� ��ġ -> LCP[order[i]]
            // ���� idx i�� �������� �� �ٷ� ���� suffix�� ���� idx�� pre��.
            // LCP�� �þ�� �� ���� �þ �� ������, LCP�� �پ��� ���� �ִ� 1��ŭ��.
            int pre=sa[order[i]-1];
            while(max(i+j,pre+j)<n && s[i+j]==s[pre+j]) j++;
            LCP[order[i]]=j;
            j=max(j-1,0);
        }
    }
}