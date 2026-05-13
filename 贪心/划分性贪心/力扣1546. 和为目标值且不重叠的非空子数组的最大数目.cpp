#include<iostream>
#include<vector>
#include<set>
using  namespace std;
class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        set<int>f;
        int n = nums.size();
        f.insert(0);
        int sum = 0;
        int ans = 0;
        for (int i = 0;i < n;i++) {
            sum += nums[i];
            if (f.find(sum - target) != f.end()) {
                f.clear();
                f.insert(0);
                ans++;
            }
            f.insert(sum);
        }
        return ans;
    }
};