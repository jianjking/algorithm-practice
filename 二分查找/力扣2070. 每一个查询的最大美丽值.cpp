#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int find(int target, int l, int r, vector<vector<int>>& items) {
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (items[mid][0] <= target) {
                ans = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        return ans;
    }
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        sort(items.begin(), items.end(), [&](auto a, auto b) {
            return a[0] < b[0];
            });
        int n = items.size();
        vector<int>cnt(n);
        int mx = items[0][1];
        for (int i = 0;i < n;i++) {
            mx = max(mx, items[i][1]);
            cnt[i] = mx;
        }
        int m = queries.size();
        vector<int>ans(m,-1);
        for (int i = 0;i < m;i++) {
            int num = find(queries[i], 0, n - 1, items);
            if (num == -1)continue;
            ans[i] = cnt[num];
        }
        return ans;
    }
};