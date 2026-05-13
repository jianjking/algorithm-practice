#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int power(long long a,int b){
    long long ans = 1 % mod; a %= mod;
    while(b){
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return (int)ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,k; 
    cin >> n >> k;

    // g[i] = 2^{2^{n-i}} - 1  （连平方）
    vector<int> g(n+1, 2);
    for(int i = n-1; i >= 0; --i) g[i] = 1LL * g[i+1] * g[i+1] % mod;
    for(int i = 0; i <= n; ++i)   g[i] = (g[i] + mod - 1) % mod;

    // 阶乘与逆阶乘
    vector<int> fac(n+1,1), ifac(n+1,1);
    for(int i=1;i<=n;i++) fac[i] = 1LL * fac[i-1] * i % mod;
    ifac[n] = power(fac[n], mod - 2);
    for(int i=n-1;i>=0;i--) ifac[i] = 1LL * ifac[i+1] * (i+1) % mod;

    auto C = [&](int N,int R)->int{
        if(R<0 || R> N) return 0;
        return 1LL * fac[N] * ifac[R] % mod * ifac[N-R] % mod;
    };

    // 把 C(n,i) 乘进 g[i] —— 一定要分步 %mod
    for(int i=0;i<=n;i++){
        g[i] = 1LL * g[i] * C(n,i) % mod;     // ★ 修复：补全 %mod
    }

    // ans = sum_{i=k}^n (-1)^{i-k} * C(i,k) * g[i]
    long long ans = 0;
    for(int i=k;i<=n;i++){
        long long term = 1LL * C(i,k) * g[i] % mod;   // ★ 分步取模
        if((i - k) & 1) ans = (ans - term + mod) % mod; // 处理负号
        else            ans = (ans + term) % mod;
    }
    cout << ans << '\n';
    return 0;
}