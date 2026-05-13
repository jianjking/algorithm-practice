#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        int n = nums1.size();
        vector<int>arr(n);
        iota(arr.begin(), arr.end(), 0);
        sort(arr.begin(), arr.end(), [&nums2](int a, int b) {
            return nums2[a] < nums2[b];
            });
        vector<int>ans(n);
        int left = 0;
        int right = n - 1;
        for (int i = 0;i < n;i++) {
            if (nums1[i] > nums2[arr[left]]) {
                ans[arr[left]] = nums1[i];
                left++;
            }
            else {
                ans[arr[right--]] = nums1[i];

            }
        }
        return ans;
    }
};