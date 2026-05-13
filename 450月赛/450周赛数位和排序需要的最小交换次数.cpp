#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<numeric>
using namespace std;
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int>num(n);
        for (int i = 0;i < n;i++) {
            int tmp = nums[i];
            int sum = 0;
            while (tmp) {
                sum += tmp % 10;
                tmp /= 10;
            }
            num[i] = sum;
        }
        vector<int>tmp(n);
        iota(tmp.begin(), tmp.end(), 0);
        sort(tmp.begin(), tmp.end(), [&](auto a, auto b) {
            if (num[a] != num[b])return num[a] < num[b];
            return nums[a] < nums[b];
            });
        unordered_map<int, int>f;
        int ans = 0;
        for (int i = 0;i < n;) {
            if (i != tmp[i]) {
                swap(tmp[i], tmp[tmp[i]]);
                ans++;
            }
            else {
                i++;
            }
        }
        return ans;
    }
};