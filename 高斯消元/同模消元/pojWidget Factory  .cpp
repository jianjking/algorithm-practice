// http://poj.org/problem?id=2947
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

int row = 1;

int mod(int x) {
    x %= 7;
    if (x < 0) x += 7;
    return x;
}

vector<int> lnv;

// 仅修正你现有逻辑：找主元判空、归一化、按列消元（别再只改一列）、记录 where
void guess(vector<int>& where, vector<vector<int>>& gaosi) {
    int R = (int)gaosi.size();     // 行：m + 1（我们用 1..m）
    int C = (int)gaosi[0].size();  // 列：n + 2（1..n 变量，n+1 常数）
    row = 1;
    for (int col = 1; row < R && col < C - 1; col++) { // 只扫到第 n 列
        int mx = -1;
        for (int r = row; r < R; r++) {
            if (gaosi[r][col] != 0) { mx = r; break; }
        }
        // 可能整列为 0：跳过
        if (mx == -1) continue;

        if (mx != row) swap(gaosi[mx], gaosi[row]);

        // 归一化主元（模 7 的逆元）
        int inv = lnv[gaosi[row][col]];
        for (int j = col; j < C; j++) {
            gaosi[row][j] = mod(1LL * gaosi[row][j] * inv);
        }

        // 用当前列把其它行消为 0（高斯-约旦）
        for (int i = 1; i < R; i++) {
            if (i == row || gaosi[i][col] == 0) continue;
            int factor = gaosi[i][col];
            for (int j = col; j < C; j++) {
                gaosi[i][j] = mod(gaosi[i][j] - 1LL * factor * gaosi[row][j]);
            }
        }
        where[col] = row++;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    unordered_map<string, int> day;
    day["MON"] = 1; day["TUE"] = 2; day["WED"] = 3; day["THU"] = 4;
    day["FRI"] = 5; day["SAT"] = 6; day["SUN"] = 7;

    // 预处理模 7 逆元（1..6），模 7 是质数，OK
    lnv.assign(7, 0);
    lnv[1] = 1;
    for (int i = 2; i < 7; i++) {
        lnv[i] = (7 - 1LL * lnv[7 % i] * (7 / i) % 7) % 7;
    }

    while (true) {
        int n, m;
        if (!(cin >> n >> m)) return 0;
        if (n == 0 && m == 0) break;

        // gaosi[1..m][1..n] 系数，gaosi[*][n+1] 常数项
        vector<vector<int>> gaosi(m + 1, vector<int>(n + 2, 0));

        for (int i = 1; i <= m; i++) {
            int k; string s1, s2;
            cin >> k >> s1 >> s2;
            int L = day[s1], R = day[s2];
            gaosi[i][n + 1] = mod(R - L + 1); // 包含首尾天数

            for (int j = 0; j < k; j++) {
                int t; cin >> t;              // 1..n
                gaosi[i][t] = (gaosi[i][t] + 1) % 7;
            }
        }

        vector<int> where(n + 1, 0);
        guess(where, gaosi);

        // 检查是否无解：存在“系数全 0 但常数不为 0”的行
        bool inconsistent = false;
        for (int i = 1; i <= m && !inconsistent; i++) {
            bool all0 = true;
            for (int j = 1; j <= n; j++) {
                if (gaosi[i][j] != 0) { all0 = false; break; }
            }
            if (all0 && gaosi[i][n + 1] != 0) inconsistent = true;
        }
        if (inconsistent) {
            cout << "Inconsistent data." << '\n';
            continue;
        }

        // 检查是否多解：存在自由变量（没有主元）
        bool multiple = false;
        for (int j = 1; j <= n; j++) {
            if (where[j] == 0) { multiple = true; break; }
        }
        if (multiple) {
            cout << "Multiple solutions." << '\n';
            continue;
        }

        // 唯一解：读取每个主元行的常数项（0..6），映射到 3..9
        for (int j = 1; j <= n; j++) {
            int v = gaosi[where[j]][n + 1]; // 0..6
            if (v < 3) v += 7;              // 0→7, 1→8, 2→9
            cout << v << (j == n ? '\n' : ' ');
        }
    }
    return 0;
}
