#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        int n = nums.size();
        vector<string>num(n);
        for (int i = 0;i < n;i++) {
            num[i] = to_string(nums[i]);
        }
        sort(num.begin(), num.end(), [](string& a, string& b) {
            return a + b > b + a;
            });
        if (num[0] == "0")return "0";
        string result;
        for (auto& p : num) {
            result += p;
        }
        return result;
        

    }
};