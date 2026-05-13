#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
ll power(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1)ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}
class Solution {
public:
    long long makeIntegerBeautiful(long long n, int target) {
        ll tmp = n;
        ll a = n;
        int cnt = 0;
        while (tmp) {
            tmp /= 10;
            cnt++;
        }
        ll limit = power(10, cnt - 1);
        vector<ll>nums(cnt);
        for (int i = 0;i < cnt;i++) {
            if (i == 0) nums[i] = n / limit;
            else nums[i] = nums[i - 1] + n / limit;
            n = n % limit;
            limit /= 10;
        }
        if (nums[cnt - 1] <= target)return 0;
        for (int i = cnt - 2;i >= 0;i--) {
            if (nums[i] < target) {
                return power(10, cnt - i - 1) - a % power(10, cnt - i - 1);
            }
        }
        return power(10, cnt) - a;
    }
};