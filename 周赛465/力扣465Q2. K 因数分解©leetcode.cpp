#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    void dfs(int n, int k, int mn, int mx, int& cur, vector<int>& tmp, vector<int>& ans) {
        if (k == 0) {
            if (n != 1)return;
            if (cur < mx - mn)return;
            ans = tmp;
            cur = mx - mn;
        }
        else {
            for (int i = 1; i <= sqrt(n); i++) {
                if (n % i == 0) {
                    int a = n / i;
                    int c = mn;
                    int d = mx;
                    mn = min(mn, i);
                    mx = max(mx, i);
                    tmp.push_back(i);
                    dfs(a, k - 1, mn, mx, cur, tmp, ans);
                    tmp.pop_back();
                    mn = c;
                    mx = d;
                    mn = min(mn, a);
                    mx = max(mx, a);
                    tmp.push_back(a);
                    dfs(i, k - 1, mn, mx, cur, tmp, ans);
                    mn = c;
                    mx = d;
                    tmp.pop_back();
                }
            }
        }
    }
    vector<int> minDifference(int n, int k) {
        vector<int>ans(k);
        int cur = INT_MAX;
        vector<int>tmp;
        dfs(n, k, INT_MAX, INT_MIN, cur, tmp, ans);
        return ans;
    }
}; 