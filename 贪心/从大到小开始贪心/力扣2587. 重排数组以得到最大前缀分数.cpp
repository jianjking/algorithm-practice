#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maxScore(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return a > b;
            });
        int n = nums.size();
        int ans = 0;
        vector<long long>sum(n + 1, 0);
        for (int i = 1;i <= n;i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        for (int i = 1;i <= n;i++) {
            if (sum[i] > 0)ans++;
            else {
                break;
            }
        }
        return ans;
    }
};