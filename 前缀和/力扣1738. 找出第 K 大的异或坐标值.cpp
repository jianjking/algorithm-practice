#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int>nums;
        nums.reserve(n * m);
        vector<vector<int>>pre(n + 1, vector<int>(m + 1, 0));
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                pre[i][j] = pre[i - 1][j] ^ pre[i][j - 1] ^ pre[i - 1][j - 1] ^ matrix[i - 1][j - 1];
                nums.push_back(pre[i][j]);
            }
        }
        sort(nums.begin(), nums.end(), [&](auto a, auto b) {
            return a > b;
            });
        return nums[k - 1];
    }
};