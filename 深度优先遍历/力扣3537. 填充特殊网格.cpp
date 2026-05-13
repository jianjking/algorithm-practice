#include<iostream>
#include<vector>
using namespace std;
int val;
class Solution {
public:
    void dfs(int i, int j, int wid, vector<vector<int>>& num) {
        if (wid == 1) {
            num[i][j] = val--;
            return;
        }
        dfs(i, j, wid / 2, num);
        dfs(i + wid / 2, j, wid / 2, num);
        dfs(i + wid / 2, j + wid / 2, wid / 2, num);
        dfs(i, j + wid / 2, wid / 2, num);
    }
    vector<vector<int>> specialGrid(int n) {
        val = (1 << 2 * n) - 1;
        int m = (1 << n);
        vector<vector<int>>num(m, vector<int>(m));
        dfs(0, 0, m, num);
        return num;
    }
};