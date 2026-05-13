#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int n = arr.size();

        long long sum = 0;
        for (int i = 0;i < n;i++) {
            sum += arr[i];
        }
        if (sum <= target)return arr[n - 1];
        int r = arr[n - 1];
        int l = 0;
        int ans = r;
        long long  m = sum - target;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            long long a = 0;
            for (int i = 0;i < n;i++) {
                if (arr[i] > mid) {
                    a += mid;
                }
                else {
                    a += arr[i];
                }
            }
            if (a - target >= 0) {
                if (a - target < m) {
                    ans = mid;
                    m = a - target;

                }
                else if (a - target == m && mid < ans) {
                    ans = mid;

                }
                r = mid - 1;
            }
            else {
                if (target - a < m) {
                    ans = mid;
                    m = target - a;
                }
                else if (target - a == m && mid < ans) {
                    ans = mid;
                }
                l = mid + 1;
            }
        }
        return ans;
    }
};