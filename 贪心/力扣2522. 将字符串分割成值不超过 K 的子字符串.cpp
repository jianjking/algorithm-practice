#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minimumPartition(string s, long long k) {
        int n = s.size();
        int ans = 0;
        int i = 0;
        while (i < n) {
            if (s[i] - '0' > k) return -1;

            long long curr = 0;
            while (i < n && curr * 10 + (s[i] - '0') <= k) {
                curr = curr * 10 + (s[i] - '0');
                i++;
            }
            ans++;  
        }
        return ans;
    }
};
