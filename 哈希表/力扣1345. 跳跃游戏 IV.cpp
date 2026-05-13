#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;
class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;

        // 值 -> 出现的所有下标
        unordered_map<int, vector<int>> pos;
        pos.reserve(n * 2);
        for (int i = 0; i < n; ++i) pos[arr[i]].push_back(i);

        vector<int> dist(n, INT_MAX);
        queue<int> q;
        dist[0] = 0;
        q.push(0);

        while (!q.empty()) {
            int i = q.front(); q.pop();
            int d = dist[i];
            if (i == n - 1) return d;

            // 相邻两步
            if (i - 1 >= 0 && dist[i - 1] == INT_MAX) {
                dist[i - 1] = d + 1; q.push(i - 1);
            }
            if (i + 1 < n && dist[i + 1] == INT_MAX) {
                dist[i + 1] = d + 1; q.push(i + 1);
            }

            // 同值跳转：把这个值对应的所有位置一次性扩张，然后删除桶
            auto it = pos.find(arr[i]);
            if (it != pos.end()) {
                for (int j : it->second) {
                    if (dist[j] == INT_MAX) {
                        dist[j] = d + 1;
                        q.push(j);
                    }
                }
                pos.erase(it); // 关键：避免重复遍历导致 O(n^2)
            }
        }
        return -1; // 理论上不会到这
    }
};
