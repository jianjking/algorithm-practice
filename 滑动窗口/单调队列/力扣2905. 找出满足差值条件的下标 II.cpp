#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
        if (indexDifference == 0 && valueDifference == 0) return { 0, 0 };

        int n = (int)nums.size();
        vector<int> queue1(n), queue2(n); // 存索引：queue1 维护最小值的单调递增队列，queue2 维护最大值的单调递减队列
        int l1 = 0, r1 = 0; // [l1, r1)
        int l2 = 0, r2 = 0; // [l2, r2)

        for (int i = indexDifference; i < n; ++i) {
            int j = i - indexDifference; // 可选的对手索引范围是 [0..j]（前缀）

            // 更新最小队列：保持 nums[queue1[*]] 递增
            while (l1 < r1 && nums[j] <= nums[queue1[r1 - 1]]) {
                --r1; // 弹掉队尾更大的（或相等的，保证更早/更优）
            }
            queue1[r1++] = j;

            // 更新最大队列：保持 nums[queue2[*]] 递减
            while (l2 < r2 && nums[j] >= nums[queue2[r2 - 1]]) {
                --r2; // 弹掉队尾更小的（或相等的）
            }
            queue2[r2++] = j;

            // 用前缀最小 / 最大 去和 i 配对
            long long d1 = llabs(1LL * nums[i] - nums[queue1[l1]]);
            if (d1 >= valueDifference) {
                return { queue1[l1], i };
            }
            long long d2 = llabs(1LL * nums[i] - nums[queue2[l2]]);
            if (d2 >= valueDifference) {
                return { queue2[l2], i };
            }
        }
        return { -1, -1 };
    }
};
