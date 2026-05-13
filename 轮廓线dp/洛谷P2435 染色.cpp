#include<iostream>
#include<vector>
using namespace std;

const int mod = 376544743;

// 在状态 s 的第 j 个“2 位槽”里写入 v（v ∈ [0, k)），先清零再置值
inline int setState(int s, int j, int v) {
    return (s & ~(3 << (2 * j))) | (v << (2 * j));
}

// 取状态 s 的第 j 个“2 位槽”
inline int getState(int s, int j) {
    return (s >> (2 * j)) & 3;
}

// 判断两行状态在同列不能相同（垂直不同）
inline bool differentState(int a, int b, int m) {
    for (int j = 0; j < m; j++) {
        if (getState(a, j) == getState(b, j)) return false;
    }
    return true;
}

int main() {
    int n, m, k;
    if (scanf("%d %d %d", &n, &m, &k) != 3) return 0;
    int S = 1 << (2 * m);
    int start = 0, endState = 0;
    for (int i = 0, v; i < m; i++) {
        scanf("%d", &v);
        start = setState(start, i, v);
    }
    for (int i = 0, v; i < m; i++) {
        scanf("%d", &v);
        endState = setState(endState, i, v);
    }
    if (k == 2) {
        int ans = (n % 2 ? (start == endState) : differentState(start, endState, m));
        printf("%d\n", ans);
        return 0;
    }
    // 预生成所有合法行状态：行内部无相邻相同且颜色 < k
    vector<int> rowStates;
    rowStates.reserve(S);
    for (int s = 0; s < S; s++) {
        bool ok = true;
        int prev = getState(s, 0);
        if (prev >= k) continue;
        for (int j = 1; j < m; j++) {
            int cur = getState(s, j);
            if (cur >= k || cur == prev) { ok = false; break; }
            prev = cur;
        }
        if (ok) rowStates.push_back(s);
    }
    int R = rowStates.size();
    // 构建状态到索引映射
    vector<int> idx(S, -1);
    for (int i = 0; i < R; i++) idx[rowStates[i]] = i;
    int idxStart = idx[start];
    int idxEnd = idx[endState];
    // 预计算行间可转移性
    vector<vector<int>> can(R);
    for (int i = 0; i < R; i++) {
        int s1 = rowStates[i];
        for (int j = 0; j < R; j++) {
            int s2 = rowStates[j];
            bool ok = true;
            // 直接比较列
            for (int c = 0; c < m; c++) {
                if (((s1 >> (2 * c)) & 3) == ((s2 >> (2 * c)) & 3)) { ok = false; break; }
            }
            if (ok) can[i].push_back(j);
        }
    }
    // dp 压缩：仅保留上一行和当前行
    vector<int> dpPrev(R, 0), dpCur(R);
    dpPrev[idxStart] = 1;
    for (int i = 1; i < n; i++) {
        fill(dpCur.begin(), dpCur.end(), 0);
        for (int u = 0; u < R; u++) {
            int val = dpPrev[u];
            if (!val) continue;
            for (int v : can[u]) {
                dpCur[v] = (dpCur[v] + val);
                if (dpCur[v] >= mod) dpCur[v] -= mod;
            }
        }
        dpPrev.swap(dpCur);
    }
    printf("%d\n", dpPrev[idxEnd]);
    return 0;
}
