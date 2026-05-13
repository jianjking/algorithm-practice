#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)res = ((long long)res * a) % mod;
        a = ((long long)a * a) % mod;
        b >>= 1;
    }
    return res;
}
class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        vector<int>jie(n + 1);
        jie[1] = 1;
        for (int i = 2;i <= n;i++) {
            jie[i] = ((long long)i * jie[i - 1]) % mod;
        }
        vector<int>lve(n + 1);
        lve[n] = power(jie[n], mod - 2);
        for (int i = n - 1;i >= 1;i--) {
            lve[i] = ((long long)(i + 1) * lve[i + 1]) % mod;
        }
        lve[0] = 1;
        long long cur, ans = 0, sign = 1;
        for (int i = 0; i < n - k; i++, sign = sign == 1 ? (mod - 1) : 1) {
            cur = (sign * power(n - i - k, goal - k)) % mod;
            cur = (cur * jie[n]) % mod;
            cur = (cur * lve[i]) % mod;
            cur = (cur * lve[n - i - k]) % mod;
            ans = (ans + cur) % mod;
        }
        return (int)ans;

    }
};