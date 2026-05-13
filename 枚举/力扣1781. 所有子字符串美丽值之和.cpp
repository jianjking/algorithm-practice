#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int beautySum(string s) {
        int n = s.size();
        vector<vector<int>>cnt(n + 1, vector<int>(26, 0));
        for (int i = 0;i < n;i++) {
            cnt[i + 1] = cnt[i];
            cnt[i + 1][s[i] - 'a']++;
        }
        int ans = 0;
        for (int i = 1;i < n;i++) {
            for (int j = 0;j < i;j++) {
                int mx = INT_MIN;
                int mn = INT_MAX;
                for (int z = 0;z < 26;z++) {
                    if (cnt[i + 1][z] - cnt[j][z] > 0) {
                        mx = max(mx, cnt[i + 1][z] - cnt[j][z]);
                        mn = min(mn, cnt[i + 1][z] - cnt[j][z]);
                    }
                }
                ans += mx - mn;
            }
        }
        return ans;
    }
};