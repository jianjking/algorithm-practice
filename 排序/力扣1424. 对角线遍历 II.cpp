#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        map<int, vector<int>> mp;
        /* 从最后一行开始存储数据, 利用map有序的特点 */
        for (int i = nums.size() - 1; i >= 0; i--) {
            for (int j = 0; j < nums[i].size(); j++) {
                mp[i + j].push_back(nums[i][j]);
            }
        }
        vector<int> ans;
        /* 顺序输出即为题目要求的 */
        for (auto& [k, v] : mp) {
            for (auto val : v) {
                ans.push_back(val);
            }
        }
        return ans;
    }
};
