#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long merge(int l, int r, vector<long long>& sum, long long lower, long long upper) {
        if (l == r) return (sum[l] >= lower && sum[l] <= upper) ? 1 : 0;

        long long ans = 0;
        int mid = l + (r - l) / 2;
        ans += merge(l, mid, sum, lower, upper) + merge(mid + 1, r, sum, lower, upper);

        int ll = l, lr = l;
        for (int i = mid + 1; i <= r; i++) {
            long long maxv = sum[i] - lower;
            long long minv = sum[i] - upper;
            while (ll <= mid && sum[ll] < minv) ll++;
            while (lr <= mid && sum[lr] <= maxv) lr++;
            ans += lr - ll;
        }

        vector<long long> tmp(r - l + 1);
        ll = l;
        lr = mid + 1;
        int k = 0;
        while (ll <= mid && lr <= r) {
            if (sum[ll] <= sum[lr]) tmp[k++] = sum[ll++];
            else tmp[k++] = sum[lr++];
        }
        while (ll <= mid) tmp[k++] = sum[ll++];
        while (lr <= r) tmp[k++] = sum[lr++];

        for (int i = 0; i < r - l + 1; i++) {
            sum[l + i] = tmp[i];
        }
        return ans;
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> sum(n);
        sum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            sum[i] = sum[i - 1] + nums[i];
        }
        return (int)merge(0, n - 1, sum, (long long)lower, (long long)upper);
    }
};
