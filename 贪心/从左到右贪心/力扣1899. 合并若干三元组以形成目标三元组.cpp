#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        int a = target[0];
        int b = target[1];
        int c = target[2];
        vector<bool>find(3, false);
        int n = triplets.size();
        for (int i = 0;i < n;i++) {
            int a1 = triplets[i][0];
            int b1 = triplets[i][1];
            int c1 = triplets[i][2];
            if (a1 > a || b1 > b || c1 > c)continue;
            if (a1 == a)find[0] = true;
            if (b1 == b)find[1] = true;
            if (c1 == c)find[2] = true;
            bool an = true;
            for (int i = 0;i < 3;i++) {
                if (!find[i])an = false;
            }
            if (an)return true;
        }
        return false;
    }
};