#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    string clearStars(string s) {
        int n = s.size();
        vector<vector<int>>cnt(26);
        vector<bool>vis(n);
        for (int i = 0; i < n;i++) {
            if (s[i] != '*') {
                vis[i] = true;
                cnt[s[i] - 'a'].push_back(i);
            }
            else {
                vis[i] = false;
                for (int j = 0; j < 26; j++) {
                    if (!cnt[j].empty()) {
                        vis[cnt[j].back()] = false;
                        cnt[j].pop_back();
                        break;
                    }
                }
            }
        }
        string ans;
        for (int i = 0; i < n;i++) {
            if (vis[i]) {
                ans += s[i];
            }
        }
        return ans;
    }
};