#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        int n = rocks.size();
        vector<int>d(n);
        for (int i = 0;i < n;i++)d[i] = capacity[i] - rocks[i];
        sort(d.begin(), d.end());
        int ans = 0;
        for (int i = 0;i < n;i++)
        {
            additionalRocks -= d[i];
            if (additionalRocks >= 0)ans++;
            else break;
        }
        return ans;
    }
};