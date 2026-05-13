#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int len;
    int f(int i, int offset, int n, vector<int>& cur, int status) {
        if (i == len)return 1;
        int ans = 0;
        int a = (n / offset) % 10;
        for (int j = 0;j < a;j++) {
            if ((status & (1 << j)) != 0) {
                ans += cur[len - i - 1];
            }
        }
        if ((status & (1 << a)) != 0) {
            ans += f(i + 1, offset / 10, n, cur, status ^ (1 << a));
        }
        return ans;
    }
    int countSpecialNumbers(int n) {
         len = 0;
        int tem = n;
        while (tem) {
            tem /= 10;
            len++;
        }
        if (len == 1)return n;
        int ans = 9;
        for (int i =2, k = 9, s = 9;i < len;i++,s--) {
            k *= s;
            ans += k;
        }
        vector<int>cur(len, 1);
        for (int i = 1, s = 10 - len + 1;i < len;i++,s++) {
            cur[i] = cur[i-1]*s;
        }
        int offest = pow(10, len - 1);
        int a = (n / offest) % 10;
        ans += (a - 1) * cur[len - 1];
        int status = (1 << 10)-1;
        return ans + f(1, offest / 10,n,cur,status^(1<<a));
    }
};
