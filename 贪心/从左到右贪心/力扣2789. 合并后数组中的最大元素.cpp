#include<iostream>
#include<vector>
using namespace std;
//倒着遍历
class Solution {
public:
    long long maxArrayValue(vector<int>& nums) {
        long long ans = 0, suffix = 0;
        // 从最右端往左扫描
        for (int i = nums.size() - 1; i >= 0; --i) {
            // 如果当前 nums[i] <= suffix，就可以加到后面那段里；否则自己重新做一段
            if (nums[i] <= suffix) {
                suffix += nums[i];
            }
            else {
                suffix = nums[i];
            }
            // 每步都更新答案
            ans = max(ans, suffix);
        }
        return ans;
    }
};
