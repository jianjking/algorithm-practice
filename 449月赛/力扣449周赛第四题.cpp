
s1 + s2 = sum - s;
#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
vector<vector<int>> rotate90(const vector<vector<int>>& a) {
    int m = a.size();
    int n = a[0].size();
    vector<vector<int>> b(n, vector<int>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            b[j][m - 1 - i] = a[i][j];
        }
    }
    return b;
}

// 在给定矩阵 a（m×n）和总和 total 下，尝试水平切分并删除一个元素使两部分平衡
bool trySplit(const vector<vector<int>>& a, long long total) {
    int m = a.size();
    int n = a[0].size();
    unordered_set<long long> st;
    st.insert(0);  // “不删任何元素”对应差值 0
    long long s = 0;

    // 删除上半部分一个元素
    for (int i = 0; i < m - 1; i++) {
        const auto& row = a[i];
        for (int j = 0; j < n; j++) {
            int x = row[j];
            s += x;
            // 第一行中间元素不能删，其他位置都可以
            if (i > 0 || j == 0 || j == n - 1) {
                st.insert(x);
            }
        }

        // 只有一列时的特殊处理
        if (n == 1) {
            // 情况：不删、删第一行、删当前行
            if (s * 2 == total ||
                s * 2 - total == a[0][0] ||
                s * 2 - total == row[0]) {
                return true;
            }
            continue;
        }

        long long diff = s * 2 - total;
        if (st.count(diff)) {
            return true;
        }
        // 走到第二行开始时，也允许删除第一行的任意元素
        if (i == 0) {
            for (int x : row) {
                st.insert(x);
            }
        }
    }

    // 删除下半部分一个元素：将矩阵上下翻转后再做同样判断
    vector<vector<int>> b = a;
    reverse(b.begin(), b.end());
    st.clear();
    st.insert(0);
    s = 0;
    for (int i = 0; i < m - 1; i++) {
        const auto& row = b[i];
        for (int j = 0; j < n; j++) {
            int x = row[j];
            s += x;
            if (i > 0 || j == 0 || j == n - 1) {
                st.insert(x);
            }
        }
        if (n == 1) {
            if (s * 2 == total ||
                s * 2 - total == b[0][0] ||
                s * 2 - total == row[0]) {
                return true;
            }
            continue;
        }
        long long diff = s * 2 - total;
        if (st.count(diff)) {
            return true;
        }
        if (i == 0) {
            for (int x : row) {
                st.insert(x);
            }
        }
    }

    return false;
}

// 既尝试水平切分，也在旋转后尝试垂直切分
bool canPartitionGridFree(vector<vector<int>>& grid) {
    long long total = 0;
    for (const auto& row : grid)
        for (int x : row)
            total += x;

    // 水平切分
    if (trySplit(grid, total)) return true;
    // 竖直切分：先旋转再水平切
    auto rg = rotate90(grid);
    if (trySplit(rg, total)) return true;

    return false;
}

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        return canPartitionGridFree(grid);
    }
};
