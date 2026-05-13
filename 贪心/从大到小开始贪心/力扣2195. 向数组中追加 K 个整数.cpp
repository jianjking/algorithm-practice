#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long minimalKSum(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        auto last = unique(nums.begin(), nums.end());
        nums.erase(last, nums.end());

        long long prev = 0; // 上一个已存在的数
        long long sum = 0;
        for (auto num : nums) {
            if (k <= 0) break;
            // 当前区间 (prev, num) 中可以用的数的个数
            long long gap = max(0LL, num - prev - 1);
            if (gap <= k) {
                sum += (prev + 1 + num - 1) * gap / 2;
                k -= gap;
            }
            else {
                sum += (prev + 1 + prev + k) * k / 2;
                k = 0;
            }
            prev = num;
        }
        // 处理剩余的k（所有数都大于当前最大值）
        if (k > 0) {
            sum += (prev + 1 + prev + k) * k / 2;
        }
        return sum;
    }
};