#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        vector<int> s(n + 1, 0);  // 前缀和数组 s[0] = 0，s[i] = nums[0] + ... + nums[i-1]

        // 手动计算前缀和
        for (int i = 0; i < n; ++i) {
            s[i + 1] = s[i] + nums[i];
        }

        int ans = 0;

        auto f = [&](int A, int B) {
            int maxA = 0;
            for (int i = A + B; i <= n; ++i) {
                // 左侧子数组 [i - B - A, i - B)
                int sumA = s[i - B] - s[i - B - A];
                maxA = max(maxA, sumA);

                // 右侧子数组 [i - B, i)
                int sumB = s[i] - s[i - B];

                // 更新答案
                ans = max(ans, maxA + sumB);
            }
            };

        // 尝试两种顺序：A在前，B在前
        f(firstLen, secondLen);
        f(secondLen, firstLen);

        return ans;
    }
};
