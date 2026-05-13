#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int maximumProduct(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int cnt = 1;
        vector<int>diff(n + 1);
        diff[0] = nums[0];
        for (int i = 1;i < n;i++) {
            diff[i] = nums[i] - nums[i - 1];
        }
        while (cnt < n&&k>0) {
            while (cnt< n && nums[cnt] == nums[cnt-1])cnt++;
            if (cnt == n)break;
            int cha = nums[cnt] - nums[cnt - 1];
            int shu = cha * cnt;
            if (k >= shu) {
                diff[0] += cha;
                diff[cnt] -= cha;
                nums[cnt - 1] = nums[cnt];
                k -= shu;
            }
            else {
                int a = k / cnt;
                int b = k % cnt;
                diff[0] += a;
                diff[cnt] -= a;
                diff[0] += 1;
                diff[b] -= 1;
                k = 0;
            }
        }
        if (k > 0) {
            int a = k / n;
            int b = k %n;
            diff[0] += a;
            diff[n] -= a;
            diff[0] += 1;
            diff[b] -= 1;
        }
        vector<int>arr(n);
        arr[0] = diff[0];
        for (int i = 1;i < n;i++) {
            arr[i] =arr[i-1]+ diff[i];
        }
        long long ans = 1;
        for (int i = 0;i < n;i++) {
            ans = (ans * arr[i]) % mod;
        }
        return ans;
    }
};