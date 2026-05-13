#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());
        int l = 0, r = tokens.size() - 1;
        int score = 0, best = 0;
        while (l <= r) {
            if (power >= tokens[l]) {
                // 用最小的那张换分
                power -= tokens[l++];
                score++;
                best = max(best, score);
            }
            else if (score > 0) {
                // 分换能量：舍弃一分拿回最大的能量
                power += tokens[r--];
                score--;
            }
            else {
                break;
            }
        }
        return best;
    }

};