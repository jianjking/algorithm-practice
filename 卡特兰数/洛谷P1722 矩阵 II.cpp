#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    if(n==1||n==0){
        cout<<1<<'\n';
        return 0;
    }
    vector<int>ans(n+1,1);
    for(int i=2;i<=n;i++){
        ans[i]=0;
        for(int j=0;j<i;j++){
              ans[i]=(ans[i]+ans[j]*ans[i-1-j])%100; 
                   }
    }
    cout<<ans[n]<<'\n';
}