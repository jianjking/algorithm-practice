#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxSubstrings(string word) {
        int ans = 0;
        vector<int>pos(26,-1);
        for (int i = 0; i < word.size(); i++) {
            int ch = word[i] - 'a';
            if (pos[ch] < 0) { // 之前没有遇到
                pos[ch] = i;
            }
            else if (i - pos[ch] > 2) { // 再次遇到，且子串长度 >= 4
                ans++;
              
                pos.assign(26, -1);
            }
        }
        return ans;
    }
};
