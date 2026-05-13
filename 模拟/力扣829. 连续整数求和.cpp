#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int ans = 0;
        // 1. 用 i 代表连续序列的长度，从 1 开始尝试，
        //    条件是 i*(i+1) <= 2*n，相当于 i*(i+1)/2 <= n*1 （提前剪枝）
        for (int i = 1; i * (i + 1) <= 2 * n; i++) {
            // 2. 连续 i 个数 a, a+1, …, a+i-1 加起来应该等于 n：
            //      n = a + (a+1) + … + (a+i-1)
            //      = i*a + (0+1+…+(i-1))
            //      = i*a + i*(i-1)/2
            //    移项得：i*a = n - i*(i-1)/2
            int t = n - i * (i - 1) / 2;

            // 3. 要让 a 是整数，就要求 t 能被 i 整除
            if (t % i == 0) {
                // 4. 整除后算出起始数 a
                int a = t / i;
                // 5. 题目要求正整数序列，所以 a 必须 ≥ 1
                if (a >= 1)
                    ans++;
            }
        }
        // 6. 返回满足条件的序列个数
        return ans;
    }
};
