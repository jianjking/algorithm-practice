#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        vector<int>cnt(26, 0);
        for (int i = 0;i < s.size();i++) {
            cnt[s[i] - 'a']++;
        }
        string ans;
        for (int i = 25, j = 24;i >= 0;) {
            if (cnt[i] <= repeatLimit) {
                for (int j = 0;j < cnt[i];j++) {
                    ans += 'a' + i;
                }
                i--;
            }
            else {

                for (int j = 0;j < repeatLimit;j++) {
                    ans += 'a' + i;
                }
                cnt[i] -= repeatLimit;
                bool find = false;
                for (int j = i - 1;j >= 0;j--) {
                    if (cnt[j] > 0) {
                        cnt[j]--;
                        ans += 'a' + j;
                        find = true;
                        break;
                    }
                }
                if (!find)break;
            }
        }
        return ans;
    }
};