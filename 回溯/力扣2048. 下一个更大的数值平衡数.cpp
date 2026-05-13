#include<iostream>
#include<vector>
using namespace std;
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:
    vector<int> nums;

    // 普通成员函数版 dfs
    void dfsGenerate(int remSum, int remLen, vector<int>& cnt, int curNum) {
        if (remLen == 0 && remSum == 0) {
            nums.push_back(curNum);
            return;
        }
        for (int d = 1; d < (int)cnt.size(); ++d) {
            if (cnt[d] == 0) continue;
            // d > cnt[d] 时，不消耗 remSum
            if (d > cnt[d]) {
                cnt[d]--;
                dfsGenerate(remSum, remLen - 1, cnt, curNum * 10 + d);
                cnt[d]++;
            }
            else {
                if (d > remSum) continue;
                cnt[d]--;
                dfsGenerate(remSum - d, remLen - 1, cnt, curNum * 10 + d);
                cnt[d]++;
            }
        }
    }

    // 预先生成所有数值平衡数
    void generateAll() {
        for (int k = 1; k <= 6; ++k) {
            vector<int> cnt(k + 1);
            for (int d = 0; d <= k; ++d) cnt[d] = d;
            dfsGenerate(k, k, cnt, 0);
        }
        // 手动加上 LeetCode 题解中特殊的 1224444
        nums.push_back(1224444);
        sort(nums.begin(), nums.end());
    }

public:
    Solution() {
        generateAll();
    }

    int nextBeautifulNumber(int n) {
        auto it = upper_bound(nums.begin(), nums.end(), n);
        return *it;  // 题目保证一定存在
    }
};
