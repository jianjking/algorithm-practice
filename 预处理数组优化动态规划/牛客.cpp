// https://www.nowcoder.com/practice/49c5284278974cbda474ec13d8bd86a9
// https://www.nowcoder.com/practice/49c5284278974cbda474ec13d8bd86a9
#include<iostream>
#include<vector>
using namespace std;
const int mod = 998244353;

// dp[v][0] / dp[v][1] : 两态；v 取 0..200
// suf0[v] = sum_{x=v..200} dp[x][0]
// pre1[v] = sum_{x=1..v}   dp[x][1]
static int suf0[201], pre1[201];

static inline int addmod(long long x) {
    x %= mod;
    return (int)(x < 0 ? x + mod : x);
}

// === 你原来调用但没实现的预处理 ===
static inline void prepare(const vector<vector<long long>>& dp) {
    // 后缀和：dp[*][0]
    suf0[200] = (int)dp[200][0];
    for (int v = 199; v >= 0; --v) {
        int t = suf0[v + 1] + (int)dp[v][0];
        if (t >= mod) t -= mod;
        suf0[v] = t;
    }
    // 前缀和：dp[*][1]
    pre1[0] = 0;
    pre1[1] = (int)dp[1][1];
    for (int v = 2; v <= 200; ++v) {
        int t = pre1[v - 1] + (int)dp[v][1];
        if (t >= mod) t -= mod;
        pre1[v] = t;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> nums(n + 1);
    for (int i = 1; i <= n; i++) cin >> nums[i];

    // === 状态：v 用 0..200（保留你 201 的尺寸，但多用了一行 0，方便边界）===
    vector<vector<long long>> dp(201, vector<long long>(2, 0));

    // 初始化：两态模板的标准起点（等价于你 Java 版的 memo 初值）
    // 这样后面每一位都统一用一套转移；不用再特殊处理 nums[1]
    for (int v = 0; v <= 200; ++v) {
        dp[v][0] = 0;
        dp[v][1] = 1;
    }

    // 逐位推进：i = 1..n（你原来只到 n-1，会漏掉最后一位）
    for (int i = 1; i <= n; i++) {
        prepare(dp);
        vector<vector<long long>> cur(201, vector<long long>(2, 0));

        // 固定值 or 自由取
        if (nums[i] != 0) {
            int x = nums[i];

            // 选 = x ：来自 dp[x][1]
            cur[x][0] = (cur[x][0] + dp[x][1]) % mod;  // 写法保留你原来的“0/1两格都加”
            cur[x][1] = (cur[x][1] + dp[x][1]) % mod;

            // 选 > x ：来自 sum_{k>x} dp[k][0]  （= suf0[x+1]）
            if (x + 1 <= 200) {
                int inc = suf0[x + 1];
                cur[x][1] = (cur[x][1] + inc) % mod;   // 只影响 state=1
            }

            // 选 < x ：来自 sum_{k<=x-1} dp[k][1] （= pre1[x-1]）
            if (x - 1 >= 0) {
                int dec = pre1[x - 1];
                cur[x][1] = (cur[x][1] + dec) % mod;   // 也汇入 state=1
            }
        }
        else {
            // 自由选择 j=1..200
            for (int j = 1; j <= 200; j++) {
                long long ans0 = 0, ans1 = 0;

                // 选 = j ：来自 dp[j][1]
                ans0 += dp[j][1];
                ans1 += dp[j][1];

                // 选 > j ：来自 sum_{k>j} dp[k][0] = suf0[j+1]
                if (j + 1 <= 200) {
                    ans1 += suf0[j + 1];
                }

                // 选 < j ：来自 sum_{k<=j-1} dp[k][1] = pre1[j-1]
                if (j - 1 >= 0) {
                    ans1 += pre1[j - 1];
                }

                cur[j][0] = ans0 % mod;
                cur[j][1] = ans1 % mod;
            }
        }

        dp.swap(cur);
    }

    // 收尾：两态标准答案
    cout << dp[0][1] % mod << "\n";
    return 0;
}
