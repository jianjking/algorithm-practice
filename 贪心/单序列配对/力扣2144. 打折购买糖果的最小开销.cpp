#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minimumCost(vector<int>& cost) {
        sort(cost.begin(), cost.end(), [](int a, int b) {
            return a > b;
            });
        int ans = 0;
        int n = cost.size();
        for (int i = 0;i < n;i++) {
            if ((i - 2) % 3) {
                ans += cost[i];
            }
        }
        return ans;
    }
};
