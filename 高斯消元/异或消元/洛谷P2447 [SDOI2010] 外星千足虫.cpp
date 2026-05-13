#include <iostream>
#include<vector>
using namespace std;

static inline int getbit(const vector<unsigned long long>& row, int idx) {
    int blk = idx >> 6, off = idx & 63;
    return (row[blk] >> off) & 1ULL;
}
static inline void setbit(vector<unsigned long long>& row, int idx) {
    int blk = idx >> 6, off = idx & 63;
    row[blk] |= (1ULL << off);
}

// 高斯-约旦（GF(2)、按64位块）
// a: m 行、每行 W 个 uint64 块；列是 0..n（n 为 RHS）共 n+1 列
// where[c] = 该列主元所在行号（无主元则 -1）
// id[r] = 这一行对应的原始记录编号（用于算最小前缀k）
// need = 前缀 k（函数内更新）
// 返回：是否满秩（即 rank == n）
bool guess(vector<vector<unsigned long long>>& a,
    vector<int>& where, vector<int>& id,
    int m, int n, int W, int& need)
{
    fill(where.begin(), where.end(), -1);
    int row = 0;
    need = 0;
    for (int col = 0; col < n && row < m; ++col) {
        int blk = col >> 6, off = col & 63;

        // 1) 选主元：在 [row..m-1] 找该列为1的行
        int sel = -1;
        for (int r = row; r < m; ++r) {
            if (((a[r][blk] >> off) & 1ULL) != 0ULL) { sel = r; break; }
        }
        if (sel == -1) continue;  // 本列无主元，跳过（可能无唯一解）

        // 2) 交换到当前行（同步 id）
        if (sel != row) {
            swap(a[sel], a[row]);
            swap(id[sel], id[row]);
        }
        where[col] = row;
        need = max(need, id[row]); // 用原始记录编号更新最小前缀 k

        // 3) 约旦：把本列其他行清零
        for (int r = 0; r < m; ++r) if (r != row) {
            if (((a[r][blk] >> off) & 1ULL) != 0ULL) {
                for (int j = 0; j < W; ++j) a[r][j] ^= a[row][j];
            }
        }
        ++row;
    }
    // 满秩当且仅当每一列都有主元（或 rank==n）
    // 更稳：统计 where[c] != -1 的列数
    int rank_ = 0;
    for (int c = 0; c < n; ++c) if (where[c] != -1) ++rank_;
    return rank_ == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // n=变量数(虫子数), m=记录数
    if (!(cin >> n >> m)) return 0;

    const int RHS = n;                    // RHS 列索引（0-based）
    const int W = (RHS + 1 + 63) >> 6;    // 需要的 64 位块数

    // 读入 m 条记录为 m 行
    vector<vector<unsigned long long>> nums(m, vector<unsigned long long>(W, 0ULL));
    for (int i = 0; i < m; ++i) {
        string s; int t;
        cin >> s >> t;                    // s 长度 n，t 为 0/1
        for (int j = 0; j < n; ++j) if (s[j] == '1') setbit(nums[i], j);
        if (t & 1) setbit(nums[i], RHS);
    }

    // where[c] 存主元行；id[r] 存该行来自的“原始记录编号 = 行号+1”
    vector<int> where(n, -1), id(m, 0);
    for (int r = 0; r < m; ++r) id[r] = r + 1;

    int need = 0;
    bool full = guess(nums, where, id, m, n, W, need);

    if (!full) {
        cout << "Cannot Determine\n";
        return 0;
    }

    // 解：x[c] = 行 where[c] 的 RHS 位
    vector<int> x(n, 0);
    for (int c = 0; c < n; ++c) {
        int r = where[c];
        x[c] = getbit(nums[r], RHS);
    }

    cout << need << "\n";
    for (int i = 0; i < n; ++i) {
        if (x[i]) cout << "?y7M#\n";   // 奇数腿：外星
        else      cout << "Earth\n";   // 偶数腿：地球
    }
    return 0;
}
