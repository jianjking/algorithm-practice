#include<iostream>
#include<vector>
#include <unordered_map>
using namespace std;

class Solution {
    // 八个方向：上下左右 + 四条对角线
    static constexpr int dirs[8][2] = {
        { 1,  0}, { 1,  1}, { 0,  1}, {-1,  1},
        {-1,  0}, {-1, -1}, { 0, -1}, { 1, -1}
    };

    // 快速 (32-bit) Miller–Rabin 素数检测，适用于 n < 2^32
    bool isPrime(int n) {
        if (n < 2) return false;
        // 特殊小底数测试集
        static const int bases[] = { 2, 7, 61 };
        // 分解 n-1 = d * 2^s
        int d = n - 1, s = 0;
        while ((d & 1) == 0) {
            d >>= 1;
            s++;
        }
        auto modmul = [&](long long a, long long b) {
            return (a * b) % n;
            };
        auto modpow = [&](long long a, long long e) {
            long long r = 1;
            while (e) {
                if (e & 1) r = modmul(r, a);
                a = modmul(a, a);
                e >>= 1;
            }
            return r;
            };
        for (int a : bases) {
            if (a >= n) break;
            long long x = modpow(a, d);
            if (x == 1 || x == n - 1) continue;
            bool composite = true;
            for (int r = 1; r < s; r++) {
                x = modmul(x, x);
                if (x == n - 1) {
                    composite = false;
                    break;
                }
            }
            if (composite) return false;
        }
        return true;
    }

public:
    int mostFrequentPrime(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        unordered_map<int, int> freq;
        int bestCount = 0, bestPrime = -1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (auto [dx, dy] : dirs) {
                    int x = i, y = j;
                    int v = 0;
                    // 最多拼接 7 位，超过 10^7 就没必要继续
                    for (int step = 0; step < 7; step++) {
                        if (x < 0 || x >= m || y < 0 || y >= n)
                            break;
                        v = v * 10 + mat[x][y];
                        if (v >= 10 && isPrime(v)) {
                            int c = ++freq[v];
                            // 实时维护最频繁；若次数相同则取较大素数
                            if (c > bestCount || (c == bestCount && v > bestPrime)) {
                                bestCount = c;
                                bestPrime = v;
                            }
                        }
                        x += dx;
                        y += dy;
                    }
                }
            }
        }

        return bestCount == 0 ? -1 : bestPrime;
    }
};
