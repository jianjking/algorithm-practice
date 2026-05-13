#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
static int a;
static int b;
void queriry(int c, vector<int>& tree1, vector<int>& tree2) {
    a = b = 0;
    while (c > 0) {
        if (a < tree1[c]) {
            a = tree1[c];
            b = tree2[c];
        }
        else if (a == tree1[c]) {
            b += tree2[c];
        }
        c -= (c & -c);
    }
}
void add(int c, vector<int>& tree1, vector<int>& tree2) {
    int n = tree1.size();
    while (c < n) {
        if (a + 1 > tree1[c]) {
            tree1[c] = a + 1;
            tree2[c] = a == 0 ? 1 : b;
        }
        else if (a + 1 == tree1[c]) {
            tree2[c] += a == 0 ? 1 : b;
        }
        c += c & (-c);
    }
}
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int ans1 = 0;
        int ans2 = 0;
        vector<int>tmp = nums;
        int n = nums.size();
        sort(tmp.begin(), tmp.end());
        auto p2 = unique(tmp.begin(), tmp.end());
        tmp.erase(p2, tmp.end());
        for (int i = 0;i < n;i++) {
            nums[i] = lower_bound(tmp.begin(), tmp.end(), nums[i]) - tmp.begin() + 1;
        }
        int m = tmp.size();
        vector<int>tree1(m + 1, 0);
        vector<int>tree2(m + 1, 0);
        for (int i = 0;i < n;i++) {
            queriry(nums[i] - 1, tree1, tree2);
            if (a + 1 > ans1) {
                ans2 = a == 0 ? 1 : b;
                ans1 = a + 1;
            }
            else if (a + 1 == ans1) {
                ans2 += a + 1 == 1 ? 1 : b;
            }
            add(nums[i], tree1, tree2);
        }
        return ans2;
    }
};