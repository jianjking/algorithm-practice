#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool f(vector<int>& time, long long total, int times) {
        long long n = time.size();
        long long sum = 0;
        for (long long i = 0;i < n;i++) {
            sum += total / time[i];
        }
        if (sum < times) {
            return false;
        }
        return true;
    }
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long min1 = INT_MAX;
        long long n = time.size();
        for (long long i = 0;i < n;i++) {
            min1 = min(min1, (long long)time[i]);
        }
        long long r = min1 * totalTrips;
        long long l = 1;
        long long ans = 0;
        while (l <= r) {
            long long mid = l + ((r - l) >> 1);
            if (f(time, mid, totalTrips)) {
                ans = mid;
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        return ans;
    }
};