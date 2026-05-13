#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
class Solution {
public:
    using LL = long long;
    long long countVowels(string word) {
        int n = word.size();
        vector<LL> f(n + 1);

        unordered_set<char> st{ 'a', 'o','e','i','u' };
        for (int i = 1; i <= n; i++) {
            if (st.count(word[i - 1])) f[i] = f[i - 1] + i;
            else f[i] = f[i - 1];
        }
        LL res = 0;
        for (const auto& x : f) {
            res += x;
        }
        return res;
    }
};
