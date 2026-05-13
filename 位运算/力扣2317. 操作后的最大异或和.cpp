#include<iostream>
#include<vector>
using namespace std;
//其实全部或一下就知道哪些位置上有1
class Solution {
public:
    int maximumXOR(vector<int>& nums) {
        vector<int>cnt(32, 0);
        for (auto& p : nums) {
            int tmp = 0;
            while (p > 0) {
                if (p & 1 == 1)cnt[tmp]++;
                p >>= 1;
                tmp++;
            }
        }
        int ans = 0;
        for (int i = 0;i < 31;i++) {
            if (cnt[i] != 0)ans += pow(2, i);
        }
        return ans;
    }
};