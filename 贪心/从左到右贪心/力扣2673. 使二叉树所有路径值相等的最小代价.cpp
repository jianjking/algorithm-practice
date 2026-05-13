#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minIncrements(int n, vector<int>& cost) {
        for (int i = 1;i < n;i++) {
            cost[i] += cost[(i - 1) / 2];
        }
        int ans = 0;
        for (int i = (n - 1) / 2 - 1;i >= 0;i--) {
            ans += abs(cost[2 * i + 1] - cost[2 * i + 2]);
            cost[i] = max(cost[2 * i + 2], cost[2 * i + 1]);
        }
        return ans;
    }
};