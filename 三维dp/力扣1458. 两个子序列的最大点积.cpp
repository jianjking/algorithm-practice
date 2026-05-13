#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
int dfs(int n,int m,vector<int>& nums1, vector<int>& nums2,vector<vector<vector<int>>>& dp,int flag){
    if(n==0||m==0){
        if(flag) return 0;
        return INT_MIN;
    }
    if(dp[n][m][flag]!=INT_MIN) return dp[n][m][flag];
    int res=INT_MIN;
    res=max(res,dfs(n-1,m,nums1,nums2,dp,flag));
    res=max(res,dfs(n,m-1,nums1,nums2,dp,flag));
    res=max(res,dfs(n-1,m-1,nums1,nums2,dp,1)+nums1[n-1]*nums2[m-1]);
    return dp[n][m][flag]=res;
}

    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size();
        int m=nums2.size();
        vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(m+1,vector<int>(2,INT_MIN)));
       return dfs(n,m,nums1,nums2,dp,0);
    }
};