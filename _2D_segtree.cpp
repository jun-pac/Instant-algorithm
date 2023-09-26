#include <bits/stdc++.h>
#define endl '\n'
using namespace std;


#define INF 1000000007

int datas[1<<10][1<<10];
int td_seg[1<<11][1<<11];

void build_td_seg(int idx1, int l1, int r1, int idx2, int l2, int r2){
    if(l1==r1 && l2==r2){
        td_seg[idx1][idx2]=datas[l1][l2];
    }
    else if(l1==r1){
        int mid2=(l2+r2)>>1;
        build_td_seg(idx1,l1,r1,2*idx2,l2,mid2);
        build_td_seg(idx1,l1,r1,2*idx2+1,mid2+1,r2);
        td_seg[idx1][idx2]=td_seg[idx1][2*idx2]+td_seg[idx1][2*idx2+1];
    }
    else{
        int mid1=(l1+r1)>>1;
        build_td_seg(2*idx1,l1,mid1,idx2,l2,r2);
        build_td_seg(2*idx1+1,mid1+1,r1,idx2,l2,r2);
        td_seg[idx1][idx2]=td_seg[2*idx1][idx2]+td_seg[2*idx1+1][idx2];
        if(l2!=r2){
            int mid2=(l2+r2)>>1;
            build_td_seg(idx1,l1,r1,2*idx2,l2,mid2);
            build_td_seg(idx1,l1,r1,2*idx2+1,mid2+1,r2);
        }
    }
}

void update_td_seg(int idx1, int l1, int r1, int t1, int idx2, int l2, int r2, int t2, int val){
    if(l1==r1 && l2==r2){
        td_seg[idx1][idx2]=val;
    }
    else if(l1==r1){
        int mid2=(l2+r2)>>1;
        if(t2<=mid2) update_td_seg(idx1,l1,r1,t1,2*idx2,l2,mid2,t2,val);
        if(t2>mid2) update_td_seg(idx1,l1,r1,t1,2*idx2+1,mid2+1,r2,t2,val);
        td_seg[idx1][idx2]=td_seg[idx1][2*idx2]+td_seg[idx1][2*idx2+1];
    }
    else{
        int mid1=(l1+r1)>>1;
        if(t1<=mid1) update_td_seg(2*idx1,l1,mid1,t1,idx2,l2,r2,t2,val);
        if(t1>mid1) update_td_seg(2*idx1+1,mid1+1,r1,t1,idx2,l2,r2,t2,val);
        td_seg[idx1][idx2]=td_seg[2*idx1][idx2]+td_seg[2*idx1+1][idx2];
        if(l2!=r2){
            int mid2=(l2+r2)>>1;
            if(t2<=mid2) update_td_seg(idx1,l1,r1,t1,2*idx2,l2,mid2,t2,val);
            if(t2>mid2) update_td_seg(idx1,l1,r1,t1,2*idx2+1,mid2+1,r2,t2,val);
        }
    }
}

int find_td_seg(int idx1, int l1, int r1, int tl1, int tr1, int idx2, int l2, int r2, int tl2, int tr2){
    if(tl1<=l1 && r1<=tr1 && tl2<=l2 && r2<=tr2){
        return td_seg[idx1][idx2];
    }
    else if(tl1<=l1 && r1<=tr1){
        int res=0;
        int mid2=(l2+r2)>>1;
        if(tl2<=mid2) res=res+find_td_seg(idx1,l1,r1,tl1,tr1,2*idx2,l2,mid2,tl2,tr2);
        if(tr2>mid2) res=res+find_td_seg(idx1,l1,r1,tl1,tr1,2*idx2+1,mid2+1,r2,tl2,tr2);
        return res;
    }
    else{
        int res=0;
        int mid1=(l1+r1)>>1;
        if(tl1<=mid1) res=res+find_td_seg(2*idx1,l1,mid1,tl1,tr1,idx2,l2,r2,tl2,tr2);
        if(tr1>mid1) res=res+find_td_seg(2*idx1+1,mid1+1,r1,tl1,tr1,idx2,l2,r2,tl2,tr2);
        return res;
    }
}

/*
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n,m;
    cin>>n>>m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>datas[i][j];
        }
    }
    build_td_seg(1,0,n-1,1,0,n-1);
    for(int i=0; i<m; i++){
        int t;
        cin>>t;
        if(t==0){
            int a,b,c;
            cin>>a>>b>>c;
            a--, b--;
            update_td_seg(1,0,n-1,a,1,0,n-1,b,c);
        }
        else{
            int a,b,c,d;
            cin>>a>>b>>c>>d;
            a--, b--, c--, d--;
            cout<<find_td_seg(1,0,n-1,a,c,1,0,n-1,b,d)<<endl;
        }
    }
    return 0;
}
*/