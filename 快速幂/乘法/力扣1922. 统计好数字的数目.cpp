#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
long long mi(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1 == 1)res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
class Solution {
public:
    int countGoodNumbers(long long n) {

        long long m1 = n % 2 == 0 ? n / 2 : (n + 1) / 2;
        long long m2 = n / 2;
        return (mi(5, m1) * mi(4, m2)) % mod;

    }
};