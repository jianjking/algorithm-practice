#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int f(int tail, int mi) {
        int ans = 1;
        int x = tail;
        while (mi > 0) {
            if (mi & 1 > 0)
                ans = ((long long)ans * x) % mod;
            x = ((long long)x * x) % mod;
            mi >>= 1;
        }
        return ans;
    }
    int cuttingBamboo(int n) {
        if (n == 2)return 1;
        if (n == 3)return 2;
        // n=4=2*2;
        //n=5=3*2;
        //n=6=3*3;
        //n=7=3*2*2;
        //n=8=3*3*2;
        //n=9=3*3*3;
        //........
        int tail = n % 3 == 0 ? 1 : (n % 3 == 1 ? 4 : 2);
        int mi = (tail == 1 ? n : (n - tail)) / 3;
        return ((long long)f(3, mi) * tail) % mod;
    }
};