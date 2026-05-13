#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Solution {
public:
    int f(vector<vector<int>>& dp, int i, int status, int num, vector<int>& arr) {
        if (status == num)return 0;
        if (i == dp.size())return INT_MAX;
        if (dp[i][status] != -1)return dp[i][status];
        int p1 = f(dp, i + 1, status, num, arr);
        int p2 = f(dp, i + 1, status | arr[i], num, arr);
        if (p2 != INT_MAX)p2++;
        dp[i][status] = min(p1, p2);
        return min(p1, p2);
    }
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        map<string, int>graph;
        int n = req_skills.size();
        for (int i = 0;i < n;i++) {
            graph[req_skills[i]] = i;
        }
        int status = (1 << n) - 1;
        int m = people.size();
        vector<int>arr(m, 0);
        for (int i = 0;i < m;i++) {
            int a = 0;
            for (auto& p : people[i]) {
                if (graph.find(p) != graph.end()) {
                    a = a | (1 << graph[p]);
                }
                arr[i] = a;
            }
        }
        vector<vector<int>>dp(m, vector<int>((1 << n) - 1, -1));
        int k = f(dp, 0, 0, status, arr);
        vector<int>ans;
        for (int i = 0, j = 0;j != status;i++) {
            if (i == m - 1 || dp[i + 1][j] != dp[i][j]) {
                j |= arr[i];
                ans.push_back(i);
            }
        }
        return ans;
    }
};