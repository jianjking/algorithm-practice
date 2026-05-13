#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        sort(answers.begin(), answers.end());
        int ans = answers[0] + 1;
        int n = answers.size();
        int cnt = 1;
        for (int i = 1;i < n;i++) {
            if (cnt <= answers[i] && answers[i - 1] == answers[i]) {
                cnt++;
            }
            else {
                cnt = 1;
                ans += answers[i] + 1;
            }
        }

        return ans;
    }
};