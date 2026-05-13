// 一共有n个盘子k种菜，所有盘子排成一排，每个盘子只能放一种菜
// 要求最多连续两个盘子菜品一样，更长的重复出现是不允许的
#include <vector>
using namespace std;

static const int MOD = 1000000007;
// 通用矩阵类型：行×列
using Matrix = vector<vector<long long>>;

// 矩阵乘法：C = A × B，均按 MOD 取模
Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();          // A 的行数
    int m = B[0].size();       // B 的列数
    int K = A[0].size();       // A 的列数 == B 的行数
    Matrix C(n, vector<long long>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            long long sum = 0;
            for (int t = 0; t < K; ++t) {
                sum += A[i][t] * B[t][j];
                if (sum >= 8LL * MOD * MOD) sum %= MOD; // 减少溢出
            }
            C[i][j] = sum % MOD;
        }
    }
    return C;
}

// 矩阵快速幂：计算 M^p
Matrix power(Matrix M, long long p) {
    int n = M.size();
    Matrix R(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) R[i][i] = 1;  // 单位矩阵
    while (p > 0) {
        if (p & 1) R = multiply(R, M);
        M = multiply(M, M);
        p >>= 1;
    }
    return R;
}

// dp3 的 C++ 实现
// 计算长度为 n、菜品种类为 k 的方案数
int dp3(int n, int k) {
    if (n == 1) return k % MOD;
    int s = (k - 1) % MOD;
    // 起始向量 1×2
    Matrix start = { {1, s} };
    // 转移矩阵 2×2
    Matrix base = { {0, s}, {1, s} };
    // base^(n-2)
    Matrix M = power(base, n - 2);
    // start × M 得到 1×2 矩阵
    Matrix ans = multiply(start, M);
    // 最终再乘回首块的 k
    long long total = (ans[0][0] + ans[0][1]) % MOD;
    return (int)((total * k) % MOD);
}
