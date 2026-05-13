#include <bits/stdc++.h>
using namespace std;

// ---------- BigInt (base = 1e9) 仅支持乘以 int 和输出 ----------
struct BigInt {
    static const uint32_t BASE = 1000000000;
    vector<uint32_t> a; // 低位在前

    BigInt(long long v = 0) { *this = v; }
    BigInt& operator=(long long v){
        a.clear();
        if(v == 0) return *this;
        while(v){
            a.push_back(v % BASE);
            v /= BASE;
        }
        return *this;
    }
    bool isZero() const { return a.empty(); }

    void mul_uint(uint64_t m){
        if(m == 0 || isZero()){ a.clear(); return; }
        uint64_t carry = 0;
        for(size_t i = 0; i < a.size(); ++i){
            __uint128_t cur = (__uint128_t)a[i] * m + carry;
            a[i] = (uint32_t)(cur % BASE);
            carry = (uint64_t)(cur / BASE);
        }
        while(carry){
            a.push_back((uint32_t)(carry % BASE));
            carry /= BASE;
        }
    }
};

ostream& operator<<(ostream& os, const BigInt& x){
    if(x.a.empty()) return os << 0;
    int n = (int)x.a.size();
    os << x.a.back();
    for(int i = n - 2; i >= 0; --i){
        os << setw(9) << setfill('0') << x.a[i];
    }
    return os;
}

// ---------- 质数筛 ----------
static vector<int> sieve(int n){
    vector<int> primes;
    vector<bool> st(n + 1, false);
    for(int i = 2; i <= n; ++i){
        if(!st[i]) primes.push_back(i);
        for(long long p : primes){
            long long x = 1LL * i * p;
            if(x > n) break;
            st[(int)x] = true;
            if(i % p == 0) break;
        }
    }
    return primes;
}

// v_p(n!) = sum floor(n/p^k)
static long long vp_fact(long long n, long long p){
    long long s = 0;
    while(n){
        n /= p;
        s += n;
    }
    return s;
}

// ---------- 主程序：用质因数指数法计算 Catalan(n) ----------
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    if(n == 0 || n == 1){
        cout << 1 << "\n";
        return 0;
    }

    // Catalan(n) = (2n)! / (n! * (n+1)!)
    // => 指数 e_p = v_p((2n)!) - v_p(n!) - v_p((n+1)!)
    int lim = 2 * n;
    vector<int> primes = sieve(lim);

    BigInt ans(1);
    for(int p : primes){
        long long e = vp_fact(2LL * n, p) - vp_fact(n, p) - vp_fact(n + 1LL, p);
        while(e-- > 0){
            ans.mul_uint(p);
        }
    }

    cout << ans << "\n";
    return 0;
}
