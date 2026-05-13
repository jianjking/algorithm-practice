#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        vector<int>z(n, 0);
        z[0] = n;
        for (int i = 1, c = 1, r = 1;i < n;i++) {
            int len = r > i ? min(r - i, z[i-c]) : 0;
            while (len + i < n && word[len] == word[i + len])len++;
            if (i + len > r) {
                r = len + i;
                c = i;
            }
            z[i] = len;
        }
        for (int i = k;i < n;i += k) {
            if (z[i] == n - i)return i / k;
        }
        return (n + (k - 1)) / k;
    }
};
