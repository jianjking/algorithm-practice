#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        int n = grades.size();
        int ans = 0;
        for (int i = 1;n >= i;n -= i, i++) {
            ans++;
        }
        return ans;
    }
};