#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        auto f = [&](int last1, int last2) -> int {
            int res = 0;
            for (int i = 0; i + 1 < nums1.size(); i++) {
                int x = nums1[i], y = nums2[i];
                if (x > last1 || y > last2) {
                    if (y > last1 || x > last2) {
                        return nums1.size() + 1;
                    }
                    res++;
                }
            }
            return res;
            };
        int ans = min(f(nums1.back(), nums2.back()), 1 + f(nums2.back(), nums1.back()));
        return ans > nums1.size() ? -1 : ans;
    }
};
