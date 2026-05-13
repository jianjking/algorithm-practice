#include<iostream>
#include<vector>
using namespace std;

// 记录每一列的主元所在行：where[col] = row (无主元则 0)
void guess(vector<vector<int>>& a, vector<int>& where) {
    int R = (int)a.size() - 1;     // 变量个数/有效行
    int C = (int)a[0].size() - 1;  // RHS 列 = R+1
    where.assign(R + 1, 0);
    int row = 1;
    for (int col = 1; col <= R && row <= R; ++col) {
        int sel = -1;
        for (int r = row; r <= R; ++r) if (a[r][col]) { sel = r; break; }
        if (sel == -1) continue;
        if (sel != row) swap(a[sel], a[row]);
        where[col] = row;

        // 约旦消元：该列其余行清零；覆盖到 RHS
        for (int i = 1; i <= R; ++i) {
            if (i == row || a[i][col] == 0) continue;
            for (int j = col; j <= C; ++j) a[i][j] ^= a[row][j];
        }
        ++row;
    }
}

// 按列从大到小回代；有主元用 where[i] 那一行; 无主元(自由变量)枚举 0/1
void dfs(int i, int sum, int& ans, vector<int>& x,
    const vector<vector<int>>& a, const vector<int>& where) {
    if (sum >= ans) return;
    if (i == 0) { ans = sum; return; }

    int R = (int)x.size() - 1;
    int RHS = (int)a[0].size() - 1;

    int r = where[i];
    if (r == 0) {
        // 自由变量：先试 0（更利于剪枝），再试 1
        x[i] = 0; dfs(i - 1, sum, ans, x, a, where);
        x[i] = 1; dfs(i - 1, sum + 1, ans, x, a, where);
    }
    else {
        int v = a[r][RHS];
        for (int j = i + 1; j <= R; ++j) if (a[r][j]) v ^= x[j];
        x[i] = v;
        dfs(i - 1, sum + v, ans, x, a, where);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // 1..n 是变量列，n+1 是 RHS
    vector<vector<int>> a(n + 1, vector<int>(n + 2, 0));
    for (int i = 1; i <= n; ++i) {
        a[i][i] = 1;   // 自身开关影响自己
        a[i][n + 1] = 1;   // 目标是灯 i 变为 1（全亮）
    }
    for (int k = 0; k < m; ++k) {
        int u, v; cin >> u >> v;
        a[u][v] ^= 1;    // 无向边：彼此影响
        a[v][u] ^= 1;
    }

    vector<int> where;
    guess(a, where);

    // 唯一解判定：每一列都有主元
    bool full = true;
    for (int i = 1; i <= n; ++i) if (where[i] == 0) { full = false; break; }

    if (full) {
        // 直接回代出唯一解并计数
        vector<int> x(n + 1, 0);
        int RHS = n + 1, cnt = 0;
        for (int i = n; i >= 1; --i) {
            int r = where[i];
            int v = a[r][RHS];
            for (int j = i + 1; j <= n; ++j) if (a[r][j]) v ^= x[j];
            x[i] = v; cnt += v;
        }
        cout << cnt << '\n';
        return 0;
    }

    // 否则存在自由变量：DFS 枚举取最少 1 个数
    int ans = n;
    vector<int> x(n + 1, 0);
    dfs(n, 0, ans, x, a, where);
    cout << ans << '\n';
    return 0;
}
