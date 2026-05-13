#include<bits/stdc++.h>
using namespace std;
const int INF=INT_MIN/4;
class Solution {
public:
int dfs(int i,vector<int>&dp,vector<int>&nums,vector<vector<int>>&offers){
    int n=dp.size();
    if(i>=n)return 0;
    int&res=dp[i];
    if(dp[i]!=INF)return res;
    int p=upper_bound(nums.begin(),nums.end(),offers[i][1])-nums.begin();
    res=max(dfs(i+1,dp,nums,offers),offers[i][2]+dfs(p,dp,nums,offers));
    return res;
}
    int maximizeTheProfit(int n, vector<vector<int>>& offers) {
        sort(offers.begin(),offers.end(),[](vector<int>&a,vector<int>&b){
            if(a[0]!=b[0])return a[0]<b[0];
            return a[1]<b[1];
        });
        vector<int>nums(n);
        for(int i=0;i<n;i++){
            nums[i]=offers[i][0];
        }
        vector<int>dp(n,INF);
        return dfs(0,dp,nums,offers);
    }
};