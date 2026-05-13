#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool dfs(const string& s, int idx, vector<int>& seq) {
        const int n = s.size();
        if (idx == n) return seq.size() >= 3;

        long long cur = 0;
        for (int i = idx; i < n; ++i) {
            // 前导零：如果以 '0' 开头，只允许取单个 0
            if (i > idx && s[idx] == '0') break;

            cur = cur * 10 + (s[i] - '0');
            if (cur > INT_MAX) break;
            int x = (int)cur;

            int m = seq.size();
            if (m >= 2) {
                long long need = (long long)seq[m - 2] + seq[m - 1];
                if (x < need) continue;   // 还不够，大胆多取一位
                if (x > need) break;      // 超了，再取只会更大，直接剪枝
            }
            seq.push_back(x);
            if (dfs(s, i + 1, seq)) return true;
            seq.pop_back();
        }
        return false;
    }

    vector<int> splitIntoFibonacci(string s) {
        vector<int> seq;
        dfs(s, 0, seq);
        return seq;
    }
};
