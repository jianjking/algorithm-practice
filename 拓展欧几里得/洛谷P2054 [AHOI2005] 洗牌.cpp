#include<iostream>
#include<vector>
using namespace std;
using ll = long long;

// 全局解 ax + by = gcd(a,b)
ll x, y;

// 正确的扩展欧几里得：先递归，再根据子问题回代
void exgcd(ll a, ll b) {
    if (b == 0) {
        x = 1;   // a*1 + b*0 = a
        y = 0;
        return;
    }
    exgcd(b, a % b);      // 先把 (b, a%b) 的 x,y 算出来
    ll tx = x, ty = y;    // 保存子问题的解
    // 推导：若 b*tx + (a%b)*ty = g
    // 且 a%b = a - floor(a/b)*b
    // => a*ty + b*(tx - floor(a/b)*ty) = g
    x = ty;
    y = tx - (a / b) * ty;
}

// 用 __int128 防止乘法溢出
static inline ll mul_mod(ll a, ll b, ll mod) {
    return (ll)((__int128)a * b % mod);
}

ll power(ll a, ll b, ll mod) {
    a %= mod;
    ll ans = 1 % mod;
    while (b) {
        if (b & 1) ans = mul_mod(ans, a, mod); // 防溢出
        a = mul_mod(a, a, mod);                // 防溢出
        b >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, l;
    cin >> n >> m >> l;

    ll MOD = n + 1;                 // 模数 = N+1（N 偶 ⇒ MOD 奇）
    ll twoPow = power(2, m, MOD);   // twoPow = 2^M mod (N+1)

    // 逆元：twoPow * inv ≡ 1 (mod MOD)
    exgcd(twoPow, MOD);
    // 这里的 x 就是逆元（可能为负），因为 gcd(2^M, MOD)=1
    x %= MOD;
    if (x < 0) x += MOD;

    // p ≡ L * (2^M)^{-1} (mod N+1)
    ll ans = mul_mod(l % MOD, x, MOD); // 同样用 128 位防溢出
    cout << ans << '\n';
    return 0;
}
