#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_map<string, vector<string>>graph;
        unordered_map<string, int>cnt;
        int n = recipes.size();
        for (int i = 0;i < n;i++) {
            string tmp = recipes[i];
            for (auto& p:ingredients[i]) {
                graph[p].push_back(tmp);
            }
            cnt[tmp] = ingredients[i].size();
        }
        queue<string>f;
        for (auto& p : supplies) {
            f.push(p);
        }
        vector<string>ans;
        while (!f.empty()) {
            string s = f.front();
            f.pop();
            for (auto& p : graph[s]) {
                cnt[p]--;
                if (cnt[p] == 0) {
                    f.push(p);
                    ans.push_back(p);
                }
            }
        }
        return ans;
    }
};