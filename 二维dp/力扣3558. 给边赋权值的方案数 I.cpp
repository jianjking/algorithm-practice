#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
class Solution {
public:
void dfs(int cur,int fa,int &nums,vector<vector<int>>&graph,vector<int>&depth){
    depth[cur]=depth[fa]+1;
    if(depth[cur]>depth[nums]){
        nums=cur;
    }
    for(auto&p:graph[cur]){
        if(p!=fa){
            dfs(p,cur,nums,graph,depth);
        }
    }
}
int dfs1(int cur,int fa,int target,int sum,vector<vector<int>>&dp,vector<vector<int>>&graph){
       int &res=dp[cur][sum];
       if(cur==target)return sum%2==0?0:1;
       if(res!=INT_MIN)return res;
       res=0;
       for(auto&p:graph[cur]){
        if(p!=fa){
            for(int i=1;i<3;i++){
            res=(res+dfs1(p,cur,target,(sum+i)%2,dp,graph))%mod;
        }
    }
       }
       return res;
}
    int assignEdgeWeights(vector<vector<int>>& edges) {
        int n=edges.size()+1;
        vector<vector<int>>graph(n+1);
        for(auto&p:edges){
            graph[p[0]].push_back(p[1]);
            graph[p[1]].push_back(p[0]);
        }
        int nums=0;
        vector<int>depth(n+1,0);
        vector<vector<int>>dp(n+1,vector<int>(3,INT_MIN));
        dfs(1,0,nums,graph,depth);
        return dfs1(1,0,nums,0,dp,graph);
    }
};