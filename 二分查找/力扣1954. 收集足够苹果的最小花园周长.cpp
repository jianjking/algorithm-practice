#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long minimumPerimeter(long long neededApples) {
        // 用 idx=i 表示「第 i/2 圈」，索引只用到偶数
        vector<long long> nums(1000000, 0);
        nums[2] = 12; // k=1 的累积总数
        
        for(int i = 3; i < 1000000; i++){
            if(i & 1) {
                nums[i] = nums[i-1];        // 奇数索引直接复用前一个偶数
            } else {
                long long k = i / 2;
                nums[i] = nums[i-2] + 12LL * k * k;
            }
        }
        
        // 找到最小的 i 使得 nums[i] >= neededApples
        int p = lower_bound(nums.begin(), nums.end(), neededApples) - nums.begin();
        return 4LL * p; // 因为 perimeter = 4 * i，当 i=2k 时就是 8k
    }
};
