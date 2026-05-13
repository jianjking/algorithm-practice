#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    double d(int i, int j, int a, int b) {
        int c = abs(i - a);
        int d = abs(j - b);
        return sqrt(c * c + d * d);
    }
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        int n = towers.size();
        int x1 = 0;
        int y1 = 0;
        int ans = 0;
        for (int i = 0;i <= 50;i++) {
            for (int j = 0;j <= 50;j++) {
                int sum = 0;
                for (int z = 0;z < n;z++) {
                    int a = towers[z][0];
                    int b = towers[z][1];
                    int c = towers[z][2];
                    if (d(i, j, a, b) <= radius) {
                        sum += (int)(((double)c) / ((double)1 + d(i, j, a, b)));
                    }
                }
                if (sum > ans) {
                    x1 = i;
                    y1 = j;
                    ans = sum;
                }
                else if (sum == ans) {
                    if (x1 > i || (x1 == i && y1 > j)) {
                        x1 = i;
                        y1 = j;
                    }
                }
            }
        }
        return { x1,y1 };
    }
};