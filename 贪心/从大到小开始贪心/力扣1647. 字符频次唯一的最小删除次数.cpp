#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minDeletions(string s) {
        map<int, int>graph;
        for (auto&& p : s) {
            graph[p - 'a']++;
        }
        vector<int>arr(graph.size());
        int i = 0;
        for (auto& p : graph) {
            arr[i++] = p.second;
        }
        sort(arr.begin(), arr.end(), [](int a, int b) {
            return a > b;
            });
        int n = arr.size();
        int ans = 0;
        vector<bool>cnt(arr[0] + 1, true);
        for (int i = 0;i < n;i++) {
            int tmp = arr[i];
            while (!cnt[tmp]) {
                tmp--;
            }
            if (tmp != 0)cnt[tmp]=false;
            ans += arr[i] - tmp;
        }
        return ans;
    }
};