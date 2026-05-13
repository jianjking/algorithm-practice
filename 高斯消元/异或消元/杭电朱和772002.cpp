//https://acm.hdu.edu.cn/showproblem.php?pid=5833
#include<iostream>
#include<vector>
using namespace std;
const int mod = 1000000007;

int power(int a, int e) {
    long long r = 1, x = a % mod;
    while (e) {
        if (e & 1) r = (r * x) % mod;
        x = (x * x) % mod;
        e >>= 1;
    }
    return (int)r;
}

// 行=质因子(1..n)，列=数字(1..m)，GF(2)求秩
int guess(vector<vector<int>>& A) {
    int n = (int)A.size() - 1;   // 因为用了1-based
    int m = (int)A[0].size() - 1;
    int row = 1;
    for (int col = 1; col <= m && row <= n; ++col) {
        int sel = 0;
        for (int r = row; r <= n; ++r) {
            if (A[r][col]) { sel = r; break; }
        }
        if (!sel) continue;
        if (sel != row) swap(A[sel], A[row]);

        // 消掉其他行
        for (int r = 1; r <= n; ++r) {
            if (r == row || !A[r][col]) continue;
            for (int c = col; c <= m; ++c) {
                A[r][c] ^= A[row][c];
            }
        }
        ++row;
    }
    return row - 1; // rank
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 筛出 <=2000 的素数
    vector<int> primes;
    vector<bool> vis(2001, false);
    for (int i = 2; i <= 2000; ++i) {
        if (!vis[i]) {
            primes.push_back(i);
            for (int j = i; j <= 2000; j += i) vis[j] = true;
        }
    }
    int P = (int)primes.size(); // <= 303

    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        cout << "Case #" << tc << ":\n";
        int m;
        cin >> m;

        // A: (P x m) 的0/1矩阵，1-based 省事
        vector<vector<int>> A(P + 1, vector<int>(m + 1, 0));

        for (int j = 1; j <= m; ++j) {
            long long x;            // 关键：要用 long long
            cin >> x;
            for (int i = 1; i <= P; ++i) {
                int p = primes[i - 1];
                if (1LL * p * p > x && x > 1) {
                    // 由于题目保证所有质因子<=2000，执行到这里时 x 要么==1，要么是<=2000的质数。
                    // 如果 x>1 并且 p*p>x，则 x 本身就是一个质数 <=2000，
                    // 但它不一定在 primes[i..] 范围内；稳妥做法是继续常规判断。
                }
                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    cnt ^= 1;      // 只关心奇偶
                }
                A[i][j] = cnt;
                if (x == 1) {
                    // 已经分解完，后面的质数都不会再出现
                    // 但为了简单可读，这里不提前 break 也行；要省点常数可以 break。
                }
            }
            // 题目保证所有质因子 ≤ 2000，因此这里必然分解到 x==1
        }

        int rk = guess(A);
        int freeVars = m - rk;
        int ans = power(2, freeVars);
        cout << (ans + mod - 1) % mod << "\n";
    }
    return 0;
}
