#include<iostream>
#include<vector>
using namespace std;
// dp[i][j]为你现在能扔几次，并且手里有几个蛋。
//因为必须要测出来不能赌，所以我们要知道这个蛋如果碎了能测几层楼,也就是dp[i-1][j-1]
//如果不在这层扔的话，在下面扔就不是最高的楼层，如果不碎的话可以向上扔dp[i][j-1]层
class Solution {
public:
    int superEggDrop(int k, int n) {
        vector<vector<int>>dp(n + 1, vector<int>(k + 1, 0));
        for (int i = 1;i <= n;i++) {
            dp[i][1] = i;
        }
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= k;j++) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + 1;
                if (dp[i][j] >= n)return i;
            }
        }
        return n;
    }
};