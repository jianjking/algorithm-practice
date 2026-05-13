#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        int sum = 0;
        for (auto& p : apple) {
            sum += p;
        }
        sort(capacity.begin(), capacity.end(), [](int a, int b) {
            return a > b;
            });
        int n = capacity.size();
        int ans = 0;
        for (int i = 0;i < n;i++) {
            ans += capacity[i];
            if (ans >= sum) {
                return i + 1;
            }
        }
        return 0;
    }
};