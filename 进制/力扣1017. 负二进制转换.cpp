#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Solution {
public:
    string baseNeg2(int n) {
        if (n == 0) return "0";
        // 1. 取出 n 的二进制位
        vector<int> b;
        int x = n;
        while (x > 0) {
            b.push_back(x & 1);
            x >>= 1;
        }
        // 2. 应用 2^i 分解公式
        vector<int> neg(b.size() + 2, 0);
        for (int i = 0; i < b.size(); i++) {
            if (i % 2 == 0) {
                neg[i] += b[i];
            }
            else {
                neg[i] += b[i];
                neg[i + 1] += b[i];
            }
        }
        // 3. 归一化到 0/1
        for (int i = 0; i + 1 < neg.size(); i++) {
            if (neg[i] >= 2) {
                int carry = neg[i] / 2;
                neg[i] %= 2;
                neg[i + 1] -= carry;
            }
            if (neg[i] < 0) {
                int borrow = (-neg[i] + 1) / 2;
                neg[i] += borrow * 2;
                neg[i + 1] += borrow;
            }
        }
        // 4. 去前导零，拼字符串
        int k = neg.size() - 1;
        while (k > 0 && neg[k] == 0) k--;
        string ans;
        for (int i = k; i >= 0; i--) {
            ans.push_back('0' + neg[i]);
        }
        return ans;
    }
};
