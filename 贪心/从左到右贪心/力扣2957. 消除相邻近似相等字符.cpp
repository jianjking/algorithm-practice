#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int removeAlmostEqualCharacters(string s) {
        int ans = 0;
        for (int i = 1; i < s.length(); i++) {
            if (abs(s[i - 1] - s[i]) <= 1) {
                ans++;
                i++;
            }
        }
        return ans;
    }
};
