#include <bits/stdc++.h>
using namespace std;
const int mod = 10007;

long long power(long long a, long long b){
    a %= mod; if (a < 0) a += mod;
    long long ans = 1 % mod;
    while(b){
        if(b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

int main(){
    int a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;

    int maxN = k;                          // 表开到 k
    vector<int> fac(maxN + 1, 1), inv(maxN + 1, 1); // inv = invfac

    for(int i = 1; i <= maxN; i++){
        fac[i] = (int)(1LL * fac[i-1] * i % mod);
    }
    inv[maxN] = (int)power(fac[maxN], mod - 2);      // 注意：是 fac[maxN] 的逆
    for(int i = maxN - 1; i >= 0; i--){
        inv[i] = (int)(1LL * inv[i + 1] * (i + 1) % mod); // 变回 invfac[i]
    }

    long long C = 1LL * fac[k] * inv[n] % mod * inv[k - n] % mod;
    long long ans = C * power(a, n) % mod * power(b, m) % mod;
    cout << (int)(ans % mod) << '\n';
}
