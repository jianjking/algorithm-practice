#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
class Solution {
public:
    int minImpossibleOR(vector<int> &nums) {
        unordered_set<int>s(nums.begin(), nums.end());
        for (int i = 1;; i <<= 1)
            if (!s.count(i))
                return i;
    }
};
