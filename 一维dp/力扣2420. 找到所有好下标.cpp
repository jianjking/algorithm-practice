#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> goodIndices(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int>pre(n, 0);
        vector<int>nxt(n, 0);
        int cnt = 1;
        for (int i = 1;i < n;i++) {
            pre[i] = cnt;
            if (nums[i] <= nums[i - 1])cnt++;
            else cnt = 1;
        }
        cnt = 1;
        for (int i = n - 2;i >= 0;i--) {
            nxt[i] = cnt;
            if (nums[i] <= nums[i + 1])cnt++;
            else cnt = 1;
        }
        vector<int>ans;
        for (int i = k;i < n - k;i++
            ) {
            if (pre[i] >= k && nxt[i] >= k)ans.push_back(i);

        }
        return ans;
    }
};