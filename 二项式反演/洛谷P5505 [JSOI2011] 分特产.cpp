#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int power(int a,int b){
    long long ans=1, base=a%mod;
    while(b){
        if(b&1) ans=ans*base%mod;
        base=base*base%mod;
        b>>=1;
    }
    return (int)ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin>>n>>m;
    vector<int> nums(m,0);
    int mx=0;
    for(int i=0;i<m;i++){
        cin>>nums[i];
        mx=max(mx,nums[i]);
    }

    int n1=n+mx+5;                      // 留余量更稳
    vector<int> fac(n1,1);
    for(int i=1;i<n1;i++){             // ★ 用 1LL 防溢出
        fac[i]=(long long)fac[i-1]*i%mod;
    }
    vector<int> inv(n1,1);             // inv = 逆阶乘
    inv[n1-1]=power(fac[n1-1],mod-2);
    for(int i=n1-2;i>=0;i--){          // ★ 回推到 0
        inv[i]=(long long)inv[i+1]*(i+1)%mod;
    }

    vector<int> g(n+1,0);
    for(int i=0;i<n;i++){              // i<n，避免 rem-1 = -1
        // g[i] = C(n,i)
        long long cur = (long long)fac[n]*inv[i]%mod*inv[n-i]%mod;
        // 乘上 ∏ C(n + nums[j] - i - 1, n - 1 - i)
        for(int j=0;j<m;j++){
            cur = cur * fac[n + nums[j] - i - 1] % mod;   // ★ 每步都 64 位
            cur = cur * inv[n - 1 - i] % mod;
            cur = cur * inv[nums[j]] % mod;
        }
        g[i] = (int)cur;
    }
    g[n]=0;                            // rem=0 的项：除非全 0，否则为 0

    long long ans=0;                   // ★ ans 用 long long
    for(int i=0;i<=n;i++){
        if(i&1) ans = (ans - g[i] + mod) % mod;   // (-1)^i 累加
        else     ans = (ans + g[i]) % mod;
    }
    cout<<ans<<'\n';
    return 0;
}
