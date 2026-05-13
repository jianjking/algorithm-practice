#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        if (startFuel >= target)return 0;
        priority_queue<int>heap;
        int cnt = 0;
        for (auto& p : stations) {
            if (startFuel >= p[0]) {
                heap.push(p[1]);
            }
            else {
                while (!heap.empty() && startFuel < p[0]) {
                    startFuel += heap.top();
                    cnt++;
                    heap.pop();
                    if (startFuel >= target) {
                        return cnt;
                    }
                }
                if (startFuel < p[0])return -1;
                heap.push(p[1]);
            }
        }
        while (!heap.empty() && startFuel < target) {
            startFuel += heap.top();
            cnt++;
            heap.pop();
            if (startFuel >= target) {
                return cnt;
            }
        }
        return -1;
    }
};