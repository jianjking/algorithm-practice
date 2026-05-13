#include<iostream>
#include<vector>
#include<algorithm>
#include<algorithm>
using namespace std;
//时间复杂度好但是内存太大了
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        long long m = INT_MIN;
        int n = power.size();
        for (int i = 0;i < n;i++) {
            m = max(m, (long long)power[i]);
        }
        vector<long long>sum(m + 1, 0);
        sort(power.begin(), power.end());
        int cnt = power[0];
        for (int i = 1;i < n;i++) {
            while (i < n && power[i] == power[i - 1]) {
                cnt += power[i];
                i++;
            }
            sum[power[i - 1]] = cnt;
            if (i < n)cnt = power[i];
        }
        sum[power[n - 1]] = cnt;
       long long a=  sum[1];
       if (m == 1)return a;
        long long b= max(a, sum[2]);
        long long prepre = 0;
        for (int i = 3;i <= m;i++) {
            int tmp = b;
            b = max(max(b,a), prepre + sum[i]);
            prepre = a;
            a = tmp;
        }
        return b;
    }
};
//没必要开这么大的内存可以用哈希表
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        int n = power.size();
        if (n == 0) return 0;

        // 1) 先统计每个 power 能带来的总伤害
        unordered_map<int, long long> sum;
        sum.reserve(n);
        for (int v : power) {
            sum[v] += v;
        }

        // 2) 把所有不同的 power 排序
        vector<int> keys;
        keys.reserve(sum.size());
        for (auto& p : sum) keys.push_back(p.first);
        sort(keys.begin(), keys.end());

        int k = keys.size();
        // dp[i]: 只考虑 keys[0..i-1] 时的最优解
        // dp[0] = 0（一个都不取）
        vector<long long> dp(k + 1, 0);

        for (int i = 1; i <= k; i++) {
            int x = keys[i - 1];
            long long s = sum[x];

            // 找到 j：最大的 j<i，使得 keys[j-1] <= x-3
            // 也就是在取 x 时，要跳过 x-1 和 x-2
            int lo = 0, hi = i - 1;
            while (lo < hi) {
                int mid = (lo + hi + 1) / 2;
                if (keys[mid - 1] <= x - 3) lo = mid;
                else hi = mid - 1;
            }
            long long take = s + dp[lo];
            // 不取 x：dp[i-1]
            dp[i] = max(dp[i - 1], take);
        }

        return dp[k];
    }
};
