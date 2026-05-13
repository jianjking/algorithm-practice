#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0)return 1;
        if (n == 1)return 10;
        int ans = 10;
        for (int s = 9, a = 9, i = n;i > 1;i--, a--) {
            s *= a;
            ans += s;
        }
        return ans;
    }
};