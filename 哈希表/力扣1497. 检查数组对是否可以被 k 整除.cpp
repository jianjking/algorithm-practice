#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        vector<int>cnt(k, 0);
        for (auto& p : arr) {
            cnt[((p % k)+k)%k]++;
        }
        for (int i = 1; i < (k+1)/2; i++) {
            if (cnt[i] != cnt[k - i])return false;
        }
        if (cnt[0] % 2 != 0)return false;
        if (k % 2 == 0 && cnt[k / 2] % 2 != 0)return false;
        return true;
    }
};