#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums) {
        this->nums = nums;
        int n = nums.size();
        // 初始化 memo 的大小
        memo.resize(n, vector<int>(n, -1));

        // 三种不同的第一次操作方式，分别对应三种 target
        // 每次调用前清空 memo
        memo.assign(n, vector<int>(n, -1));
        int res1 = dfs(2, n - 1, nums[0] + nums[1]);

        memo.assign(n, vector<int>(n, -1));
        int res2 = dfs(0, n - 3, nums[n - 2] + nums[n - 1]);

        memo.assign(n, vector<int>(n, -1));
        int res3 = dfs(1, n - 2, nums[0] + nums[n - 1]);

        return max({ res1, res2, res3 }) + 1;
    }

private:
    vector<int> nums;
    vector<vector<int>> memo;

    // 普通的递归 + 记忆化
    int dfs(int i, int j, int target) {
        if (i >= j) return 0;
        int& ans = memo[i][j];
        if (ans != -1) return ans;

        ans = 0;
        // 删最左两，删最右两，删首尾各一个
        if (nums[i] + nums[i + 1] == target)
            ans = max(ans, dfs(i + 2, j, target) + 1);
        if (nums[j - 1] + nums[j] == target)
            ans = max(ans, dfs(i, j - 2, target) + 1);
        if (nums[i] + nums[j] == target)
            ans = max(ans, dfs(i + 1, j - 1, target) + 1);

        return ans;
    }
};
