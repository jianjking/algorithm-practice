#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>
using namespace std;
class  compare {
    bool operator()(const pair<int, long long>& a, pair<int, long long>& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    }
};
class Solution {
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        set<pair<int,long long>,compare>cnt;
        for (auto& p : nums) {
            cnt.insert({ p,0 });
        }
        int n = freq.size();
        unordered_map<int, long long>num;
        vector<long long>ans(n, 0);
        for (int i = 0; i < n; i++) {
            cnt.erase({ nums[i],num[nums[i]] });
            num[nums[i]] += freq[i];
            cnt.insert({ nums[i],num[nums[i]] });
            ans[i] = (*cnt.begin()).second;
        }
        return ans;
    }
};