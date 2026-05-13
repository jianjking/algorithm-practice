#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long minCuttingCost(int n, int m, int k) {
        long long ans = 0;
        while (n > k) {
            ans += k * (n - k);
            n -= k;
        }
        while (m > k) {
            ans += m * (m - k);
            m -= k;
        }
        return ans;
    }
};