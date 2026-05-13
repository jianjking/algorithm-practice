#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int>cnt(26, 0);
        for (auto& p : word) {
            cnt[p - 'a']++;
        }
        int ans = INT_MAX;
        for (auto& p : cnt) {
            int tmp = 0;
            for (auto& q : cnt) {
                if (q < p) {
                    tmp += q;
                }
                if (q > p + k) {
                    tmp += q - p - k;
                }
            }
            ans = min(ans, tmp);
        }
        return ans;
    }
};

