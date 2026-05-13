#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>
using namespace std;
class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        queue<int> q;
        unordered_set<int> vis;
        q.push(x);
        vis.insert(x);

        int ans = 0;
        int limit = max(x, y) + 100; // 给个余量

        while (!q.empty()) {
            int k = q.size();
            for (int i = 0; i < k; i++) {
                int num = q.front();
                q.pop();

                if (num == y) return ans;

                // 操作 1: +1
                if (num < limit && !vis.count(num + 1)) {
                    q.push(num + 1);
                    vis.insert(num + 1);
                }
                // 操作 2: -1
                if (num > 0 && !vis.count(num - 1)) {
                    q.push(num - 1);
                    vis.insert(num - 1);
                }
                // 操作 3: /11
                if (num % 11 == 0 && !vis.count(num / 11)) {
                    q.push(num / 11);
                    vis.insert(num / 11);
                }
                // 操作 4: /5
                if (num % 5 == 0 && !vis.count(num / 5)) {
                    q.push(num / 5);
                    vis.insert(num / 5);
                }
            }
            ans++;
        }
        return ans;
    }
};
