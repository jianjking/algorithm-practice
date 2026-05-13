#include<iostream>
#include<vector>
using namespace std;
//cnt是以后多少位自由选择的情况。
//cnt选0+cnt[i-1]cnt是1的话+cnt[i-2]就跟斐波那契数列一样
class Solution {
public:
    int f(int i, vector<int>& cnt, int num) {
        if (i == -1)return 1;
        int ans = 0;
        if ((num & (1 << i)) != 0) {
            ans += cnt[i];
            if ((num & (1 << (i + 1))) != 0) {
                return ans;
            }
            ans += f(i - 1, cnt, num);
            return ans;
        }
        ans += f(i - 1, cnt, num);
        return ans;
    }
    int findIntegers(int n) {
        if (n == 0)return 1;
        if (n == 1)return 2;
        int tmp = n;
        int len = 0;
        while (tmp) {
            tmp /= 2;
            len++;
        }
        vector<int>cnt(len, 1);

        cnt[1] = 2;
        for (int i = 2;i < len;i++) {
            cnt[i] = cnt[i - 1] + cnt[i - 2];
        }
        return f(len - 1, cnt, n);
    }
};