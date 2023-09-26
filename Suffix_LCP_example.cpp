// LCP[1] + ... + LCP[N-1] �� ��� �ߺ��Ǵ� substring�� ����

// result <- result + max(0,prev-LCP[i])
// prev <- LCP[i]
// �̷��� �ߺ��Ǵ� substring�� ������ ��´�.

// ���ڿ� X (LCP�� Ȱ��) - �־��� ���ڿ� �� ��Ȯ�� K���� ���ڿ��� ���ԵǴ� ���ڿ��� ������ ���ϴ� ��.
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

typedef long long ll;


#define N 1000001
#define INF 1000000007

string s;
string datas[N];
int pos[N], cnt[N], group[N];
int mx_lcp[N];
int g[N+1], temp_g[N]; // g[i]�� ���� �� i��° ���̻簡 �����ϴ� group ordering
int t; // ��������
int sa[N], order[N]; // inv_sa==order of suffix array
int LCP[N];
int n, nn; // n�� string�� ����, nn�� �̰͵� ��ģ s.size()�� ũ��

bool compare(int i, int j){
    if(g[i]==g[j]) return g[i+t]<g[j+t];
    else return g[i]<g[j];
}

void suffix_sort(const string &s){
    int n=s.size();
    for(int i=0; i<n; i++) sa[i]=i, g[i]=s[i]; 
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
            int pre=sa[order[i]-1];
            while(max(i+j,pre+j)<n && s[i+j]==s[pre+j]) j++;
            LCP[order[i]]=j;
            j=max(j-1,0);
        }
    }
}

int seg[1<<21];

void build_seg(int idx, int l, int r){
    if(l==r){
        seg[idx]=LCP[l];
        return;
    }
    int mid=(l+r)>>1;
    build_seg(2*idx,l,mid);
    build_seg(2*idx+1,mid+1,r);
    seg[idx]=min(seg[2*idx],seg[2*idx+1]); // Some other operation
}

int find_seg(int idx, int l, int r, int t_l, int t_r){
    if(t_l<=l && r<=t_r) return seg[idx];
    int mid=(l+r)>>1, ans=INF;
    if(t_l<=mid) ans=min(ans,find_seg(2*idx,l,mid,t_l,t_r));
    if(t_r>mid) ans=min(ans,find_seg(2*idx+1,mid+1,r,t_l,t_r));
    return ans;
}

ll solve(ll k){
    // k�� �̻��� ���ڿ��� ���ԵǴ� ������ �����ش�.
    ll res_k=0;
    int l=0, r, cur=0; // cur�� ���� [l,r]�� �ִ� ���� �ٸ� ���� ����
    int prev=0; // ���� l���� ���� �ִ��� ����. �� l���� ������Ʈ�� ����� ��.
    while(s[sa[l]]=='$') l++;
    fill(cnt,cnt+n,0);
    cur=0;
    cnt[group[sa[l]]]++;
    cur++;
    r=l;
    for(; l<s.size(); l++){
        while(r+1<s.size() && cur<k){
            r++;
            if(cnt[group[sa[r]]]==0) cur++;
            cnt[group[sa[r]]]++;
        }
        if(cur<k) break;
        int temp = (l==r?mx_lcp[sa[l]]:find_seg(1,0,nn-1,l+1,r)); 
        res_k+=max(0,temp-prev);
        prev=temp;

        cnt[group[sa[l]]]--;
        if(cnt[group[sa[l]]]==0) cur--;
        if(cur<k && r!=nn-1) prev=min(prev,LCP[r+1]); 
    }
    return res_k;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int k;
    cin>>n>>k;
    for(int i=0; i<n; i++) cin>>datas[i];
    pos[0]=0;
    s+=datas[0];
    s+="$";
    for(int j=pos[0]; j<=pos[0]+datas[0].size(); j++) mx_lcp[j]=pos[0]+datas[0].size()-j;
    for(int j=pos[0]; j<pos[0]+datas[0].size(); j++) group[j]=0;

    for(int i=1; i<n; i++){
        pos[i]=s.size();
        s+=datas[i];
        s+="$";
        for(int j=pos[i]; j<=pos[i]+datas[i].size(); j++) mx_lcp[j]=pos[i]+datas[i].size()-j;
        for(int j=pos[i]; j<pos[i]+datas[i].size(); j++) group[j]=i;
    }

    suffix_sort(s);
    get_lcp(s);

    // #�� �������� �ʵ��� LCP�� ������ �ʿ䰡 ����
    for(int i=0; i<s.size(); i++) LCP[i]=min(LCP[i],mx_lcp[sa[i]]); // sa[i]�� ���ľ� ������ ��ġ�� ��.


    // segtree����� : min(LCP[...])�� ����ϴ� �뵵
    nn=s.size();
    build_seg(1,0,nn-1);


    // k�̻��� ���� - k+1�̻��� ����
    cout<<solve(k)-solve(k+1)<<endl;
    return 0;
}