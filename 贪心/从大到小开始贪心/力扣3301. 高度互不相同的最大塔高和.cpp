#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long maximumTotalSum(vector<int>& maximumHeight) {
        sort(maximumHeight.begin(), maximumHeight.end(), [](int a, int b) {
            return a > b;
            });
        int n = maximumHeight.size();
        long long ans = maximumHeight[0];
        int tmp = maximumHeight[0];
        for (int i = 1;i < n;i++) {
            tmp = min(tmp - 1, maximumHeight[i]);
            if (tmp <= 0)return -1;
            ans += tmp;
        }
        return ans;
    }
};