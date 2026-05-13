#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int q = queries.size();
        int L = nums[0].size();         // 每个数字字符串的长度
        vector<int> ans(q);

        for (int qi = 0; qi < q; qi++) {
            int k = queries[qi][0];     // 要选第 k 小
            int trim = queries[qi][1];  // 截取后缀长度 trim

            // 构造一个 index 数组 [0,1,2,…,n-1]
            vector<int> idx(n);
            iota(idx.begin(), idx.end(), 0);

            // 对下标数组按对应后缀字符串排序
            sort(idx.begin(), idx.end(), [&](int a, int b) {
                // 取 nums[a] 和 nums[b] 的后缀 trim 个字符
                // substr(pos, len)：从 pos 开始，长度 len
                const string& sa = nums[a];
                const string& sb = nums[b];
                for (int i = L - trim;i < L;i++) {
                    if (sa[i] != sb[i])return sa[i] < sb[i];
                }
                return a < b;
                });

            ans[qi] = idx[k - 1];  // 取第 k 小的下标
        }

        return ans;
    }
};
//增量排序记得用stable_sort
class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        int l = nums[0].size();
        int n = queries.size();
        vector<int>f(n);
        vector<int>ans(n);
        iota(f.begin(), f.end(), 0);
        vector<int>tong(nums.size());
        int m = nums.size();
        iota(tong.begin(), tong.end(), 0);
        sort(f.begin(), f.end(), [&](auto a, auto b) {
            return queries[a][1] < queries[b][1];
            });
        int cnt = 1;
        sort(tong.begin(), tong.end(), [&](auto a, auto b) {
            if (nums[a][l - 1] != nums[b][l - 1])return nums[a][l - 1] < nums[b][l - 1];
            return a < b;
            });
        for (int i = 0;i < n;i++) {
            int a = queries[f[i]][0];
            int b = queries[f[i]][1];
            while (cnt < b) {
                ++cnt;
                stable_sort(tong.begin(), tong.end(), [&](auto a, auto b) {
                    return nums[a][l - cnt] < nums[b][l - cnt];

                    });
            }
            ans[f[i]] = tong[a - 1];
        }
        return ans;
    }
};