#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    vector<long long> getDistances(vector<int>& arr) {
        unordered_map<int, vector<int>>graph;
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            graph[arr[i]].push_back(i);
        }
        vector<long long>ans(n);
        for (int i = 0; i < n; i++) {
            int present = lower_bound(graph[arr[i]].begin(), graph[arr[i]].end(), i) - graph[arr[i]].begin();
            if (present == 0) {
                for (auto& p : graph[arr[i]])ans[i] += p - i;
            }
            else {
                int j = graph[arr[i]][present - 1];
                ans[i] += ans[j] + present * (i - j) + (graph[arr[i]].size() - present) * (i - j);
            }
        }
        return ans;
    }
};