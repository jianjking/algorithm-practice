#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;
class Solution {
public:
    int countPairs(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [&](auto a, auto b) {
            return a < b;
            });
        int ans = 0;
        unordered_map<int, int>f;
        for (auto& p : nums) {
            string s = to_string(p);
            int m = s.size();
            ans += f[p];
            for (int i = 0;i < m;i++) {
                for (int j = i + 1;j < m;j++) {
                    if (s[i] != s[j]) {
                        swap(s[i], s[j]);
                        int a = stoi(s);
                        ans += f[a];
                        swap(s[i], s[j]);
                    }
                }
            }
            f[p]++;
        }
        return ans;
    }
};