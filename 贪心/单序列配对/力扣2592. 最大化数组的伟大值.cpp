#include<iostream>
#include<vector>
#include<map>
using namespace std;
//匹配不上的一定是最大词频
class Solution {
public:
    int maximizeGreatness(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        map<int, int>graph;
        for (int i = 0;i < n;i++) {
            graph[nums[i]]++;
            ans = max(graph[nums[i]], ans);
        }
        return n - ans ;
    }
};