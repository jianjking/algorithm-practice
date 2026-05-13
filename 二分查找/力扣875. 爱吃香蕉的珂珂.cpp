#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool  check(int speed, vector<int>& piles, int h) {
        for (auto& p : piles) {
            h -= (p + speed - 1) / speed;
        }
        return h >= 0;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int mx = INT_MIN;
        for (auto& p : piles) {
            mx = max(mx, p);
        }
        int mn = 1;
        int ans;
        while (mn <= mx) {
            int mid = mn + (mx - mn) / 2;
            if (check(mid, piles, h)) {
                ans = mid;
                mx = mid - 1;
            }
            else {
                mn = mid + 1;
            }
        }
        return ans;
    }
};