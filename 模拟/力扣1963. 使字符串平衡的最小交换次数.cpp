#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minSwaps(string s) {
        int cnt = 0;
        int ans = 0;
        for (auto& p : s) {
            if (p == ']') {
                cnt--;
                if (cnt < 0) {
                    ans++;
                    cnt += 2;
                }
            }
            else { cnt++; }
        }
        return ans;
    }
};