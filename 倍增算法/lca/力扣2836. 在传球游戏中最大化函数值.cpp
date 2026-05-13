#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int power(long long n) {
        int p = 0;
        while ((1LL << p) <= n) p++;
        return p;
    }

    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        int n = receiver.size();
        int limit = power(k);
        vector<vector<int>> st(n, vector<int>(limit + 1));
        vector<vector<long long>> sum(n, vector<long long>(limit + 1));

        for (int i = 0; i < n; i++) {
            st[i][0] = receiver[i];
            sum[i][0] = receiver[i];
        }

        for (int j = 1; j <= limit; j++) {
            for (int i = 0; i < n; i++) {
                st[i][j] = st[st[i][j - 1]][j - 1];
                sum[i][j] = sum[i][j - 1] + sum[st[i][j - 1]][j - 1];
            }
        }

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long tmp = i;  // 初始加上出发点编号
            int j = i;
            long long t = k;
            for (int b = 0; t; b++, t >>= 1) {
                if (t & 1) {
                    tmp += sum[j][b];
                    j = st[j][b];
                }
            }
            ans = max(ans, tmp);
        }

        return ans;
    }
};