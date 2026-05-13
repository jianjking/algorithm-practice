#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int n = dist.size();
        vector<int>t(n);
        for (int i = 0;i < n;i++) {
            t[i] = (dist[i] + speed[i] - 1) / speed[i];
        }
        sort(t.begin(), t.end());
        for (int i = 0;i < n;i++) {
            if (t[i] <= i) {
                return  i;
            }
        }
        return n;
    }
};