#include<iostream>
#include<vector>
#include<array>
using namespace std;
class Solution {
public:
    static vector<vector<int>> arr;
    static vector<int>          goal;
    int cnt;

    void construct(const string& p) {
        int tmp = 0;
        int n = p.size();
        for (int i = 0; i < n; ++i) {
            int c = p[i] - 'a';
            if (arr[tmp][c] == 0)
                arr[tmp][c] = cnt++;
            tmp = arr[tmp][c];
            goal[tmp]++;
        }
    }

    void cal(vector<int>& ans, int idx, const string& p) {
        int tmp = 0;
        for (char ch : p) {
            tmp = arr[tmp][ch - 'a'];
            ans[idx] += goal[tmp];
        }
    }

    vector<int> sumPrefixScores(vector<string>& words) {
        arr.assign(100005, vector<int>(26, 0));
        goal.assign(100005, 0);
        cnt = 1;

        for (auto& w : words)
            construct(w);

        vector<int> ans(words.size());
        for (int i = 0; i < (int)words.size(); ++i)
            cal(ans, i, words[i]);
        return ans;
    }
};

// 别忘了这一对定义！
vector<vector<int>> Solution::arr;
vector<int>          Solution::goal;
