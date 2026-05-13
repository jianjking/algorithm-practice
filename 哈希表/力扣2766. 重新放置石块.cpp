#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
class Solution {
public:
    vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) {
        map<int, bool>p;
        for (auto& p1 : nums) {
            p.insert({ p1, true });
        }
        int n = moveFrom.size();
        for (int i = 0;i < n;i++) {
            p[moveFrom[i]] = false;
            p[moveTo[i]] = true;
        }
        vector<int>ans;
        for (auto& p1 : p) {
            if (p1.second)ans.push_back(p1.first);
        }
        return ans;
    }
};