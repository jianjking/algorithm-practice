#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        unordered_map<int, int>f1;
        for (int i = 0;i < n;i += 2) {
            f1[nums[i]]++;
        }
        int a, b;
        int c = 0;
        int d = 0;
        for (auto p : f1) {
            if (p.second > c) {
                b = a;
                d = c;
                c = p.second;
                a = p.first;
            }
            else if (p.second > d) {
                d = p.second;
                b = p.first;
            }
        }
        unordered_map<int, int>f2;
        for (int j = 1;j < n;j += 2) {
            f2[nums[j]]++;
        }
        int a1, b1;
        int c1 = 0;
        int d1 = 0;
        for (auto p : f2) {
            if (p.second > c1) {
                b1 = a1;
                d1 = c1;
                c1 = p.second;
                a1 = p.first;
            }
            else if (p.second > d1) {
                d1 = p.second;
                b1 = p.first;
            }
        }
        if (a1 != a)return n - (c1 + c);
        return n - max(c1 + d, c + d1);
    }
};