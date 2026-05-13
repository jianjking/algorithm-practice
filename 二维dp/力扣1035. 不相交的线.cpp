#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    int maxUncrossedLines(vector<int>& s, vector<int>& t) {
        int n = s.size(), m = t.size();
        vector<vector<int>> memo(n, vector<int>(m, -1)); // -1 表示没有计算过
        auto dfs = [&](auto&& dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                return 0;
            }
            int& res = memo[i][j]; // 注意这里是引用
            if (res != -1) { // 之前计算过
                return res;
            }
            if (s[i] == t[j]) {
                return res = dfs(dfs, i - 1, j - 1) + 1;
            }
            return res = max(dfs(dfs, i - 1, j), dfs(dfs, i, j - 1));
            };
        return dfs(dfs, n - 1, m - 1);
    }
};
