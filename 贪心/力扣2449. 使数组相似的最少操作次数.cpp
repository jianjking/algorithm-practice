#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long makeSimilar(vector<int>& nums, vector<int>& target) {
        sort(nums.begin(), nums.end());
        int l = 0;
        int r = 0;
        vector<int>ou1;
        vector<int>qi1;
        for (auto& p : nums) {
            if (p % 2)qi1.push_back(p);
            else ou1.push_back(p);
        }
        long long ans = 0;
        sort(target.begin(), target.end());
        for (auto& p : target) {
            int tmp;
            if (p % 2)tmp = abs(qi1[r++] - p);
            else tmp = abs(ou1[l++] - p);
            ans += tmp;
        }
        return ans / 4;

    }
};
