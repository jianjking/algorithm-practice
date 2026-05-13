#include<iostream>
#include<vector>
#include<iomanip>
#include <numeric>  
#include<algorithm>
using namespace std;

const int MAXN = 502;
const int MAXM = 502;

int n, m;
double sml = 1e-5;

// mat[i][1..m] 为属性；mat[i][m+1] 为价格
double mat[MAXN][MAXM];

// basis[j] = 以第 j 列为主元的那一行的行号（0 表示暂无）
int basis_idx[MAXN];

int cnt_sel = 0;   // 选择的物品数
long long sum_cost = 0;

// 尝试把第 i 行插入当前“行基”（与 Java 的 insert(i) 等价）
bool insert_row(int i) {
    for (int j = 1; j <= m; ++j) {
        if (fabs(mat[i][j]) >= sml) {
            if (basis_idx[j] == 0) {           // 这一列还没有主元，收下
                basis_idx[j] = i;
                return true;
            }
            // 用已有主元行消掉第 i 行的该列
            int b = basis_idx[j];
            double rate = mat[i][j] / mat[b][j];
            for (int k = j; k <= m; ++k) {
                mat[i][k] -= rate * mat[b][k];
            }
        }
    }
    return false; // 被已有基消成相关了
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mat[i][j];

    for (int i = 1; i <= n; ++i) {
        double c; cin >> c;
        mat[i][m + 1] = c;                    // 价格放在第 m+1 列
    }

    // 按价格升序遍历：用索引数组排序即可，不必搬动整行
    vector<int> id(n);
    iota(id.begin(), id.end(), 1);
    sort(id.begin(), id.end(), [&](int a, int b) {
        return mat[a][m + 1] < mat[b][m + 1];
        });

    // 清空基
    memset(basis_idx, 0, sizeof(basis_idx));
    cnt_sel = 0;
    sum_cost = 0;

    for (int idx : id) {
        if (insert_row(idx)) {
            cnt_sel++;
            sum_cost += (long long)mat[idx][m + 1];
            if (cnt_sel == m) break;          // 秩最多 m
        }
    }

    cout << cnt_sel << ' ' << sum_cost << '\n';
    return 0;
}
