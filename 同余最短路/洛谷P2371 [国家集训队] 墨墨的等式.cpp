#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; long long l, r;
    cin >> n >> l >> r;
    int mn; cin >> mn;
    const long long INF = (1LL<<62);
    vector<long long> dist(mn, INF);
    dist[0] = 0;
    for (int idx = 1; idx < n; idx++) {
        long long x; cin >> x;
        int v = (int)(x % mn);
        if (v == 0) continue;
        int g = std::gcd(mn, v);
        for (int s = 0; s < g; s++) {
            int t = s, laps = 0;
            do {
                int p = t + v; if (p >= mn) p -= mn;
                if (dist[t] != INF && dist[t] + x < dist[p]) dist[p] = dist[t] + x;
                t = p;
                if (t == s) ++laps;
            } while (laps < 2);
        }
    }
    auto count_up_to = [&](long long R)->long long {
        if (R < 0) return 0LL;
        long long res = 0;
        for (int i = 0; i < mn; i++) {
            if (dist[i] <= R) res += (R - dist[i]) / mn + 1;
        }
        return res;
    };
    cout << (count_up_to(r) - count_up_to(l - 1)) << '\n';
    return 0;
}

