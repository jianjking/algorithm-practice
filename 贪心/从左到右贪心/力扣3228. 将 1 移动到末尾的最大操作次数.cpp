#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxOperations(string s) {
        int n = s.size();
        int ans = 0;
        int cnt = 0;
        for (int i = 0;i < n;i++) {
            if (s[i] == '1')cnt++;
            if (i+1<n&&s[i] == '1' && s[i + 1] == '0') {
                ans += cnt;
                

            }
        }
        return ans;
    }
};