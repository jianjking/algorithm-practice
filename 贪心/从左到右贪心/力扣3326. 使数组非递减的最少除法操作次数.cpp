#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e6 + 1;
vector<int>lcp(mod, 0);
void initlcp(int n) {
    for (int i = 2;i < n;i++) {
        if (lcp[i] == 0) {
            lcp[i] = i;
            for (int j = i;j < n;j += i) {
                if (lcp[j] == 0)
                    lcp[j] = i;
            }
        }

    }
}
class Solution {
public:
    int minOperations(vector<int>& nums) {
        initlcp(mod);
        int n = nums.size();
        int ans = 0;
        for (int i = n - 2;i >= 0;i--) {
            if (nums[i] > nums[i + 1]) {
                nums[i] = lcp[nums[i]];
                ans++;
                if (nums[i] > nums[i + 1]) {
                    return -1;
                }
            }
        }
        return ans;
    }
};