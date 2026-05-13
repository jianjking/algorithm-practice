#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double r = 2 * 1e9;
        double l = 0;
        double ans;
        int n = squares.size();

        for (int i = 0;i < 50;i++) {
            double mid = l + (r - l) / 2;
            double sum1 = 0;
            double sum2 = 0;
            for (int j = 0;j < n;j++) {
                int x1 = squares[i][0];
                int y1 = squares[i][1];
                int x2 = x1 + squares[i][2];
                int y2 = y1 + squares[i][2];
                if (mid <= y1) {
                    sum1 += (y2 - y1) * (x2 - x1);
                }
                else if (mid >= y2) {
                    sum2 += (y2 - y1) * (x2 - x1);
                }
                else{
                    sum1 += (y2 - mid) * (x2 - x1);
                    sum2 += (mid - y1) * (x2 - x1);
                }
                if (sum1 == sum2) {
                    ans = mid;
                    r = mid;
                }
                else if (sum1 < sum2) {
                    l = mid;
                }
                else {
                    r = mid - 1;
                }
            }
        }
        return ans;
    }
};