#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = queries.size();
        int m = s.size();
        vector<int>nums;
        for (int i = 0; i < m; i++) {
            if (s[i] == '|') {
                nums.push_back(i);
            }
        }
        vector<int>ans(n);
        for (int i = 0; i < n; i++) {
            auto p1 = lower_bound(nums.begin(), nums.end(), queries[i][0])-nums.begin();
            auto p2 = upper_bound(nums.begin(), nums.end(), queries[i][1])-nums.begin()-1;
            if (p1 >= p2)ans[i] = 0;
            else ans[i] = nums[p2] - nums[p1] - p2 + p1;
           
        }
        return ans;
    }
};