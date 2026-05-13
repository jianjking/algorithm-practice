#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int largestCombination(vector<int>& candidates) {
        int cnt[24]{};
        for (int x : candidates) {
            for (int i = 0; x; i++) {
                cnt[i] += x & 1;
                x >>= 1;
            }
        }
        return ranges::max(cnt);
    }
};

