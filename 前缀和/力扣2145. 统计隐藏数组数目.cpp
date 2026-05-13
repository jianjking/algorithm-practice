#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        int i = lower;
        int r = upper;
        int n = differences.size();
        long long min1 = 0;
        long long max1 = 0;
        long long cnt = 0;
        for (int i = 0;i < n;i++) {
            cnt += differences[i];
            min1 = min(min1, cnt);
            max1 = max(max1, cnt);
        }
        return upper - max1 + min1 - lower >= 0 ? upper - max1 + min1 - lower + 1 : 0;
    }
};