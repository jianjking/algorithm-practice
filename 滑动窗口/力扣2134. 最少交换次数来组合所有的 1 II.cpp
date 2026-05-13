#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int>arr(2 * n, 0);
        int sum = 0;
        for (int i = 0;i < 2 * n;i++) {
            arr[i] = nums[i % n];
            if (i < n)sum += arr[i];
        }
        deque<int>f;
        int ans = 0;
        int tmp = 0;
        for (int i = 0;i < n + sum - 1;i++) {
            f.push_back(i);
            tmp += arr[i];
            while (!f.empty() && f.front() <= i - sum) {
                tmp -= arr[f.front()];
                f.pop_front();
            }
            ans = max(ans, tmp);
        }
        return sum - ans;
    }
};