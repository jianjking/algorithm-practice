#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool isItPossible(string word1, string word2) {
        vector<int> c1(26), c2(26);
        for (char c : word1) c1[c - 'a']++;
        for (char c : word2) c2[c - 'a']++;

        // 统计不同字符的个数
        auto distinct = [](const vector<int>& cnt) {
            int res = 0;
            for (int x : cnt) if (x > 0) res++;
            return res;
            };

        int d1 = distinct(c1);
        int d2 = distinct(c2);

        for (int x = 0; x < 26; x++) {
            if (c1[x] == 0) continue; // 必须要有字母
            for (int y = 0; y < 26; y++) {
                if (c2[y] == 0) continue;

                if (x == y) {
                    if (d1 == d2) return true;
                }
                else {
                    int nd1 = d1 - (c1[x] == 1) + (c1[y] == 0);
                    int nd2 = d2 - (c2[y] == 1) + (c2[x] == 0);
                    if (nd1 == nd2) return true;
                }
            }
        }
        return false;
    }
};
