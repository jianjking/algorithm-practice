#include<bits/stdc++.h>
class Solution {
public:
    int minimumArrayLength(std::vector<int> &nums) {
        int m = ranges::min(nums);
        for (int x : nums) {
            if (x % m) {
                return 1;
            }
        }
        return (ranges::count(nums, m) + 1) / 2;
    }
};
