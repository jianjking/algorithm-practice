#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 这里的 value 返回的是 “前 i 头奶牛最优且第 i 头不被选(dpSkip[i]) 减去前缀和 nums[i]”
// dpSkip[i] = (i>0?dp[i-1]:0)
inline long long value(int i, const vector<long long>& dp, const vector<long long>& nums) {
    return i < 0 ? 0LL : ((i > 0 ? dp[i - 1] : 0LL) - nums[i]);
}

// 把下标 i 加入单调队列，维护 value(j) 单调递减
void add(int i, int& l, int& r,
    vector<int>& que,
    const vector<long long>& dp,
    const vector<long long>& nums) {
    if (i < 0) return;
    long long cur = value(i, dp, nums);
    while (l < r && value(que[r - 1], dp, nums) <= cur) {
        --r;
    }
    que[r++] = i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    // 前缀和
    for (int i = 1; i < n; ++i) {
        nums[i] += nums[i - 1];
    }

    vector<long long> dp(n);
    vector<int> que(n);
    int l = 0, r = 0;
    que[r++] = -1;  // 哨兵，下标 -1 对应 value(-1)=0

    for (int i = 0; i < n; ++i) {
        // 1) 将 j = i-1 入队
        add(i - 1, l, r, que, dp, nums);
        // 2) 弹出失效的 j < i-k
        while (l < r && que[l] < i - k) ++l;
        // 3) 以 i 结尾开新段的候选值
        long long cand = nums[i] + value(que[l], dp, nums);
        // 4) 状态转移：不选 i 或 选新段到 i
        dp[i] = max((i > 0 ? dp[i - 1] : 0LL), cand);
    }

    cout << dp[n - 1] << "\n";
    return 0;
}
