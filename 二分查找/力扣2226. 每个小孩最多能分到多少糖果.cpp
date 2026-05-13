#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool f(int mid, vector<int>& tang, long long k) {
        long long ans = 0;
        for (auto& p : tang)ans += p / mid;
        return ans >= k;
    }
    int maximumCandies(vector<int>& candies, long long k) {
        int mx = INT_MIN;
        for (auto& p : candies)mx = max(mx, p);
        int l = 1;
        int r = mx;
        int ans = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (f(mid, candies, k)) {
                ans = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        return ans;
    }
};