#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ans = 0;
        int hp = 0;
        for (auto p : nums) {
            if (hp == 0) {
                ans = p;
                hp = 1;
            }
            else {
                if (p == ans)hp++;
                else hp--;
            }
        }
        return ans;
    }
};