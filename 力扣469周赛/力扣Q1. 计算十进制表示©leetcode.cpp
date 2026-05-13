#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> decimalRepresentation(int n) {
        vector<int>nums;
        while (n > 0) {
            int cnt = 1;
            while (cnt * 10 <= n) {
                cnt *= 10;
            }
            int p = n / cnt;
            cnt *= p;
            nums.push_back(cnt);
            n -= cnt;
        }
        return nums;
    }
};