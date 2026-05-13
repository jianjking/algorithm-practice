#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
vector<int>fac;
vector<int>inv;

int power(int a,int b){
    long long ans=1, x=a%mod;
    while(b){
        if(b&1) ans = ans * x % mod;
        x = x * x % mod;
        b >>= 1;
    }
    return (int)ans; // ← 必须返回
}

int c(int a,int b){
    if(b<0 || b>a) return 0; // ← 兜底
    return (int)(1LL*fac[a]*inv[b]%mod*inv[a-b]%mod); // ← 边乘边取模
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin>>n)) return 0;

    fac.assign(2*n+1,1);
    inv.assign(2*n+1,1);

    for(int i=1;i<=2*n;i++){
        fac[i]=(int)(1LL*i*fac[i-1]%mod);
    }
    inv[2*n]=power(fac[2*n],mod-2); // ← 是 (2n)! 的逆，不是 2n 的逆
    for(int i=2*n-1;i>=0;i--){
        inv[i]=(int)(1LL*inv[i+1]*(i+1)%mod); // ← 下滚到 0
    }

    int ans;
    if(n==0) ans=1; // Catalan(0)=1
    else{
        ans = c(2*n,n) - c(2*n,n-1);
        if(ans<0) ans+=mod;
    }
    cout<<ans<<'\n';
}
