#include<iostream>
#include<vector>
using namespace std;
vector<int>mx;
int n;
int query(int x, int y, int l, int r, int nums) {
    if (x <= l && y >= r) {
        return mx[nums];
    }
    else {
        int ans = INT_MIN;
        int mid = l + (r - l) / 2;
        if (x <= mid)ans = max(ans, query(x, y, l, mid, 2 * nums));
        if (y > mid)ans = max(ans, query(x, y, mid + 1, r, 2 * nums + 1));
        return ans;
    }
}
void update(int target, int l, int r, int v, int nums) {
    if (l == r) {
        mx[nums] = v;
        return;
    }
    else {
        int mid = l + (r - l) / 2;
        if (target <= mid)update(target, l, mid, v, 2 * nums);
        else update(target, mid + 1, r, v, 2 * nums + 1);
        mx[nums] = max(mx[2 * nums], mx[2 * nums + 1]);
    }
}
class Solution {
public:
    int longestIdealString(string s, int k) {
        mx.assign(4 * 26 + 1, 0);
        int ans = 0;
        n = s.size();
        for (int i = 0; i < n; i++) {
            int mid = s[i] - 'a' + 1;
            int l = max(1, mid - k);
            int r = min(26, mid + k);
            int len = query(l, r, 1, 26, 1) + 1;
            ans = max(ans, len);
            update(mid, 1, 26, len, 1);
        }
        return ans;
    }
};