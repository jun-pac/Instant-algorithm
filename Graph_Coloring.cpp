
#include <bits/stdc++.h>
using namespace std;

vector<int> edges[100];
#define INF 100

int chromatic_number(int n){ // n is # of vertices of the graph
    // Minimum number of colors require to satisty "Graph Coloring Problem"
    assert(n<20); // O(3^N) algorithm
    int DP[(1<<n)];
    DP[0]=1; // Convinient in DP process 
    for(int k=0; k<n; k++){
        for(int j=0; j<(1<<k); j++){
            int num=(1<<k)+j, res=INF; // num indicates current subset
            bool indep=0;
            if(DP[j]==1){ // Check independence
                indep=1;
                for(auto next : edges[k]){
                    if(j&(1<<next)){
                        indep=0;
                        break;
                    }
                }
            }
            if(indep) res=1;
            else{
                for(int t=num; t>0; t=(t-1)&num){
                    // t swaps all the subsets of num
                    if(num==t) continue;
                    res=min(res, DP[t]+DP[num-t]);   
                }
            }
            DP[num]=res;
        }
    }
    return DP[(1<<n)-1];
}
