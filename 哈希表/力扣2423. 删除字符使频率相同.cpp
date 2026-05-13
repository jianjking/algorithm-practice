#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
class Solution {
public:
    bool equalFrequency(string word) {
        unordered_map<char, int> m_cnt;
        for (char c : word)
            ++m_cnt[c];
        vector<int> cnt;
        for (auto& [_, c] : m_cnt)
            cnt.push_back(c);
        sort(cnt.begin(), cnt.end()); // 出现次数从小到大排序
        // 只有一种字符 or 去掉次数最少的 or 去掉次数最多的
        return cnt.size() == 1 ||
            cnt[0] == 1 && equal(cnt.begin() + 2, cnt.end(), cnt.begin() + 1) ||
            cnt.back() == cnt[cnt.size() - 2] + 1 && equal(cnt.begin() + 1, cnt.end() - 1, cnt.begin());
    }
};

