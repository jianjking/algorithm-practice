#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        vector<int>l(n, 0);
        vector<int>r(n, 0);
        int cnt = 1;
        for (int i = 1;i < n;i++) {
            l[i] = cnt;
            if (security[i] <= security[i - 1])cnt++;
            else cnt = 1;
        }
        cnt = 1;
        for (int i = n - 2;i >= 0;i--) {
            r[i] = cnt;
            if (security[i + 1] >= security[i])cnt++;
            else cnt = 1;
        }
        vector<int>ans;

        for (int i = time;i < n - time;i++) {
            if (l[i] >= time && r[i] >= time && (time == 0 || (security[i] <= security[i - 1] && security[i + 1] >= security[i])))ans.push_back(i);
        }
        return ans;
    }
};