#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
class Solution {
public:
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
        unordered_map<int, int>nums;
        int n = order.size();
        for (int i = 0; i < n; i++) {
            nums[order[i]] = i;
        }
        sort(friends.begin(), friends.end(), [&](auto a, auto b) {
            return nums[a] < nums[b];
            });
        return friends;
    }
}; 