#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int sum;
    void create(vector<int>& num, vector<vector<int>>& cnt) {
        int pre = 0;
        int n = num.size();
        for (int i = 0;i < n;i++) {
            if (cnt[pre][num[i]] == 0) {
                cnt[pre][num[i]] = sum++;
            }
            pre = cnt[pre][num[i]];
        }
    }
    int find(vector<int>& num, vector<vector<int>>& cnt) {
        int pre = 0;
        int cur = 0;
        int n = num.size();
        for (int i = 0;i < n;i++) {
            if (cnt[pre][num[i]] == 0)break;
            cur++;
            pre = cnt[pre][num[i]];
        }
        return cur;
    }
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        vector<vector<int>>cnt(9, vector<int>(10, 0));
        sum = 1;
        for (auto& p : arr1) {
            int tmp = p;
            int aaa=1;
            while (tmp) {
                tmp /= 10;
                aaa *= 10;
            }
            aaa /= 10;
            vector<int>num;
            num.reserve(8);
            while (p) {
                num.push_back(p / aaa);
                p %=aaa;
                aaa /= 10;
            }
            create(num, cnt);
        }
        int ans = INT_MIN;
        for (auto& p : arr2) {
            int tmp = p;
            int aaa = 1;
            while (tmp) {
                tmp /= 10;
                aaa *= 10;
            }
            aaa /= 10;
            vector<int>num;
            num.reserve(8);
            while (p) {
                num.push_back(p / aaa);
                p %= aaa;
                aaa /= 10;
            }
            ans=max(ans,find(num, cnt));
        }
        return ans;
    }
};