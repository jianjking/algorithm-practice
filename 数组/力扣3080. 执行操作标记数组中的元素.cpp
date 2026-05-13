#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<long long> unmarkedSumArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int m = queries.size();
        vector<long long>ans(m);
        vector<int>num(n);
        vector<bool>visit(n, false);
        long long sum = 0;
        for (int i = 0;i < n;i++) {
            num[i] = i;
            sum += nums[i];
        }
        sort(num.begin(), num.end(), [&](int a, int b) {
            return nums[a] < nums[b];
            });
        int l = 0;
        for (int i = 0;i < m;i++) {
            int a = queries[i][0];
            int b = queries[i][1];
            if (!visit[a]) {
                visit[a] = true;
                sum -= nums[a];
            }
            for (int j = 0;l < n && j < b;l++) {
                if (visit[num[l]])continue;
                else {
                    sum -= nums[num[l]];
                    visit[num[l]] = true;
                    j++;
                }
            }
            ans[i] = sum;
        }
        return ans;
    }
};
int main() {
    Solution a;
    vector<int>nums = { 9, 9, 9, 9, 9, 14, 17, 3, 15, 15, 4, 17, 19, 11, 9, 15, 9, 4, 10
    };
    vector<vector<int>>q = { {13,3},{15,2},{12,2},{4,3} };
    vector<long long>ans = a.unmarkedSumArray(nums, q);
    for (int i = 0;i < ans.size();i++)cout << ans[i] << " ";
}