#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        int n = endTime.size();
        vector<int>nums(n + 1);
        nums[0] = startTime[0];
        for (int i = 1;i < n;i++) {
            nums[i] = startTime[i] - endTime[i - 1];
        }
        nums[n] = eventTime - endTime[n - 1];
        deque<int>dui;
        long long sum = 0;
        long long ans = LLONG_MIN;
        for (int i = 0;i <= n;i++) {
            while (!dui.empty() && dui.front() <= i - k - 1) {
                sum -= nums[dui.front()];
                dui.pop_front();
            }
            dui.push_back(i);
            sum += nums[i];
            ans = max(ans, sum);
        }
        return ans;
    }
};