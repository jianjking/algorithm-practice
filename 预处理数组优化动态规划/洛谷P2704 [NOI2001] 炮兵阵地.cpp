#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// 生成一行的合法状态：横向必须间隔 >= 3
void dfs1(int i, int m, int s, vector<int>& states) {
    if (i >= m) { states.push_back(s); return; }
    // 放在 i，则下一格能放的位置是 i+3
    dfs1(i + 3, m, s | (1 << i), states);
    // 不放则考察 i+1
    dfs1(i + 1, m, s, states);
}

int dfs2(int i, int lastIdx, int lastlastIdx,
    const vector<int>& states,
    const vector<int>& rowMask,
    const vector<int>& popc,
    const vector<vector<int>>& okIdx,          // 每行可用状态索引列表
    const vector<vector<char>>& compat,        // 两状态是否按列无冲突
    vector<vector<vector<int>>>& dp, int n)
{
    if (i == n) return 0;
    int& res = dp[i][lastIdx][lastlastIdx];
    if (res != -1) return res;
    res = 0;
    for (int sIdx : okIdx[i]) {
        if (!compat[sIdx][lastIdx])     continue; // 与上一行同列冲突
        if (!compat[sIdx][lastlastIdx]) continue; // 与上上行同列冲突
        res = max(res, popc[sIdx] + dfs2(i + 1, sIdx, lastIdx, states, rowMask, popc, okIdx, compat, dp, n));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // 读图：P 可放置，H 不可放
    vector<int> rowMask(n, 0);
    for (int i = 0; i < n; i++) {
        string row; cin >> row;
        for (int j = 0; j < m; j++) {
            if (row[j] == 'P') rowMask[i] |= (1 << j);
        }
    }

    // 生成一行的所有“横向合法”的状态
    vector<int> states;
    dfs1(0, m, 0, states);
    // 去重（理论上 dfs1 不会重复，但稳妥起见）
    sort(states.begin(), states.end());
    states.erase(unique(states.begin(), states.end()), states.end());
    int K = (int)states.size();

    // 预处理 bitcount
    vector<int> popc(K, 0);
    for (int i = 0; i < K; i++) popc[i] = __builtin_popcount((unsigned)states[i]);

    // 预处理两状态是否兼容（同列不重合）
    vector<vector<char>> compat(K, vector<char>(K, 0));
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            compat[i][j] = ((states[i] & states[j]) == 0);
        }
    }

    // 预处理每行可用状态索引：状态必须是 rowMask 的子集
    vector<vector<int>> okIdx(n);
    for (int i = 0; i < n; i++) {
        int mask = rowMask[i];
        for (int sIdx = 0; sIdx < K; sIdx++) {
            if ((states[sIdx] & ~mask) == 0) okIdx[i].push_back(sIdx);
        }
    }

    // 加一个“空状态”索引，方便初始 last / lastlast
    // 方法：把空状态 0 的下标找出来
    int zeroIdx = int(lower_bound(states.begin(), states.end(), 0) - states.begin());
    // 记忆化 dp[i][last][lastlast]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(K, vector<int>(K, -1)));

    int ans = dfs2(0, zeroIdx, zeroIdx, states, rowMask, popc, okIdx, compat, dp, n);
    cout << ans << "\n";
    return 0;
}
