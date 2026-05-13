#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        auto maskOf = [](const string& s) {
            int m = 0;
            for (char c : s) m |= 1 << (c - 'a');
            return m;
        };

        unordered_set<int> S;
        S.reserve(startWords.size() * 2);
        for (auto& w : startWords) S.insert(maskOf(w));

        int ans = 0;
        for (auto& w : targetWords) {
            int m = maskOf(w);
            bool ok = false;
            for (int b = 0; b < 26; ++b) {
                if (m & (1 << b)) {
                    int prev = m ^ (1 << b);
                    if (S.count(prev)) { ok = true; break; }
                }
            }
            if (ok) ++ans;
        }
        return ans;
    }
};
