#include <bits/stdc++.h>
using namespace std;

static pair<long long,long long> compress_cycle(const string &s) {
    long long mul = 1; // 分母：2^K
    long long add = 0; // 偏移：按顺序累计（已在当前 mul 尺度上）
    for (char c : s) {
        if (c == 'A') add += mul; // x := x - 1 等价于 add += mul
        else          mul <<= 1;  // x := floor(x/2) 等价于分母 * 2
    }
    return {mul, add};
}

static inline long long apply_one(long long x, char c) {
    if (x == 0) return 0;
    return (c == 'A') ? (x - 1) : (x >> 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, q;
        string s;
        cin >> n >> q >> s;

        auto [mul, add] = compress_cycle(s);

        while (q--) {
            long long x; 
            cin >> x;
            long long steps = 0;
            int idx = 0; 

         
            while (x > 0) {
                long long after;
                if (x > add) after = (x - add) / mul;
                else         after = 0;
                if (after > 0) {
                    x = after;
                    steps += n;  
                } else break;    
            }

           
            while (x > 0) {
                x = apply_one(x, s[idx]);
                idx++; if (idx == n) idx = 0;
                steps++;
            }

            cout << steps << '\n';
        }
    }
    return 0;
}

