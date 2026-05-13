// HDU 5755（模3高斯-约旦，自己+2、四邻+1；目标清零）
// 输入：T；每组 n m，然后 n 行棋盘值(0/1/2)
// 输出：最少按钮次数和每次按的位置(行 列)，若多解取自由变量=0的那组
#include <iostream>
#include<vector>
using namespace std;
// https://acm.hdu.edu.cn/showproblem.php?pid=5755
vector<int> inv;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int mod(int x) { x %= 3; if (x < 0) x += 3; return x; }

// ====== 模3 高斯-约旦，保留你的函数签名 ======
void guess(vector<int>& where, vector<vector<int>>& gaosi) {
    int n = (int)gaosi.size() - 1;        // 行数：1..nm
    int m = (int)gaosi[0].size() - 1;     // 列数：1..(nm+1) 最后一列是 b

    int row = 1;
    for (int col = 1; col <= n && row <= n; col++) {
        int mx = -1;
        for (int i = row; i <= n; i++) {
            if (gaosi[i][col] % 3 != 0) { mx = i; break; }
        }
        if (mx == -1) continue;

        // FIX: 真的把主元行换上来
        if (mx != row) swap(gaosi[mx], gaosi[row]);

        where[col] = row;

        // FIX: 归一化（主元变 1），不要再用 gcd 整倍数，会把主元行放大毁掉
        int invp = inv[mod(gaosi[row][col])]; // inv[1]=1, inv[2]=2
        for (int j = col; j <= m; j++) gaosi[row][j] = mod(1LL * gaosi[row][j] * invp);

        // FIX: 消去其它行的该列，注意不要改动 pivotRow 的值（我们只读它）
        for (int i = 1; i <= n; i++) {
            if (i == row) continue;
            int factor = gaosi[i][col];
            if (factor == 0) continue;
            for (int j = col; j <= m; j++) {
                gaosi[i][j] = mod(gaosi[i][j] - 1LL * factor * gaosi[row][j]);
            }
        }
        row++;
    }
}

// 你的 DFS 基本可用，只是注意列数（最后一列是 b）
bool dfs(int i, int sum, vector<int>& op, int limit,
    vector<int>& where, vector<vector<int>>& gaosi) {
    if (sum > limit) return false;
    if (i == 0) return true;

    if (where[i] == 0) { // 自由变量，取 0/1/2 三种尝试（你原来就是这样）
        op[i] = 0;
        if (dfs(i - 1, sum, op, limit, where, gaosi)) return true;
        op[i] = 1;
        if (dfs(i - 1, sum + 1, op, limit, where, gaosi)) return true;
        op[i] = 2;
        return dfs(i - 1, sum + 2, op, limit, where, gaosi);
    }
    else {
        int ncol = (int)gaosi[0].size();      // = nm+2
        int last = ncol - 1;                  // 最后一列是 b
        int cnt = gaosi[where[i]][last];
        for (int j = i + 1; j < last; j++) {  // j 遍历到 nm 列（不含 b）
            if (gaosi[where[i]][j] != 0) cnt = mod(cnt - gaosi[where[i]][j] * op[j]);
        }
        // FIX: 主元已经被归一为 1，直接取 rhs；若没完全归一，可再乘 inv
        // op[i] = mod(1LL * cnt * inv[mod(gaosi[where[i]][i])]);
        op[i] = mod(cnt);
        return dfs(i - 1, sum + op[i], op, limit, where, gaosi);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    // FIX: inv 只需要 0..2；2 的逆元是 2（2*2=4≡1 mod3）
    inv.assign(3, 0);
    inv[1] = 1; inv[2] = 2;

    while (t--) {
        int n, m;
        cin >> n >> m;
        int nm = n * m;

        // 读入棋盘（样例是给初始盘面，目标清零）
        vector<vector<int>> grid(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> grid[i][j];

        // FIX: 增广矩阵：列要有 nm+1（最后一列是 b），所以开 nm+2（1-based + 末尾）
        vector<vector<int>> gaosi(nm + 1, vector<int>(nm + 2, 0));

        auto id = [&](int r, int c) { return (r - 1) * m + c; }; // 1-based

        // FIX: 正确邻接 & 右端 b = (3 - grid%3)
        for (int r = 1; r <= n; r++) {
            for (int c = 1; c <= m; c++) {
                int k = id(r, c);
                gaosi[k][k] = mod(gaosi[k][k] + 2);            // 自身 +2
                if (r + 1 <= n) gaosi[k][id(r + 1, c)] = mod(gaosi[k][id(r + 1, c)] + 1);
                if (r - 1 >= 1) gaosi[k][id(r - 1, c)] = mod(gaosi[k][id(r - 1, c)] + 1);
                if (c + 1 <= m) gaosi[k][id(r, c + 1)] = mod(gaosi[k][id(r, c + 1)] + 1);
                if (c - 1 >= 1) gaosi[k][id(r, c - 1)] = mod(gaosi[k][id(r, c - 1)] + 1);
                gaosi[k][nm + 1] = mod(3 - mod(grid[r][c]));   // 右端 b
            }
        }

        vector<int> where(nm + 1, 0);
        guess(where, gaosi);

        // 可选：检测矛盾（全 0 系数但 b 非 0）——题面通常保证有解
        for (int i = 1; i <= nm; i++) {
            bool all0 = true;
            for (int j = 1; j <= nm; j++) if (gaosi[i][j] != 0) { all0 = false; break; }
            if (all0 && gaosi[i][nm + 1] != 0) {
                cout << 0 << '\n'; // 无解兜底
                goto NEXT_CASE;
            }
        }

        {
            vector<int> op(nm + 1, 0);
            // 你原 dfs 允许自由变量 0/1/2 枚举，这里 limit 放宽一点
            dfs(nm, 0, op, 2 * nm, where, gaosi);

            int ans = 0;
            for (int i = 1; i <= nm; i++) ans += op[i];
            cout << ans << '\n';
            for (int i = 1; i <= nm; i++) {
                for (int j = 0; j < op[i]; j++) {
                    // FIX: 列号要用 (i-1)%m+1，不能用 i%m+1
                    cout << (i - 1) / m + 1 << " " << (i - 1) % m + 1 << '\n';
                }
            }
        }

    NEXT_CASE:
        continue;
    }
    return 0;
}
