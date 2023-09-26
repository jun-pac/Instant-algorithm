// Sprague-grundy Theorem
// 조건 [순차게임, 완전정보게임, 일반게임, 두 명의 참가자, 유한한 게임] 
// 게임의 상태의 grundy수를 정의할 수 있음. 
// Grundy number is 0 in terminal state.
// Grundy Number of State A = mex{A에서 이동할 수 있는 상태의 Grundy수}
// 0이면 패배하는 초기조건, 1이면 승리하는 초기조건

// 게임 여러 개가 동시에 진행될 때는 각 게임의 Grundy 수의 XOR값이 Grundy 수


#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin>>n;
    int x, res=0;
    for(int i=0; i<n; i++){
        cin>>x;
        res=res^x;
    }
    cout<<(res!=0?"koosaga":"cubelover")<<'\n';
    return 0;
}