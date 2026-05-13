#include<bits/stdc++.h>
using namespace std;
const int mod=100000007;
vector<int>fac;
vector<int>inv;
int c(int a,int b){
    return ((1LL*fac[a]*inv[b])%mod*1LL*inv[a-b])%mod;
}
int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*1LL*a)%mod;
        }
        a=(1LL*a*a)%mod;
        b>>=1;
    }
    return ans;
}
int main(){
     int n;
     cin>>n;
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac.assign(2*n+1,1);
    inv.assign(2*n+1,1);
    for(int i=2;i<=2*n;i++)
    fac[i]=(1LL*fac[i-1]*i)%mod;
    inv[2*n]=power(fac[2*n],mod-2);
    for(int i=2*n-1;i>=0;i--){
        inv[i]=(1LL*inv[i+1]*(i+1))%mod;
    }
    int ans=(c(2*n,n)-c(2*n,n-1))%mod;
    if(ans<0)ans+=mod;
    cout<<ans<<'\n';
}