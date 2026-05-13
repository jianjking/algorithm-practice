#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;
class Solution {
public:
    // 判断 sub 是否是 arr 中除下标 idx 以外所有字符串都不包含的子串
    bool isUniqueSubstring(const vector<string>& arr, int idx, const string& sub) {
        for (int j = 0; j < (int)arr.size(); j++) {
            if (j == idx) continue;
            if (arr[j].find(sub) != string::npos) {
                // 如果在其它某个字符串中能找到 sub，就不是唯一的了
                return false;
            }
        }
        return true;
    }

    vector<string> shortestSubstrings(vector<string>& arr) {
        int n = arr.size();
        vector<string> ans(n);

        // 对每个字符串 arr[i]，枚举所有可能的子串，找出「最短、字典序最小」且满足唯一性的那个
        for (int i = 0; i < n; i++) {
            const string& s = arr[i];
            int m = s.size();
            string best = "";  // 记录当前找到的最优子串

            // 枚举子串长度 size，从 1 开始递增，先找到短的就可以停长度循环
            for (int size = 1; size <= m && best.empty(); size++) {
                // 枚举所有长度为 size 的子串，子串的起点是 [0..m-size]
                for (int start = 0; start + size <= m; start++) {
                    string sub = s.substr(start, size);
                    // 如果这个子串满足「在其它字符串中不存在」的要求
                    if (isUniqueSubstring(arr, i, sub)) {
                        // 如果是第一个符合条件的，或者字典序更小，就更新 best
                        if (best.empty() || sub < best) {
                            best = sub;
                        }
                    }
                }
                // 注意：虽然长度相同的子串还可能更小，但一旦在本长度内
                // 枚举完毕后 best 一定记录了该长度内字典序最小的合法子串，
                // 此时不用再尝试更大的长度
            }

            ans[i] = best;
        }

        return ans;
    }
};