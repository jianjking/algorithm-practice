#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        unordered_map<int, int>cnt;
        int n = arr.size();
        int ans = 0;
        for (int i = 0;i < n;i++) {
            ans = (ans + cnt[target - arr[i]]) % mod;
            for (int j = 0;j < i;j++) {
                cnt[arr[i] + arr[j]]++;
            }
        }
        return ans;
    }
};