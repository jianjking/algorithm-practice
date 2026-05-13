#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    long long minOperationsToMakeMedianK(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int mid = n / 2;
        long long ans = 0;

        if (nums[mid] < k) {
            for (int i = mid; i < n && nums[i] < k; i++) {
                ans += k - nums[i];
            }
        }
        else if (nums[mid] > k) {
            for (int i = mid; i >= 0 && nums[i] > k; i--) {
                ans += nums[i] - k;
            }
        }

        return ans;
    }
};