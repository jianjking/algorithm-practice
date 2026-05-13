#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        vector<int>l(n, 0);
        vector<int>r(n, 0);
        int cnt = 0;
        int sum = 0;
        for (int i = 0;i < n;i++) {
            if (s[i] == '0')cnt++;
            else if (i == n - 1 || (i + 1 < n && s[i + 1] == '0')) {
                l[i] = cnt;
                cnt = 0;
                sum++;
            }
            else {
                l[i] = cnt;
                sum++;
            }
        }
        cnt = 0;
        for (int i = n - 1;i >= 0;i--) {
            if (s[i] == '0')cnt++;
            else if (i == 0 || (i >= 0 && s[i - 1] == '0')) {
                r[i] = cnt;
                cnt = 0;

            }
            else {
                r[i] = cnt;

            }
        }
        int ans = 0;
        for (int i = 0;i < n;i++) {
            if (l[i] > 0 && r[i] > 0) {
                ans = max(ans, l[i] + r[i]);
            }
        }
        return ans + sum;
    }
};