#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
struct compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first;
    }
};
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<int>nums;
        int n = buildings.size();
        nums.reserve(3 * n);
        for (int i = 0;i < n;i++) {
            nums.push_back(buildings[i][0]);
            nums.push_back(buildings[i][1] - 1);
            nums.push_back(buildings[i][1]);
        }
        sort(nums.begin(), nums.end());
        auto p2 = unique(nums.begin(), nums.end());
        nums.erase(p2, nums.end());
        sort(buildings.begin(), buildings.end(), [](auto a, auto b) {
            return a[0] < b[0];
            });
        priority_queue<pair<int, int>, vector<pair<int, int>>, compare>f;
        int m = nums.size();
        int l = 0;
        int r = 0;
        vector<int>ans(m);
        while (r < m) {
            while (l < n) {
                int a = buildings[l][0];
                if (lower_bound(nums.begin(), nums.end(), a) - nums.begin() <= r) {
                    f.push({ buildings[l][2],lower_bound(nums.begin(), nums.end(), buildings[l][1] - 1) - nums.begin() });
                    l++;
                }
                else {
                    break;
                }
            }
            while (!f.empty() && f.top().second < r) {
                f.pop();

            }
            if (f.empty()) {
                ans[r] = 0;
            }
            else {
                ans[r] = f.top().first;
            }
            r++;
        }
        vector<vector<int>>cnt;
        cnt.push_back({ nums[0],ans[0] });
        for (int i = 1;i < m;i++) {
            if (ans[i] != ans[i - 1]) {
                cnt.push_back({ nums[i],ans[i] });
            }
        }
        return cnt;
    }
};
