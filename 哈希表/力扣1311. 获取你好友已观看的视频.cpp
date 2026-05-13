#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<numeric>
#include<string>
using namespace std;
class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        unordered_set<int>pre;
        unordered_set<int>cur;
        int n = watchedVideos.size();
        vector<bool>visit(n, false);
        pre.insert(id);
        visit[id] = true;
        for (int i = 0;i < level;i++) {
            for (auto p : pre) {
                for (auto p1 : friends[p]) {
                    if (!visit[p1])
                        cur.insert(p1);

                    visit[p1] = true;
                }
            }
            pre = cur;
            cur.clear();
        }
        unordered_map<string, int>cnt;
        for (auto& p : pre) {
            for (auto& p1 : watchedVideos[p]) {
                cnt[p1]++;
            }
        }
        vector<pair<string, int>>vec;
        vec.reserve(cnt.size());
        for (auto& p : cnt) {
            vec.emplace_back(p.first, p.second);
        }
        sort(vec.begin(), vec.end(), [&](auto a, auto b) {
            if (a.second != b.second)return a.second < b.second;
            return a.first < b.first;
            });
        vector<string>ans;
        for (auto& p : vec) {
            if (p.second > 0)ans.push_back(p.first);
        };
        return ans;
    }
};