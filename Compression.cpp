// Data compression
#include <bits/stdc++.h>
#define N_ 300030
typedef long long ll;
using namespace std;

pair<ll, ll> datas[N_]; // Ranges indicate [l,r]
vector<ll> pos;

int main(){
    int n,m; // n is # of segments, m is total available range of number.
	cin>>n>>m;
    pos.clear(); // In case of multiple TCs.
	for(int i=0; i<n; i++){
		cin>>datas[i].first>>datas[i].second;
		pos.push_back(datas[i].first); // plus range [l,inf)
		pos.push_back(datas[i].second+1); // minus range [r+1,inf) 
	}
	pos.push_back(1); // '1' is the first possible value.
	pos.push_back(m+1); // 'm+1'is the first impossible value after range/
	sort(pos.begin(),pos.end());
	pos.erase(unique(pos.begin(), pos.end()),pos.end()); 
	int M=(int)pos.size()-1; // The purpose of last segment [M+1, inf) is for marking bound, so it should not be used.
	// If pos is an array, // int tempn=2*n+2; int M=unique(pos,pos+tempn)-pos; M--;
	// Each compressed element i indicate actual range of [pos[i],pos[i+1])

	//s.build_seg(1,0,M-1);
	for(int i=0; i<n; i++){
		int pl=lower_bound(pos.begin(),pos.end(),datas[i].first)-pos.begin();
		int pr=lower_bound(pos.begin(),pos.end(),datas[i].second+1)-pos.begin(); // Compressed idx should be determined based on r+1 !!
		datas[i]={pl,pr-1}; // Compressed range of segment i.
		//s.update_seg(1,0,M-1,datas[i].first,datas[i].second,1);
	}
}