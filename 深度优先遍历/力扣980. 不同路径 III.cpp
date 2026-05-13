#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
int ans;
void dfs(int i,int j,vector<vector<int>>&grid,int n,int m,int sum,int cnt){
                 if(grid[i][j]==2){
                    if(cnt==sum)ans++;
                    return;
                 }
                 int arr[]={1,0,-1,0,1};
                 for(int z=0;z<4;z++){
                    int tmpi=i+arr[z];
                    int tmpj=j+arr[z+1];
                    if(tmpi>=0&&tmpi<n&&tmpj>=0&&tmpj<m&&grid[tmpi][tmpj]!=-1&&grid[tmpi][tmpj]!=1){
                        if(grid[tmpi][tmpj]==2){
                            if(cnt==sum)ans++;
                        }
                        else{
                            grid[tmpi][tmpj]=-1;
                            dfs(tmpi,tmpj,grid,n,m,sum,cnt+1);
                            grid[tmpi][tmpj]=0;
                        }
                    }
                 }
}
    int uniquePathsIII(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        ans=0;
        int starti;
        int startj;
        int cnt=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                  if(grid[i][j]==1){
                    starti=i;
                    startj=j;
                  }
                  if(grid[i][j]==0)cnt++;
            }
        }
        dfs(starti,startj,grid,n,m,cnt,0);
        return ans;}
};