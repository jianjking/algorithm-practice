#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<long long> maximumEvenSplit(long long n) {
        if (n % 2)return {};
        vector<long long>ans;
        for (long long i = 2;n >= i;i += 2) {
            ans.push_back(i);
            n -= i;
        }
        ans.back() += n;
        return ans;
    }
};