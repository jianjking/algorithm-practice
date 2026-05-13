#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxJump(vector<int>& stones) {
        int ans = INT_MIN;
        int n = stones.size();
        for (int i = 0; i < n; i += 2) {
            if (i + 2 < n) {
                ans = max(ans,stones[i + 2] - stones[i]);
            }
            else {
                ans = max(ans, stones[n - 1] - stones[i]);
            }
        }
        for (int i = 1; i < n; i += 2) {
            if (i + 2 < n) {
                ans = max(ans, stones[i + 2] - stones[i]);
            }
            else {
                ans = max(ans, stones[n - 1] - stones[i]);
            }
        }
        return ans;
    }
};