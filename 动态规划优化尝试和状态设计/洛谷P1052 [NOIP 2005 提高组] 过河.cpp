#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;           // 独木桥长度
    int s, t, m;    // 跳跃区间 [s, t]，石子数 m
    cin >> n >> s >> t >> m;

    vector<ll> arr(m);
    for (int i = 0; i < m; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());

    // 特判：跳距固定
    if (s == t) {
        int cnt = 0;
        for (ll x : arr) {
            if (x % s == 0) cnt++;
        }
        cout << cnt << "\n";
        return 0;
    }

    // 否则 s < t，做“路径压缩”
    int safe = t;  // 安全距离 = 最大跳距 t

    // prevOrig：上一个石子的原始坐标； last：压缩后坐标
    ll prevOrig = 0, last = 0;
    vector<int> newPos;
    newPos.reserve(m);
    for (ll x : arr) {
        ll gap = x - prevOrig;
        last += min(gap, (ll)safe);
        prevOrig = x;
        newPos.push_back((int)last);
    }

    // 压缩后最远可能位置
    int M = newPos.empty() ? 0 : newPos.back();
    int N = M + safe;

    // stone[i] = true 表示压缩后坐标 i 有石子
    vector<char> stone(N + 1, 0);
    for (int p : newPos) stone[p] = 1;

    // DP: dp[i] = 到达 i 时踩过的最少石子数
    const int INF = INT_MAX / 2;
    vector<int> dp(N + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= N; i++) {
        int L = max(0, i - t);
        int R = i - s;
        if (R < 0) continue;
        int best = INF;
        for (int j = L; j <= R; j++) {
            best = min(best, dp[j]);
        }
        dp[i] = best + (stone[i] ? 1 : 0);
    }

    // 只要一跳出最后一颗石子就到对岸
    int ans = INF;
    for (int i = M + 1; i <= N; i++) {
        ans = min(ans, dp[i]);
    }

    cout << ans << "\n";
    return 0;
}
