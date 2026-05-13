#include<bits/stdc++.h>
using namespace std;
const int mod=20100403; 
vector<int>fac;
vector<int>inv;
int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(1LL*ans*a)%mod;
        }
        a=(1LL*a*a)%mod;
        b>>=1;
    }
    return ans;
}
int c(int a,int b){
    return ((1LL*fac[a]*inv[b])%mod*inv[a-b])%mod;
}
int main(){
    int n,m;
    cin>>n>>m;
    fac.assign(n+m+1,1);
    inv.assign(n+m+1,1);
    for(int i=2;i<=n+m;i++){
        fac[i]=(1LL*fac[i-1]*i)%mod;
    }
    inv[n+m]=power(fac[n+m],mod-2);
    for(int i=n+m-1;i>=0;i--){
        inv[i]=(1LL*(i+1)*inv[i+1])%mod;
    }
    int ans=(c(n+m,n)-c(n+m,m-1))%mod;
    if(ans<0)ans+=mod;
    cout<<ans<<'\n';
}