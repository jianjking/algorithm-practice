#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool check(vector<long long> power, int k, long long mid, int r) {
        int n = power.size();
        vector<long long>diff(n, 0);
        long long sum = 0;
        for (int i = 0;i < n;i++) {
            sum += diff[i];
            if (power[i] + sum < mid) {
                int need = mid - power[i] - sum;
                if (k < need)return false;
                k -= need;
                sum += need;
                if (i + 2 * r + 1 < n)diff[i + 2 * r + 1] -= need;
            }
        }
        return true;
    }
    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();
        vector<long long>cnt(n + 1, 0);
        for (int i = 0;i < n;i++) {
            cnt[i + 1] = cnt[i] + stations[i];
        }
        long long mn = LLONG_MAX;
        vector<long long>power(n, 0);
        for (int i = 0;i < n;i++) {
            long long left = max(0, i - r);
            long long right = min(n - 1, i + r);
            power[i] = cnt[right + 1] - cnt[left];
            mn = min(mn, power[i]);
        }
        long long left = mn;
        long long right = mn + k;
        long long ans = -1;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (check(power, k, mid, r)) {
                left = mid + 1;
                ans = mid;
            }
            else {
                right = mid - 1;
            }
        }
        return ans;
    }
};