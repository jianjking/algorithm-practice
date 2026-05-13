#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minOperations(string word1, string word2) {
        int n = word1.size();
        vector<int>dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0;i < n;i++) {
            vector<vector<int>>cnt(26, vector<int>(26, 0));
            int op1 = 0;


            for (int j = i;j >= 0;j--) {
                int a = word1[j] - 'a';
                int b = word2[j] - 'a';
                if (a != b) {
                    if (cnt[b][a] > 0) {
                        cnt[b][a]--;
                    }
                    else {
                        cnt[a][b]++;
                        op1++;
                    }
                }
                int op2 = 1;
                vector<vector<int>>rev(26, vector<int>(26, 0));
                for (int z = i;z >= j;z--) {
                    int c = word1[z] - 'a';
                    int d = word2[j + i - z] - 'a';
                    if (c != d) {
                        if (rev[d][c] > 0) {
                            rev[d][c]--;
                        }
                        else {
                            rev[c][d]++;
                            op2++;
                        }
                    }
                }
                dp[i + 1] = min(dp[i + 1], dp[j] + min(op1, op2));
            }


        }
        return dp[n];
    }
};