#include <bits/stdc++.h>
// 洛谷P4774 [NOI2018] 屠龙勇士.cpp
// https://www.luogu.com.cn/problem/P4774
using namespace std;
using ll = long long;
__int128 x, y;

__int128 exgcd(__int128 a, __int128 b) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    __int128 d = exgcd(b, a % b);
    __int128 temp = x;
    x = y;
    y = temp - a / b * y;
    return d;
}

long long read_ll() {
    long long n;
    cin >> n;
    return n;
}

void print128(__int128 n) {
    if (n == 0) {
        cout << 0;
        return;
    }
    if (n < 0) {
        cout << '-';
        n = -n;
    }
    string s;
    while (n) {
        s.push_back('0' + n % 10);
        n /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int z = 0; z < t; z++) {
        __int128 limit = 0;
        int n, m;
        cin >> n >> m;
        vector<__int128> a(n), p(n), reward(n);
        for (int j = 0; j < n; j++) {
            long long tmp;
            cin >> tmp;
            a[j] = tmp;
        }
        for (int j = 0; j < n; j++) {
            long long tmp;
            cin >> tmp;
            p[j] = tmp;
        }
        for (int j = 0; j < n; j++) {
            long long tmp;
            cin >> tmp;
            reward[j] = tmp;
        }
        set<__int128, less<__int128>> jian;
        unordered_map<long long, int> cnt;
        for (int i = 0; i < m; i++) {
            long long tmp;
            cin >> tmp;
            jian.insert(tmp);
            cnt[tmp]++;
        }

        __int128 lcm = 1;
        __int128 tail = 0;
        for (int i = 0; i < n; i++) {
            auto it = jian.upper_bound(a[i]);
            if (it != jian.begin()) {
                it--;
            }
            __int128 value = *it;
            cnt[(long long)*it]--;
            if (cnt[(long long)*it] == 0) {
                jian.erase(*it);
            }
            cnt[(long long)reward[i]]++;
            jian.insert(reward[i]);

            __int128 a1 = value * lcm;
            __int128 b1 = p[i];
            __int128 c1 = a[i] - value * tail;

            __int128 g = exgcd(a1, b1);
            limit = max(limit, (a[i] + value - 1) / value);

            if (c1 % g != 0) {
                cout << -1 << '\n';
                goto NEXT_CASE;
            }
            {
                __int128 mod = b1 / g;
                __int128 t_x = x * (c1 / g);
                t_x = (t_x % mod + mod) % mod;
                tail = tail + lcm * t_x;
                lcm = lcm * mod;
                tail = (tail % lcm + lcm) % lcm;
            }
        }

        if (tail > limit) {
            print128(tail);
            cout << '\n';
        } else {
            __int128 need = (limit - tail + lcm - 1) / lcm;
            print128(tail + need * lcm);
            cout << '\n';
        }

        continue;

    NEXT_CASE:
        continue;
    }
}
