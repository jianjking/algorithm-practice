#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        int n = nums.size();
        int tmp = 0;
        int hp = 0;
        for (auto p : nums) {
            if (hp == 0) {
                tmp = p;
                hp = 1;
            }
            else {
                if (p == tmp)hp++;
                else hp--;
            }
        }
        hp = 0;
        for (auto p : nums) {
            if (p == tmp)hp++;
        }
        for (int i = 0, l = 0, r = hp;i < n - 1;i++) {
            if (nums[i] == tmp) {
                l++;
                r--;
            }
            if (l > (i - 0 + 1) / 2 && r > (n - i - 1) / 2)return i;
        }
        return -1;
    }
};