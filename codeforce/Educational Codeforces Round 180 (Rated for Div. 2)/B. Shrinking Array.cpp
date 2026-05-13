#include<iostream>
#include<deque>
#include<vector>
#include<unordered_map>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        bool ok0 = false;
        for (int i = 1; i < n; i++) {
            if (llabs(a[i] - a[i - 1]) <= 1) {
                ok0 = true;
                break;
            }
        }
        if (ok0) {
            cout << 0 << '\n';
            continue;
        }

        bool ok1 = false;
        for (int k = 0; k + 1 < n; k++) {
            ll lo = min(a[k], a[k + 1]);
            ll hi = max(a[k], a[k + 1]);
            if (k - 1 >= 0) {
                ll v = a[k - 1];
                ll L = max(lo, v - 1), R = min(hi, v + 1);
                if (L <= R) { ok1 = true; break; }
            }
            if (k + 2 < n) {
                ll v = a[k + 2];
                ll L = max(lo, v - 1), R = min(hi, v + 1);
                if (L <= R) { ok1 = true; break; }
            }
        }
        if (ok1) {
            cout << 1 << '\n';
            continue;
        }
        unordered_map<ll, int> last;
        const int INF = 1e9;
        int ans = INF;
        for (int i = 0; i < n; i++) {
            for (ll v : {a[i], a[i] - 1, a[i] + 1}) {
                auto it = last.find(v);
                if (it != last.end())
                    ans = min(ans, i - it->second - 1);
            }
            last[a[i]] = i;
        }
        cout << (ans == INF ? -1 : ans) << '\n';
    }
    return 0;
}
