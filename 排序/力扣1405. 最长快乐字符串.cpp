#include<iostream>
#include<vector>
#include<set>
using namespace std;
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        string res;
        vector<pair<int, char>> arr = { {a, 'a'}, {b, 'b'}, {c, 'c'} };

        while (true) {
            // 2.1 把库存从大到小排序，让 arr[0] 是“当下最富有”的字母
            sort(arr.begin(), arr.end(), [](const auto& p1, const auto& p2) {
                return p1.first > p2.first;
                });

            bool hasNext = false; // 这一轮能不能成功加一个字符

            // 2.2 尝试从最多的开始挑一个合法字符
            for (auto& [freq, ch] : arr) {
                int m = res.size();
                if (freq <= 0) break; // 排好序后遇到<=0，后面也都<=0，直接放弃

                // 如果 res 的最后两位正好都是 ch，继续选 ch 会形成 chchch（三连），那就跳过试试下一个
                if (m >= 2 && res[m - 2] == ch && res[m - 1] == ch) {
                    continue;
                }

                // 能放就放
                hasNext = true;
                res.push_back(ch);
                freq--;        // 库存 -1
                break;         // 本轮只放一个字符，然后回到 while 开新一轮
            }

            // 2.3 如果这一轮谁都放不下（要么没库存，要么放了会三连），那就收工
            if (!hasNext) break;
        }
        return res;

    }
};