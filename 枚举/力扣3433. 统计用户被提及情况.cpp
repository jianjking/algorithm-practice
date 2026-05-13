#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<int> countMentions(int n, vector<vector<string>>& events) {
        vector<int>ans(n, 0);
        vector<int>cnt(n, 0);
        sort(events.begin(), events.end(), [&](vector<string>& a, vector<string>& b) {
            int time1 = 0;
            for (int j = 0;j < a[1].size();j++) {
                time1 = time1 * 10 + a[1][j] - '0';
            }
            int time2 = 0;
            for (int j = 0;j < b[1].size();j++) {
                time2 = time2 * 10 + b[1][j] - '0';
            }
            if (time1 != time2)return time1 < time2;
            return a[0][0] > b[0][0]; 
            });

        int m = events.size();
        for (int i = 0;i < m;i++) {
            if (events[i][0] == "MESSAGE") {
                int time = 0;
                for (int j = 0;j < events[i][1].size();j++) {
                    time = time * 10 + events[i][1][j]-'0';
                }
                if (events[i][2][0] == 'A') {
                    for (int j = 0;j < n;j++) {
                        ans[j]++;
                    }
                }
                else if (events[i][2][0] == 'H') {
                    for (int j = 0;j < n;j++) {
                        if (cnt[j] <= time)ans[j]++;
                    }
                }
                else {
                    int tmp = 0;
                    for (auto& p : events[i][2]) {
                        if (p >= '0' && p <= '9') {
                            tmp = tmp * 10 + p - '0';
                        }
                        if (p == ' ') {
                            ans[tmp]++;
                            tmp = 0;
                        }
                    }
                    ans[tmp]++;
                }
            }
            else {
                int time = 0;
                for (int j = 0;j < events[i][1].size();j++) {
                    time = time * 10 + events[i][1][j] - '0';
                }
                int tmp = 0;
                for (auto& p : events[i][2]) {
                    if (p >= '0' && p <= '9') {
                        tmp = tmp * 10 + p - '0';
                    }
                }
                cnt[tmp] = time + 60;
            }
        }
        return ans;
    }
};