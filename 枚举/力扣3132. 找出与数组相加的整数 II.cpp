#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//题目为删除两个数所以最小的三个数至少会保存下来一个枚举
class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        for (int i = 2;i >= 0;i--) {
            int diff = nums2[0] - nums1[i];
            int r = 0;
            for (int l = 0;l < nums1.size() && r < nums2.size();l++) {
                if (nums1[l] + diff == nums2[r]) {
                    r++;
                }
            }
            if (r == nums2.size())return diff;
        }
        return 0;
    }
};