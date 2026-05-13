#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        vector<int>dp(n + 1, 0);
        dp[1] = 2;
        int weight = boxes[0][1];
        int trip = 2;
        for (int l = 0, r = 1;r < n;r++) {
            if (boxes[r][0] != boxes[r - 1][0]) {
                trip++;
               
                
            }
            weight += boxes[r][1];
            while (r - l + 1 > maxBoxes || weight > maxWeight || dp[l] == dp[l + 1]) {
                weight -= boxes[l++][1];
                if (boxes[l - 1][0] != boxes[l][0])trip--;
            }
            dp[r+1] = dp[l]+trip;
        }
        return dp[n];
    }
};