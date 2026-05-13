#include<iostream>
#include<vector>
using namespace std;
class Solution {
private:
    vector<int>h;
    vector<int>nxt;
    vector<int>to;
    int cnt;
public:
    void f(int a, int b, int seats, vector<int>& nums, vector<long>& costs, vector<int>& h, vector<int>& to, vector<int>& nxt) {
        for (int i = h[a];i >= 0;i = nxt[i]) {
            int c = to[i];
            if (c != b) {
                f(c, a, seats, nums, costs, h, to, nxt);
                costs[a] += costs[c] + (nums[c] + seats - 1) / seats;
                nums[a] += nums[c];
            }
        }
    }
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        cnt = 1;
        int n = roads.size();
        h.resize(n + 1, -1);
        nxt.resize(2 * n + 2);
        to.resize(2 * n + 2);
        for (auto& p : roads) {
            nxt[cnt] = h[p[0]];
            to[cnt] = p[1];
            h[p[0]] = cnt++;
            nxt[cnt] = h[p[1]];
            to[cnt] = p[0];
            h[p[1]] = cnt++;
        }
        vector<long>costs(n + 1, 0);
        vector<int>nums(n + 1, 1);
        f(0, -1, seats, nums, costs, h, to, nxt);
        return costs[0];
    }
};