#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        ranges::sort(buses);
        ranges::sort(passengers);

        // 模拟乘客上车
        int j = 0, c;
        for (int t : buses) {
            for (c = capacity; c && j < passengers.size() && passengers[j] <= t; c--) {
                j++;
            }
        }

        // 寻找插队时机
        j--;
        int ans = c ? buses.back() : passengers[j];
        while (j >= 0 && ans == passengers[j]) {
            ans--; // 往前找没人到达的时刻
            j--;
        }
        return ans;
    }
};
