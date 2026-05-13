#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    static constexpr int NEG = INT_MIN / 4;

    // g(i, used): 以 i 开头的最大和，used ∈ {0,1} 表示还能删的次数
    int g(int i, int used, const vector<int>& a, vector<vector<int>>& dp) {
        if (i >= (int)a.size()) return NEG;        // 不能从越界处“开头”
        int& res = dp[i][used];
        if (res != INT_MIN / 2) return res;

        // 选 a[i]，然后三种走法：立刻停、继续不删、删掉 i+1 再继续
        int keepTail = (i + 1 < (int)a.size() ? g(i + 1, used, a, dp) : NEG);
        int skipNext = (used > 0 && i + 1 < (int)a.size() ? g(i + 2, 0, a, dp) : NEG);

        // 以 i 开头必须包含 a[i]，后缀可以不延伸（相当于“这里就停”）
        res = a[i] + max({ 0, keepTail, skipNext });
        return res;
    }

    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(2, INT_MIN / 2));
        int ans = INT_MIN;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, g(i, 1, arr, dp));  // 以 i 开头，允许删一次
            ans = max(ans, g(i, 0, arr, dp));  // 以 i 开头，不删
        }
        return ans;
    }
};
