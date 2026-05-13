#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        vector<int>arr(n);
        long long ans = 0;
        for (int i = 0;i < n;i++) {
            arr[i] = abs(nums1[i] - nums2[i]);
            ans += (long long)arr[i] * arr[i];
        }
        sort(arr.begin(), arr.end(), [](int a, int b) {return a > b;
            });
        int k = k1 + k2;
        arr.push_back(0);
        for (int i = 0;i < n;i++) {
            int j = i + 1;
            ans -= (long long)arr[i] * arr[i];
            long long d = ((long long)arr[i] - arr[j]) * j;
            if (k > d) {
                k -= d;
                continue;
            }
            long long b = k / j;
            long long c = k % j;
            long long h = arr[i] - b;
            long long part = (j - c) * (h * h)
                + c * ((h - 1) * (h - 1));
            return ans + part;
        }
        return ans;
    }
};