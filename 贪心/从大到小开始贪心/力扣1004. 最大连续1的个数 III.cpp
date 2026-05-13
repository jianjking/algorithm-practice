#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        sort(horizontalCut.begin(), horizontalCut.end(), [](auto a, auto b) {
            return a > b;
            });
        sort(verticalCut.begin(), verticalCut.end(), [](auto a, auto b) {
            return a > b;
            });

        int l = 0;
        int r = 0;
        int ans = 0;
        while (l < m - 1 && r < n - 1) {
            if (horizontalCut[l] > verticalCut[r]) {
                ans += horizontalCut[l] * (r + 1);
                l++;
            }
            else {
                ans += verticalCut[r] * (l + 1);
                r++;
            }
        }
        while (l < m - 1) {
            ans += horizontalCut[l++] * (r + 1);
        }
        while (r < n - 1) {
            ans += verticalCut[r++] * (l + 1);
        }
        return ans;
    }
};
