#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int mx;
    void dfs(int i, int n, vector<string>& arr, int status) {
        if (i == n) {
            int tmp = 0;

            for (int i = 0;i < 26;i++) {
                if ((status >> i & 1) == 1)tmp++;
            }
            mx = max(mx, tmp);
            return;
        }
        bool choice = true;
        dfs(i + 1, n, arr, status);
        for (auto& p : arr[i]) {
            int a = p - 'a';
            if ((status >> a & 1) == 1) { choice = false;break; }
            status |= (1 << a);
        }
      
        if (choice) {
            dfs(i + 1, n, arr, status);
        }
    }
    int maxLength(vector<string>& arr) {
        int n = arr.size();
        mx = 0;
        dfs(0, n, arr, 0);
        return mx;
    }
};