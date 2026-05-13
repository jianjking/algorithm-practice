#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int value(vector<int>& values, int i) {
        return values[i] + i;
    }
    int maxScoreSightseeingPair(vector<int>& values) {
        deque<int>f;
        int n = values.size();
        int ans = 0;
        for (int i = 1;i < n;i++) {
            while (!f.empty() && value(values, i - 1) >= value(values, f.back()))f.pop_back();
            f.push_back(i - 1);
            ans = max(ans, value(values, f.front()) + values[i] - i);
        }
        return ans;
    }
};