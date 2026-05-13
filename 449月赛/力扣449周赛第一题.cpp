#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minDeletion(string s, int k) {
        vector<int>arr(26, 0);
        for (auto& p : s) {
            arr[p - 'a']++;
        }
        sort(arr.begin(), arr.end(), [](int a, int b) {
            return a > b;
            });
        int ans = 0;
        for (int i = k;i < 26;i++)ans += arr[i];
        return ans;
    }
};