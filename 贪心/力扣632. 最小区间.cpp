#include<iostream>
#include<vector>
#include<set>;
using namespace std;
struct GGG {
    int num;
    int i;
    int j;
};
struct compare {
    bool operator()(const GGG& a, const GGG& b)const {
        if (a.num != b.num)return a.num < b.num;
        return a.i < b.i;
    }
};
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        set<GGG, compare>arr;
        int n = nums.size();
        for (int i = 0;i < n;i++) {
            arr.insert({ nums[i][0],i,0 });
        }
        int right;
        int left;
        int m = INT_MAX;
        while (arr.size() == n) {
            int a = (*arr.begin()).num;
            int b = (*arr.rbegin()).num;
            if (m > b - a + 1) {
                m = b - a + 1;
                right = b;
                left = a;
            }
            auto c = arr.begin();
            int d = (*c).i;
            int f = (*c).j;
            arr.erase(arr.begin());
            if (f + 1 < nums[d].size()) {
                arr.insert({ nums[d][f + 1],d,f + 1 });
            }

        }
        return { left,right };
    }
};