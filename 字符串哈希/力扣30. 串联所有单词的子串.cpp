#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int base = 1313;
        int n = s.size();
        int m = words[0].size(); // 每个单词的长度
        int totalWords = words.size();
        int windowSize = m * totalWords; // 窗口总长度

        // 处理空输入的情况
        if (n == 0 || windowSize == 0 || windowSize > n) {
            return {};
        }

        unordered_map<unsigned long long, int> wordCount;

        // 计算前缀哈希和bas数组
        vector<unsigned long long> hash(n);
        vector<unsigned long long> bas(max(n, m) + 1); // 确保bas足够大

        hash[0] = s[0] - 'a' + 1;
        for (int i = 1; i < n; ++i) {
            hash[i] = hash[i - 1] * base + s[i] - 'a' + 1;
        }

        bas[0] = 1;
        for (int i = 1; i < bas.size(); ++i) {
            bas[i] = base * bas[i - 1];
        }

        // 计算所有单词的哈希并统计次数
        for (auto& word : words) {
            unsigned long long wordHash = 0;
            for (char c : word) {
                wordHash = wordHash * base + (c - 'a' + 1);
            }
            wordCount[wordHash]++;
        }

        vector<int> result;

        // 遍历每个可能的起始位置（模m的余数）
        for (int start = 0; start < m; ++start) {
            unordered_map<unsigned long long, int> currentCount;
            int debt = totalWords;

            // 初始化当前窗口
            for (int i = start; i <= start + windowSize - m && i + m <= n; i += m) {
                unsigned long long substringHash = (i == 0) ? hash[i + m - 1] : hash[i + m - 1] - hash[i - 1] * bas[m];
                currentCount[substringHash]++;
                if (currentCount[substringHash] <= wordCount[substringHash]) {
                    debt--;
                }
            }

            if (debt == 0) {
                result.push_back(start);
            }

            // 滑动窗口
            for (int init = start; init + windowSize + m <= n; init += m) {
                int left = init;
                int right = init + windowSize;

                // 移除最左边的单词
                unsigned long long leftHash = (left == 0) ? hash[left + m - 1] : hash[left + m - 1] - hash[left - 1] * bas[m];
                currentCount[leftHash]--;
                if (currentCount[leftHash] < wordCount[leftHash]) {
                    debt++;
                }

                // 添加新的右侧单词
                unsigned long long rightHash = (right == 0) ? hash[right + m - 1] : hash[right + m - 1] - hash[right - 1] * bas[m];
                currentCount[rightHash]++;
                if (currentCount[rightHash] <= wordCount[rightHash]) {
                    debt--;
                }

                left += m;
                right += m;

                if (debt == 0) {
                    result.push_back(left);
                }
            }
        }

        return result;
    }
};