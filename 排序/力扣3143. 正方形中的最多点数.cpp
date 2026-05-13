#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        int n = points.size();
        vector<vector<int>>nums(n, vector<int>(3));
        for (int i = 0;i < n;i++) {
            nums[i][0] = points[i][0];
            nums[i][1] = points[i][1];
            nums[i][2] = i;
        }
        sort(nums.begin(), nums.end(), [](auto a, auto b) {
            return max(abs(a[0]), abs(a[1])) < max(abs(b[1]), abs(b[0]));
            });
        int ans = 0;
        vector<int>cnt(26, 0);
        for (int i = 0;i < n;i++) {
            cnt[s[nums[i][2]] - 'a']++;
            if (cnt[s[nums[i][2]] - 'a'] >= 2) return ans;

            while (i + 1 < n && max(abs(nums[i][0]), abs(nums[i][1])) == max(abs(nums[i + 1][1]), abs(nums[i + 1][0]))) {
                i++;
                cnt[s[nums[i][2]] - 'a']++;
                if (cnt[s[nums[i][2]] - 'a'] >= 2) return ans;


            }
            ans = i + 1;
        }
        return ans;
    }
};