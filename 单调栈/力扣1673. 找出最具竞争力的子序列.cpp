#include<iostream>
#include<vector>
#include<stack>
using namespace std;
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        stack<int> st;

        for (int i = 0; i < n; ++i) {
            // 还能凑满 k，就弹掉更大的
            while (!st.empty() && nums[i] < st.top()
                && (int)st.size() - 1 + (n - i) >= k) {
                st.pop();
            }
            // 只在还没满 k 时才压栈，避免“栈太长、最后丢前面小数”
            if ((int)st.size() < k) st.push(nums[i]);
        }

        // 从栈里倒回，恢复原序
        vector<int> ans(k);
        for (int i = k - 1; i >= 0; --i) {
            ans[i] = st.top();
            st.pop();
        }
        return ans;
    }
};
