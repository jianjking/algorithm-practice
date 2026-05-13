#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> words_perfect;        // 完全匹配
        unordered_map<string, string> words_cap;     // 小写形式 -> 原始单词
        unordered_map<string, string> words_vow;     // 去掉元音的小写形式 -> 原始单词

        // === 预处理字典 ===
        for (auto& word : wordlist) {
            words_perfect.insert(word);

            // 转小写
            string wordlow = word;
            for (auto& c : wordlow) c = tolower(c);

            if (!words_cap.count(wordlow)) {
                words_cap[wordlow] = word;
            }

            // 去元音
            string wordlowDV;
            for (char c : wordlow) {
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                    wordlowDV.push_back('*');
                else
                    wordlowDV.push_back(c);
            }

            if (!words_vow.count(wordlowDV)) {
                words_vow[wordlowDV] = word;
            }
        }

        // === 查询处理 ===
        vector<string> ans;
        for (auto& query : queries) {
            // 1. 完全匹配
            if (words_perfect.count(query)) {
                ans.push_back(query);
                continue;
            }

            // 转小写
            string queryL = query;
            for (auto& c : queryL) c = tolower(c);

            // 2. 忽略大小写匹配
            if (words_cap.count(queryL)) {
                ans.push_back(words_cap[queryL]);
                continue;
            }

            // 去元音
            string queryLV;
            for (char c : queryL) {
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                    queryLV.push_back('*');
                else
                    queryLV.push_back(c);
            }

            // 3. 忽略元音错误匹配
            if (words_vow.count(queryLV)) {
                ans.push_back(words_vow[queryLV]);
                continue;
            }

            // 4. 没有匹配
            ans.push_back("");
        }
        return ans;
    }
};
