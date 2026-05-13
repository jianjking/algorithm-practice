#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;
class Solution {
public:
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
        int l = (intLength + 1) / 2;   // 可以唯一确定回文数的前半部分的长度
        int start = (int)pow(10, l - 1) - 1;   // start + k 即为第 k 个 l 位无前导零整数
        int limit = (int)pow(10, l) - 1;   // l 位无前导零整数的上界
        vector<long long> res;
        // 将前半部分恢复为对应的回文数
        auto recover = [&](int num) -> long long {
            string s = to_string(num);
            if (intLength % 2 == 0) {
                for (int i = l - 1; i >= 0; --i) {
                    s.push_back(s[i]);
                }
            }
            else {
                for (int i = l - 2; i >= 0; --i) {
                    s.push_back(s[i]);
                }
            }
            return stoll(s);
            };

        // 依次处理询问
        for (int query : queries) {
            if (start + query > limit) {
                // 不存在
                res.push_back(-1);
                continue;
            }
            res.push_back(recover(start + query));
        }
        return res;
    }
};
