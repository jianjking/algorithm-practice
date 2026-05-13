#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool lowbit(long long a, int k) {
        int cnt = 0;
        while (a) {
            long long b = a & (-a);
            a -= b;
            cnt++;
        }
        return k >= cnt;
    }
    //num1=k个2的i次方+k*num2
    //num1-k*num2=k个2的i次方
    //x=num1-k*num2
    //如果x<k则错了因为最小分解为k个1
    //k>=x的比特位
    //k>=num1-k*num2
    //取最大值发现k不超过36
    int makeTheIntegerZero(int num1, int num2) {
        int k = 1;
        while (k <= 36) {
            if ((long long)num1 - (long long)k * num2 < k)return -1;
            if (lowbit((long long)num1 - (long long)k * num2, k))return k;
            k++;
        }
        return 0;
    }
};