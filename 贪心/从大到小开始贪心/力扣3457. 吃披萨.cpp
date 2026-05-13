#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        sort(pizzas.begin(), pizzas.end(), [](int a, int b) {
            return a > b;
            });
        long long ans = 0;
        int n = pizzas.size();
        int m = n / 4;
        int j = 0;
        int i = 0;
        for (;i < (m + 1) / 2;i++) {
            ans += pizzas[j++];
        }
        j++;
        for (i = 0;i < m / 2;i++,j+=2) {
            ans += pizzas[j];
        }
        return ans;
    }
};
