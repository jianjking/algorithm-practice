#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int countPermutations(vector<int>& complexity) {
        int limit = complexity[0];
        for (int i = 1;i < complexity.size();i++) {
            if (complexity[i] <= limit)return 0;
        }
        long long ans = 1;
        int n = complexity.size() - 1;
        while (n) {
            ans = (ans * n) % mod;
            n--;
        }
        return ans;
    }
};