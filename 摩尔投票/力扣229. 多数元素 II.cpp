#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        int ans1 = INT_MIN, ans2 = INT_MIN;
        int hp1 = 0;
        int hp2 = 0;
        for (auto p : nums) {
            if (p == ans2)hp2++;
            else if (p == ans1)hp1++;
            else if (hp1 == 0) {
                ans1 = p;
                hp1 = 1;
            }

            else if (hp2 == 0) {
                ans2 = p;
                hp2 = 1;
            }

            else {
                hp1--;
                hp2--;
            }

        }
        hp1 = 0;
        hp2 = 0;
        for (auto p : nums) {
            if (p == ans1)hp1++;
            if (p == ans2)hp2++;
        }
        if (hp1 * 3 <= n && hp2 * 3 <= n)return {};
        if (3 * hp1 <= n)return{ ans2 };
        if (3 * hp2 <= n)return { ans1 };
        if (ans1 == ans2)return { ans1 };
        return { ans2,ans1 };
    }
};