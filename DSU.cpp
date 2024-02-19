// union_find

#include <bits/stdc++.h>
using namespace std;

int parent[300030];
int find(int idx){
	if(idx==parent[idx]) return idx;
	return parent[idx]=find(parent[idx]);
}
void c_union(int a, int b){
	a=find(a), b=find(b);
	parent[b]=a;
}