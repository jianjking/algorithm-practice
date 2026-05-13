#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Solution {
public:
    string largestPalindromic(string num) {
        vector<int>arr(10, 0);
        for (auto& p : num) {
            arr[p - '0']++;
        }
        string s;
        int mid = -1;
        for (int i = 9;i >= 1;i--) {
            if (mid == -1 && arr[i] & 1 == 1) {
                mid = i;
            }
            for (int j = 0;j < arr[i] / 2;j++) {
                s += to_string(i);
            }
        }
        if (s.size() == 0) {
            if (mid == -1) {
                return "0";
            }
            else {
                return to_string(mid);
            }
        }
        else {
            for (int i = 0;i < arr[0] / 2;i++)s += "0";
            if (mid == -1 && arr[0] & 1 == 1) {
                s += "0";
                int n = s.size();
                for (int i = n - 2;i >= 0;i--) {
                    s += s[i];
                }
            }
            else if (mid != -1) {
                s += to_string(mid);
                int n = s.size();
                for (int i = n - 2;i >= 0;i--) {
                    s += s[i];
                }
            }
            else {
                int n = s.size();
                for (int i = n - 1;i >= 0;i--) {
                    s += s[i];
                }
            }

        }
        return s;
    }
};