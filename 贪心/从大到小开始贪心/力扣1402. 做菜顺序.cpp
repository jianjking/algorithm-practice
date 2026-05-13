#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.begin(), satisfaction.end(), [&](auto a, auto b) {
            return a > b;
            });
        int n = satisfaction.size();
        vector<int>arr(n);
        int cnt = 0;
        long long sum = 0;
        for (int i = 0;i < n;i++) {
            sum += satisfaction[i];
            if (sum > 0) {
                arr[cnt++] = i;
            }
        }
        int ans = 0;
        int time = 1;
        for (int i = cnt - 1;i >= 0;i--) {
            ans += satisfaction[arr[i]] * time++;

        }
        return ans;
    }
};