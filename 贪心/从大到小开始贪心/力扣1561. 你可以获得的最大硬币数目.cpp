#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maxCoins(vector<int>& piles) {
        int n = piles.size();
        sort(piles.begin(), piles.end(), [](int a, int b) {
            return a > b;
            });
        int ans = 0;
        if (n == 1)return 0;
        int k = n / 3;
        for (int i = 0,j=1;i < k;i++,j+=2) {
            ans += piles[j];
        }
        return ans;
    }

};