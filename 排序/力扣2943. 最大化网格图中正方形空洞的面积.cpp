#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {

        sort(hBars.begin(), hBars.end());
        sort(vBars.begin(), vBars.end());
        int cnt1 = 1;
        int tmp = 1;
        for (int i = 1;i < hBars.size();i++) {
            if (hBars[i] == hBars[i - 1] + 1)tmp++;
            else tmp = 1;
            cnt1 = max(tmp, cnt1);
        }
        tmp = 1;
        int cnt2 = 1;
        for (int i = 1;i < vBars.size();i++) {
            if (vBars[i] == vBars[i - 1] + 1)tmp++;
            else tmp = 1;
            cnt2 = max(tmp, cnt2);
        }
        int ans = min(cnt1, cnt2) + 1;
        return ans * ans;
    }
};