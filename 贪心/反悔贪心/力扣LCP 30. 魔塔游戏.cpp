#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct compare {
    bool operator()(int a, int b) {
        return a < b;
    }
};
class Solution {
public:
    int magicTower(vector<int>& nums) {
        priority_queue<int, vector<int>, compare>heap;
        long long sum = 1;
        long long pay = 0;
        int ans = 0;
        for (auto& p : nums) {
            if (p >= 0)sum += p;
            else {
                heap.push(abs(p));
                sum += p;
                if (sum <= 0) {
                    while (!heap.empty() && sum <= 0) {
                        sum += heap.top();
                        pay += heap.top();
                        heap.pop();
                        ans++;
                    }
                    if (sum <= 0)return -1;
                }
            }
        }
        return sum > pay ? ans : -1;
    }
};