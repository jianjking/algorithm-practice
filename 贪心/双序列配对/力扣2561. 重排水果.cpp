#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        int n = basket1.size();
        map<int, int>cnt;
        for (int i = 0;i < n;i++) {
            cnt[basket1[i]]++;
            cnt[basket2[i]]--;
        }
        int mn = INT_MAX;
        vector<int>ans;
        for (auto& p : cnt) {
            if (abs(p.second) % 2)return -1;
            mn = min(mn, p.first);
            for (int i = abs(p.second) / 2;i > 0;i--) {
                ans.push_back(p.first);
            }
        }
        sort(ans.begin(), ans.end());
        long long sum = 0;
        for (int i = 0;i < ans.size() / 2;i++) {
            sum += min(2 * mn, ans[i]);
        }
        return sum;
    }
};