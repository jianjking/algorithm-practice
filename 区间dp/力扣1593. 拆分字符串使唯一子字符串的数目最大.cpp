#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    unordered_map<string, int>f;
    int dfs(int r, string& s) {
        if (r < 0)return 0;
        if (r == 0) {
            string s1;
            s1 += s[r];
            return f[s1] == 0 ? 1 : INT_MIN / 2;
        }
        string s1;
        int cnt = 0;
        for (int i = r;i >= 0;i--) {
            s1 += s[i];
            if (f[s1] == 1) {
                continue;
            }
            f[s1]++;
            cnt = max(cnt, 1 + dfs(i - 1, s));
            f[s1]--;
        }
        return cnt;
    }
    int maxUniqueSplit(string s) {
        int n = s.size();
        return dfs(n - 1, s);
    }
};