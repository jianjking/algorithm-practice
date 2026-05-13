#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    int getLargestOutlier(vector<int>& nums) {
        unordered_map<int, int> cnt;
        int total = 0;
        for (int x : nums) {
            cnt[x]++;
            total += x;
        }

        int ans = INT_MIN;
        for (int x : nums) {
            cnt[x]--;
            if ((total - x) % 2 == 0 && cnt[(total - x) / 2] > 0) {
                ans = max(ans, x);
            }
            cnt[x]++;
        }
        return ans;
    }
};
