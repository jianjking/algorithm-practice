#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minOperations(int n) {
        int ans = 1;
        while (n & (n - 1)) {
            int d = n & (-n);
            if (n & (d << 1))n += d;
            else n -= d;
            ans++;
        }
        return ans;
    }
};