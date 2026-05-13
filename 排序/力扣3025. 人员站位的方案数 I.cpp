#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [&](auto a, auto b) {
           if(a[0]!=b[0]) return a[0] < b[0];
           return a[1] > b[1];
            });
        int n = points.size();
        int cnt = 0;
        for (int i = 0;i < n;i++) {
            int y0 = points[i][1];
            int x0 = points[i][0];
            int mx = INT_MIN;
            for (int j = i + 1;j < n;j++) {
                int y = points[j][1];
                int x = points[j][0];
                if (y<y0 && x>x0 && y > mx)cnt++;
                mx = max(y, mx);
            }
        }
        return cnt;
    }
};