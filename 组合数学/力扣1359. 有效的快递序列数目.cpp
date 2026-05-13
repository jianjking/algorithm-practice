#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int countOrders(int n) {
        if (n == 1)return 1;
        long long cnt = 1;
        for (int i = 2;i <= n;i++) {
            cnt = (cnt * (2 * i - 1) * i) % mod;
        }
        return cnt % mod;
    }
};