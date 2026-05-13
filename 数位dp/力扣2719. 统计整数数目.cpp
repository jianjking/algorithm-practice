#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int min;
    int max;
    string s;
    int len;
    vector<vector<pair<int,int>>>dp;
    int f(int i,int sum,int free) {
        if (sum > max)return 0;
        if (sum + (len - i) * 9 < min)return 0;
        if (i == len)return 1;
        if (free == 0 && dp[i][sum].first != -1) {
            return dp[i][sum].first;
        }
        else if (free == 1 && dp[i][sum].second != -1)return dp[i][sum].second;
        int ans = 0;
        int cur = s[i] - '0';
        if (!free) {
            for (int j = 0;j <= cur;j++) {
                if (j < cur) {
                    ans =(ans+ f(i + 1, sum + j, 1))%mod;
                }
                else {
                    ans =(ans+ f(i + 1, sum + j, 0))%mod;
                }
            }
        }
        else {
            for (int j = 0;j <= 9;j++) {
                ans =(ans+ f(i + 1, sum + j, 1))%mod;
            }
        }
        if (free == 0)
            dp[i][sum].first = ans;
        else
            dp[i][sum].second = ans;
        return ans;
    }
    bool p(string& s1) {
        int n = s1.size();
        int ans = 0;
        for (int i = 0;i < n;i++) {
            ans += s1[i] - '0';
        }
        return ans <= max&&ans>=min;
    }
    int count(string num1, string num2, int min_sum, int max_sum) {
        int n = num1.size();
        s = num1;
        len = n;
        min = min_sum;
        max = max_sum;
        dp.resize(n, vector<pair<int, int>>(max_sum+1, { -1,-1 }));
        int ans1 = f(0, 0, 0);
        dp.clear();
        n = num2.size();
        s = num2;
        len = n;
        dp.resize(n, vector<pair<int, int>>(max_sum+1, { -1,-1 }));
        int ans2 = f(0, 0, 0);
        if (p(num1)) {
            return (ans2 - ans1 + 1+mod)%mod;
        }
        return (ans2 - ans1+mod)%mod;
    }
};