#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    //蚂蚁相撞之后，双双调转方向等于不掉转方向，因为求的是最后蚂蚁的时间
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int mx = INT_MIN;
        for (auto& p : left) {
            mx = max(mx, p);
        }
        for (auto& p : right) {
            mx = max(mx, n - p);
        }
        return mx;
    }
};