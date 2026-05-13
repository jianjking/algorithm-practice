#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        long long ans = 0;
        int mx = INT_MIN;
        for (auto& p : milestones) {
            mx = max(mx, p);
            ans += p;
        }
        if (ans - mx >= mx)return ans;
        return ans - (mx - (ans - mx)) + 1;
    }
};