#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
            });
        int ans = 1;
        int n = points.size();
        int sum = points[0][0]+w;
        for (int i = 0;i < n;i++) {
            if (points[i][0] > sum) {
                sum = points[i][0] + w;
                ans++;
            }

        }
        return ans;
    }
};