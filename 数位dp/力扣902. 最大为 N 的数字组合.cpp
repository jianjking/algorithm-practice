#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int f(vector<int>& arr, vector<int>& a, int offset, int target, int len) {
        if (len == 0)return 1;
        int cur = (target / offset) % 10;
        int ans = 0;
        for (auto& p : arr) {
            if (p < cur)ans += a[len - 1];
            else if (p == cur)ans += f(arr, a, offset / 10, target, len - 1);
            else {
                break;
            }
        }
        return ans;
    }
    int atMostNGivenDigitSet(vector<string>& digits, int t) {
        int n = digits.size();
        vector<int>arr(n);
        for (int i = 0;i < n;i++) {
            int cur = digits[i][0];
            int m = digits[i].size();
            for (int j = 1;j < m;j++) {
                cur *= 10;
                cur += digits[i][j];
            }
            arr[i] = cur;
        }
        vector<int>a(n,1);
        a[1] = n;
        int ans = a[1];
        for (int i = 2;i < n;i++) {
            a[i] = a[i - 1] * n;
            ans += a[i];
        }
        int len = 0;
        int tem = n;
        while (tem) {
            tem / 10;
            len++;
        }
        int offset = pow(10,len-1);
        return ans+f(arr, a, offset, t, len);
    }
};