#include<bits/stdc++.h>
using namespace std;
const int mod=1000000;
int main(){
    int n;
    vector<int>ans(1001,1);
    for(int i=2;i<=1000;i++){
        ans[i]=0;
        for(int j=0;j<i;j++){
             ans[i]=(ans[i]+1LL*ans[i-1-j]*ans[j])%mod;
        }
    }
    while(true){
        cin>>n;
        if(n==0){
            break;
        }
        cout<<ans[n]<<'\n';
    }
}