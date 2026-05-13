#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
const int power = 533;
class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        int n = nums.size();
        unordered_set<long long>f;
        for (int i = 0;i < n;i++) {
            int cnt = 0;
            unsigned long long hash = 0;
            for (int j = i;j < n;j++) {
                if (nums[j] % p == 0)cnt++;
                if (cnt > k)break;
                hash = hash * power + nums[j];
                f.insert(hash);
            }
        }
        return f.size();
    }
};