#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
class Solution {
public:
    long long dist(int i, int j, vector<int>& robot, vector<vector<int>>& factory) {
        return llabs(robot[i] - factory[j][0]);
    }

    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        int m = robot.size(), n = factory.size();
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end(), [](auto& a, auto& b) { return a[0] < b[0]; });

        const long long INF = LLONG_MAX / 4;
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INF));
        for (int i = 0; i <= n; i++) dp[i][0] = 0;

        for (int i = 1; i <= n; i++) {
            // 1) 准备前缀和 sum[0..m]
            vector<long long> sum(m + 1, 0);
            for (int j = 1; j <= m; j++) {
                sum[j] = sum[j - 1] + dist(j - 1, i - 1, robot, factory);
            }

            deque<int> q;
            for (int j = 1; j <= m; j++) {
                // 不选第 i 个厂，继承上一行
                dp[i][j] = dp[i - 1][j];

                // 只要 dp[i-1][j-1] 可达，就把 j-1 这个候选插入队列
                if (dp[i - 1][j - 1] < INF) {
                    // value = dp[i-1][k] - sum[k]
                    long long val = dp[i - 1][j - 1] - sum[j - 1];
                    while (!q.empty() && (dp[i - 1][q.back()] - sum[q.back()]) >= val) {
                        q.pop_back();
                    }
                    q.push_back(j - 1);
                }

                // 踢出“分配数量超过容量”的 k
                int cap = factory[i - 1][1];
                while (!q.empty() && q.front() < j - cap) {
                    q.pop_front();
                }

                // 用队头 k 更新 dp
                if (!q.empty()) {
                    int k = q.front();
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] - sum[k] + sum[j]);
                }
            }
        }

        return dp[n][m];
    }
};
