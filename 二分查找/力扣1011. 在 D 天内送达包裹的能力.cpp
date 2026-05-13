#include<iostream>
#include<vector>
using namespace std;
bool yes(vector<int>& weights, long long mid, int days) {
    long long sum = 0;
    int cnt = 1;
    for (auto& p : weights) {
        if (sum + p > mid) {
            sum = 0;
            cnt++;
        }
        sum += p;
    }
    return cnt <= days;

}
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        long long r = 0;
        long long mx = LLONG_MIN;
        for (auto& p : weights) {
            r += p;
            mx = max(mx, (long long)p);
        }
        long long l = 0;
        long long ans = 0;
        while (l <= r) {
            long long mid = r + (l - r) / 2;
            if (mid >= mx && yes(weights, mid, days)) {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans;
    }
};