#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
bool dfs(int i,int j,int n,int m,vector<vector<char>>&grid,char value,vector<vector<bool>>&vis,int dirt){
              for(int z=0;z<4;z++){
                if(z==(dirt+2)%4)continue;
                int tmpi=i+arr[z][0];
                int tmpj=j+arr[z][1];
                if(tmpi<n&&tmpi>=0&&tmpj<m&&tmpj>=0&&grid[tmpi][tmpj]==grid[i][j]){
                        if(vis[tmpi][tmpj]){
                            return true;
                        }
                        vis[tmpi][tmpj]=true;
                        if(dfs(tmpi,tmpj,n,m,grid,value,vis,z))return true;
                }
              }
              return false;
}
vector<vector<int>>arr;
    bool containsCycle(vector<vector<char>>& grid) {
      arr={{-1,0},{0,-1},{1,0},{0,1}};
      int n=grid.size();
      int m=grid[0].size();
      vector<vector<bool>>vis(n,vector<bool>(m,false));
      for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!vis[i][j]){
                vis[i][j]=true;
                if(dfs(i,j,n,m,grid,grid[i][j],vis,-3)){
                    return true;
                }
            }
        }
      }
      return false;
    }
};