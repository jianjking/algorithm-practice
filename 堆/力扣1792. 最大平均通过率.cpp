#include<iostream>
#include<vector>
#include<set>
using namespace std;
struct compare {
    bool operator()(const pair<int, double>& a, const pair<int, double>& b)const{
        if (a.second != b.second)return a.second > b.second;
        return a.first > b.first;
    }
};
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        int n = classes.size();
        double ans = 0;
        set<pair<int, double>,compare>nums;
        for (int i = 0; i < n; i++) {
            ans += (double)classes[i][0] / classes[i][1] / n;;
            nums.insert({ i,(double)(classes[i][0]+1) / (classes[i][1]
 +1) - (double)classes[i][0] / classes[i][1] });
        }
        while (extraStudents > 0) {
            auto tmp = *nums.begin();
            int i = tmp.first;
            double j = tmp.second;
            ans += j / n;
            int a = classes[i][0];
            int b = classes[i][1];
            nums.erase(nums.begin());
            nums.insert({ i,(double)(a + 1) / (b + 1)-(double)a/b});
            extraStudents --;
        }
        return ans;
    }
};