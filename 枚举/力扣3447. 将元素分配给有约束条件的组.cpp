#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        int mx = INT_MIN;
        for (auto& p : groups) {
            mx = max(p, mx);
        }
        vector<int>ans(mx + 1, -1);
        int m = elements.size();
        for (int i = 0;i < m;i++) {
            if (elements[i] > mx)continue;
            if (ans[elements[i]] != -1)continue;
            for (int j = elements[i];j <= mx;j += elements[i]) {
                if (ans[j] == -1)ans[j] = i;
            }
        }
        int n = groups.size();
        vector<int>nums(n, 0);
        for (int i = 0;i < n;i++) {
            nums[i] = ans[groups[i]];
        }
        return nums;
    }
};