#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int ans;
    void dfs(int remain,int pre,int n,int m, vector<vector<int>>& matrix, vector<int>& cnt) {
        if (remain == 0) {
            int tmp = 0;
            for (int i = 0;i < n;i++)if (cnt[i] == 0)tmp++;
            ans = max(ans, tmp);
            return;
        }
        if (pre == m)return;
        for (int i = pre;i < m;i++) {
            for (int j = 0;j < n;j++) {
                if (matrix[j][i] == 1)cnt[j]--;
            }
            dfs(remain - 1, i+1,n, m, matrix, cnt);
            for (int j = 0;j < n;j++) {
                if (matrix[j][i] == 1)cnt[j]++;
            }
        }
    }
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        int n = matrix.size();
        ans = 0;
        int m = matrix[0].size();
        vector<int>cnt(n,0);
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                if (matrix[i][j] == 1)cnt[i]++;
            }
        }
        dfs(numSelect, 0,n,m,matrix, cnt);
        return ans;
    }
};