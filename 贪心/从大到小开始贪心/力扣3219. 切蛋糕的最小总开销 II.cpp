#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        vector<pair<int, int>>cnt(m + n - 2);
        for (int i = 0; i < m - 1; i++) {
            cnt[i] = { horizontalCut[i],0 };
        }
        for (int i = 0; i < n - 1; i++) {
            cnt[i + m - 1] = { verticalCut[i],1 };
        }
        sort(cnt.begin(), cnt.end(), [&](pair<int, int>& a, pair<int, int>& b) {
            return a.first > b.first;
            });
        int i = 1;
        int j = 1;
        long long ans = 0;
        for (auto& p : cnt) {
            if (p.second == 0) {
                ans += i * p.first;
                j++;
            }
            else {
                ans += j * p.first;
                i++;
            }
        }
        return ans;
    }
};