#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(), costs.end());
        int n = costs.size();
        int ans = 0;
        for (int i = 0;i < n;i++) {
            if (coins >= costs[i]) {
                coins -= costs[i];
            }
            if (coins <= 0) {
                return ans;
            }
        }
        return ans;
    }
};