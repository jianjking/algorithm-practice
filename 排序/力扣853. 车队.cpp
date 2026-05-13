#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;
struct node {
    int place;
    double time;
};
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<node>t(n);
        int a = INT_MIN;
        double limit = 0;
        for (int i = 0;i < n;i++) {
            t[i].place = position[i];
            t[i].time = (double)(target - position[i]) / speed[i];
        }
        sort(t.begin(), t.end(), [&](auto a, auto b) {
            return a.place < b.place;
            });
        int ans = n;
        for (int i = n - 1;i > 0;i--) {
            if (t[i - 1].time <= t[i].time) {
                ans--;
                t[i - 1].time = t[i].time;
            }
        }
        return ans;
    }
};