#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        int n = beans.size();
        sort(beans.begin(), beans.end());
        long long sum = 0;
        for (int i = 0;i < n;i++) {
            sum += beans[i];
        }
        long long ans = LLONG_MAX;
        for (int i = 0;i < n;i++) {
            ans = min(ans, sum - (long long)(n - i) * beans[i]);
        }
        return ans;
    }
};