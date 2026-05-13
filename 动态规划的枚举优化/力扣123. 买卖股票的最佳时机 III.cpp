#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    //一开始的思路 但是超时了于是我们决定优化一下枚举
    //我们着眼于枚举
    // dp2[i]=dp1[0]+prices[i]-preces[0]
    // dp2[i]=dp1[1]+prices[i]-preces[1]
    //dp2[i] = dp1[2] + prices[i] - preces[2]
    //由此可见对于一个i值dp2[i]和prices[i]都是定值，问题变成了求(0,i)dp1[i]-prices[i]的最大值
    int f1(vector<int>& prices) {
        int n = prices.size();
        //dp1[i]为在（0，i）只能买一只股票的最大值
        vector<int>dp1(n);
        dp1[0] = 0;
        int m = prices[0];
        for (int i = 1;i < n;i++) {
            m = min(prices[i], m);
            dp1[i] = max(dp1[i - 1], prices[i] - m);
        }
        int ans = INT_MIN;
        vector<int>dp2(n,INT_MIN);
        //dp2[i]为必须在i点卖出获得的最大利润，第一层for循环为了遍历卖出点，第二层循环枚举买入点
        for (int i = 0;i < n;i++) {
            for (int j = 0;j <= i;j++) {
                dp2[i] = max(dp2[i],dp1[j] + prices[i] - prices[j]);
                ans = max(ans, dp2[i]);
            }
        }
        return ans;
   }
    //于是f2应运而生
    int f2(vector<int>& prices) {
        int n = prices.size();
        //dp1[i]为在（0，i）只能买一只股票的最大值
        vector<int>dp1(n);
        dp1[0] = 0;
        int m = prices[0];
        for (int i = 1;i < n;i++) {
            m = min(prices[i], m);
            dp1[i] = max(dp1[i - 1], prices[i] - m);
        }
        vector<int>best(n);
        //best[i]为(0, i)dp1[i] - prices[i]的最大值
        best[0] = dp1[0] - prices[0];
        for (int i = 1;i < n;i++) {
            best[i] = max(best[i - 1], dp1[i] - prices[i]);
        }
        int ans = INT_MIN;
        vector<int>dp2(n, INT_MIN);
        for (int i = 0;i < n;i++) {
            dp2[i] = prices[i] + best[i];
            ans = max(ans, dp2[i]);
        }
        return ans;
    }
    //剩下的方法我懒得写了就是合并成一个循环
    //然后发现只依赖于上一个位置，在进行空间压缩
    int maxProfit(vector<int>& prices) {
        return f2(prices);
    }
};