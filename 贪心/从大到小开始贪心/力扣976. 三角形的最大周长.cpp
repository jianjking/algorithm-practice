#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return a > b;
            });
        int n = nums.size();
        if (n <= 2)return 0;
        int lll = nums[2];
        int ll = nums[1];
        int l = nums[0];
        for (int i = 2;i < n;i++) {
            lll = nums[i];
            if (abs(l - ll) < lll && (ll + lll) > l) {
                return l + ll + lll;
            }
            l = ll;
            ll = lll;
        }
        return 0;
    }
};