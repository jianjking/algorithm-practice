#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool zhen(vector<int>& dist, double hour, int v) {
        double ans = 0;
        int n = dist.size();
        for (int i = 0;i < n - 1;i++) {
            ans += (dist[i] + v - 1) / v;
        }
        ans += dist[n - 1] / (double)v;
        return ans <= hour;
    }
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int l = 1;
        int r = 1e7;
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (zhen(dist, hour, mid)) {
                r = mid - 1;
                ans = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return ans;
    }
};