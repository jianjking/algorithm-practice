#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string lexSmallest(string s) {
        int n = s.size();
        string ans = s;
        for (int k = 1; k <= n; k++) {
            string t1 = s;
            reverse(t1.begin(), t1.begin() + k);
            ans = min(ans, t1);

            string t2 = s;
            reverse(t2.begin() + n - k, t2.end());
            ans = min(ans, t2);
        }
        return ans;
    }
};
