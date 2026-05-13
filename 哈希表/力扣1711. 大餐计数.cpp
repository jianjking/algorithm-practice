#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
        unordered_map<int, int>cnt;
        int n = deliciousness.size();
        for (int i = 0; i < n; i++) {
            cnt[deliciousness[i]]++;
        }
        long long ans = 0;
        int arr[22];
        arr[0] = 1;
        for (int i = 1; i < 22; i++) {
            arr[i] = arr[i - 1] * 2;
        }
        for (int i = 0; i < n; i++) {
            cnt[deliciousness[i]]--;
            for (int j = 0; j < 22; j++) {
                int tmp = arr[j] - deliciousness[i];
                
                ans = (ans + cnt[tmp]) % mod;
            }
        }
        return ans;
    }
};