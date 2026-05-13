#include<iostream>
#include<vector>
using namespace std;
const int MOD = 1e9 + 7;
class Solution {
public:
    int dfs(vector<vector<vector<int>>>& dp, int i, int n, int pre, int status, int l, int r) {
        if (i == n)return 1;
        int& res = dp[i][pre][status];
        if (res != -1)return res;
        res = 0;
        if (pre == 0) {
            for (int j = l; j <= r; j++) {
                res = (res + dfs(dp, i + 1, n, j, 0, l, r)) % mod;
            }
        }
        else {
            if (status == 0) {
                for (int j = l; j <= r; j++) {
                    if (j == pre)continue;
                    int sign = j < pre ? 1 : 2;
                    res = (res + dfs(dp, i + 1, n, j, sign, l, r)) % mod;
                }
            }
            else if (status == 1) {
                for (int j = pre + 1; j <= r; j++) {
                    res = (res + dfs(dp, i + 1, n, j, 2, l, r)) % mod;
                }
            }
            else {
                for (int j = l; j < pre; j++) {
                    res = (res + dfs(dp, i + 1, n, j, 1, l, r)) % mod;
                }
            }
        }
        return res;
    }

    // 与递归 dfs 完全等价的三状态转移：
      // p0[j] = 以值 j 结尾且 status=0 的方案数（仅 len=1 才可能为 1）
      // p1[j] = 以值 j 结尾且 status=1（上一跳是“降”）的方案数
      // p2[j] = 以值 j 结尾且 status=2（上一跳是“升”）的方案数
      //
      // 递推：
      // - 从 status=0 走到下一位：j!=pre，若 j<pre → 新 status=1；j>pre → 新 status=2。
      // - 从 status=1（上一步降）走到下一位：必须 j>pre → 新 status=2。
      // - 从 status=2（上一步升）走到下一位：必须 j<pre → 新 status=1。
      //
      // 对应到下式（j 是“新结尾”的值）：
      // len=2 特殊：c1[j] += sum_{x>j} p0[x] (=k-1-j)，c2[j] += sum_{x<j} p0[x] (=j)
      // len>=3：c1[j] += sum_{x>j} p2[x]；c2[j] += sum_{x<j} p1[x]
      // 且 c0[*] 始终为 0（从第二位开始方向已定）
    int zigZagArrays(int n, int l, int r) {
        int k = r - l + 1;
        if (k <= 0) return 0;
        if (n == 1) return k % MOD;

        // len=1：还没确定方向，p0 全 1；p1/p2 为 0
        vector<int> p0(k, 1), p1(k, 0), p2(k, 0);
        vector<int> c0(k, 0), c1(k, 0), c2(k, 0);
        vector<int> pref1(k), suff2(k);

        // 从第二个元素开始推
        for (int len = 2; len <= n; ++len) {
            // 预处理：pref1[j]=sum_{x<j} p1[x]；suff2[j]=sum_{x>j} p2[x]
            long long run = 0;
            for (int j = 0; j < k; ++j) {
                pref1[j] = (int)run;
                run += p1[j];
                if (run >= MOD) run -= MOD;
            }
            run = 0;
            for (int j = k - 1; j >= 0; --j) {
                suff2[j] = (int)run;
                run += p2[j];
                if (run >= MOD) run -= MOD;
            }

            // 清零当前层
            // （注意：len>=2 后，c0 始终全 0）
            // 根据 DFS 语义的等价转移：
            // c1[j] = (len==2 ? k-1-j : 0) + sum_{x>j} p2[x]
            // c2[j] = (len==2 ? j       : 0) + sum_{x<j} p1[x]
            if (len == 2) {
                for (int j = 0; j < k; ++j) {
                    int baseDown = (k - 1 - j);       // sum p0[x] for x>j
                    int baseUp = j;                  // sum p0[x] for x<j
                    int v1 = baseDown + suff2[j]; if (v1 >= MOD) v1 -= MOD;
                    int v2 = baseUp + pref1[j]; if (v2 >= MOD) v2 -= MOD;
                    c1[j] = v1;
                    c2[j] = v2;
                }
            }
            else {
                for (int j = 0; j < k; ++j) {
                    c1[j] = suff2[j];   // 来自上一层 status=2，且 x>j
                    c2[j] = pref1[j];   // 来自上一层 status=1，且 x<j
                }
            }

            // 滚动：下一轮不再需要 p0（它只在 len=1 有意义）
            fill(c0.begin(), c0.end(), 0);
            p0.swap(c0);  // 这行只是把 p0 置空（之后不再使用 p0 的值）
            p1.swap(c1);
            p2.swap(c2);
        }

        long long ans = 0;
        for (int j = 0; j < k; ++j) {
            ans += p1[j]; if (ans >= MOD) ans -= MOD;
            ans += p2[j]; if (ans >= MOD) ans -= MOD;
        }
        return (int)ans;
    }

};