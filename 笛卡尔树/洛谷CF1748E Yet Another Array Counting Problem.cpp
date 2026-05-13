#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;

// 最大笛卡尔树：while 用 <（相等不弹）=> 左优先最大
void build(const vector<int>& nums, vector<int>& zuo, vector<int>& you, int& head){
    int n = (int)nums.size() - 1;
    vector<int> st(n + 1, 0);
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;
        while (pos > 0 && nums[st[pos]] < nums[i]) pos--;
        if (pos > 0) you[st[pos]] = i;
        if (pos < top) zuo[i] = st[pos + 1];
        st[++pos] = i;
        top = pos;
    }
    head = st[1]; // 栈底是根
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> nums(n + 1);
        for (int i = 1; i <= n; i++) cin >> nums[i];

        vector<int> zuo(n + 1, 0), you(n + 1, 0);
        int head = 0;
        build(nums, zuo, you, head);

        // dp[u][j] : 以 u 为根的子树，所有值在 [1..j] 内，满足 左<根<=右 的方案数
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int j = 0; j <= m; j++) dp[0][j] = 1; // 空树恒 1

        // 后序遍历顺序（非递归）：stack1->stack2
        vector<int> s1, s2;
        if (head) {
            s1.push_back(head);
            while (!s1.empty()) {
                int u = s1.back(); s1.pop_back();
                s2.push_back(u);
                if (zuo[u]) s1.push_back(zuo[u]);
                if (you[u]) s1.push_back(you[u]);
            }
        }

        // 逐点做 DP：tmp[j] = dp[L][j-1] * dp[R][j]，dp[u][j] = dp[u][j-1] + tmp[j]
        vector<int> tmp(m + 1, 0);
        while (!s2.empty()) {
            int u = s2.back(); s2.pop_back();
            int L = zuo[u], R = you[u];

            tmp[0] = 0;
            for (int j = 1; j <= m; j++) {
                long long x = 1LL * dp[L][j - 1] * dp[R][j] % mod;
                tmp[j] = (int)x;
            }
            dp[u][0] = 0;
            for (int j = 1; j <= m; j++) {
                int val = dp[u][j - 1] + tmp[j];
                if (val >= mod) val -= mod;
                dp[u][j] = val;
            }
        }

        cout << dp[head][m] << '\n';
    }
    return 0;
}
