#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        int n = happiness.size();
        sort(happiness.begin(), happiness.end(), [](int a, int b) {
            return a > b;
            });
        long long ans = 0;
        for (int i = 0;i < k;i++) {
            if (happiness[i] >= i) {
                happiness[i] -= i;
            }
            else {
                happiness[i] = 0;
            }
            ans += happiness[i];
        }
        return ans;

    }
};