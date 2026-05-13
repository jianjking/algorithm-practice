#include<iostream>
#include<vector>
#include<stack>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int cal(int l, int cur, int r,
        const vector<int>& ss,
        const vector<int>& nums) {
        // 1. A = ss[r] - ss[cur]
        long long A = (ss[r] - ss[cur] + mod) % mod;
        // 2. B = ss[cur] - ss[l], 但若 l<0 就当作 0
        long long leftPrefix = (l >= 0 ? ss[l] : 0LL);
        long long B = (ss[cur] - leftPrefix + mod) % mod;
        // 3. leftCnt 要用原始的 l
        long long leftCnt = cur - l;   // 当 l==-1 时，cur-(-1)=cur+1
        long long rightCnt = r - cur;

        long long part = (A * leftCnt % mod - B * rightCnt % mod + mod) % mod;
        return int(part * nums[cur] % mod);
    }

    int totalStrength(vector<int>& strength) {
        stack<int>f;
        int ans = 0;
        int n = strength.size();
        vector<int>sum(n + 2, 0);
        for (int i = 1;i <= n;i++) {
            sum[i] = (sum[i - 1] + strength[i - 1])%mod;
        }
        vector<int>ss(n + 2, 0);
        for (int i = 1;i <= n+1;i++) {
            ss[i] = (ss[i - 1] + sum[i])%mod;
        }
        for (int i = 0;i < n;i++) {
            while (!f.empty() && strength[f.top()] >= strength[i]) {
                int cur = f.top();
                f.pop();
                int l = f.empty() ? -1 : f.top();
                ans = (ans + cal(l, cur, i, ss, strength)) % mod;
            }
            f.push(i);
        }
        while (!f.empty()) {
            int cur = f.top();
            f.pop();
            int l = f.empty() ? -1 : f.top();
            ans = (ans + cal(l, cur, n, ss, strength)) % mod;
        }
        return (ans+mod)%mod;
    }
};
