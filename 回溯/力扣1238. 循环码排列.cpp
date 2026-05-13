#include<iostream>
#include<vector>
using namespace std;
bool used[1 << 16];  // 最多 2^16 个节点

class Solution {
public:
    vector<int> ans;

    vector<int> circularPermutation(int n, int start) {
        vector<int> path;
        memset(used, 0, sizeof(used));

        path.push_back(start);
        used[start] = true;

        dfs(n, path);
        return ans;
    }

    bool dfs(int n, vector<int>& path) {
        // 出口：路径长度够了
        if (path.size() == (1 << n)) {
            // 检查首尾是否相邻（只差一位）
            int x = path.back() ^ path[0];
            if ((x & (x - 1)) == 0) {
                ans = path;
                return true;
            }
            return false; // 否则回溯
        }

        int pre = path.back();
        for (int i = 0; i < n; i++) {
            int cur = pre ^ (1 << i);  // 翻转第 i 位
            if (!used[cur]) {
                used[cur] = true;
                path.push_back(cur);

                if (dfs(n, path)) return true;

                path.pop_back();
                used[cur] = false;
            }
        }
        return false;
    }
};
