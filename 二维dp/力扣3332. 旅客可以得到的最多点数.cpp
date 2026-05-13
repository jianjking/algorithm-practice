#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int dfs(int n,vector<vector<int>>&dp,int i,int  step,vector<vector<int>>&score1,vector<vector<int>>&score2){
        if(step==0)return 0;
        int&res=dp[i][step];
        if(res!=INT_MIN)return res;
        res=max(res,dfs(n,dp,i,step-1,score1,score2)+score1[step-1][i]);
        for(int j=0;j<n;j++){
            if(j==i)continue;
         res=max(res,dfs(n,dp,j,step-1,score1,score2)+score2[j][i]);
        }
        return res;
    }
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        vector<vector<int>>dp(n,vector<int>(k+1,INT_MIN));
        int ans=INT_MIN;
        for(int i=0;i<n;i++){
            ans=max(ans,dfs(n,dp,i,k,stayScore,travelScore));
        }
        return ans;
    }
};