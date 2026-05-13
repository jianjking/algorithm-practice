#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>>dist(n,vector<int>(n,INT_MAX));
        for(int i=0;i<n;i++){
            dist[i][i]=0;
        }
        for(auto&p:edges){
            dist[p[0]][p[1]]=p[2];
            dist[p[1]][p[0]]=p[2];
        }
        for(int i=0;i<n;i++){
           for(int j=0;j<n;j++){
            for(int z=0;z<n;z++){
                if(dist[j][i]!=INT_MAX&&dist[i][z]!=INT_MAX&&dist[i][z]+dist[j][i]<dist[j][z]){
                      dist[j][z]=dist[j][i]+dist[i][z];
                }
            }
           }
        }
        int ans1=0;
        int ans2=INT_MAX;
        for(int i=0;i<n;i++){
             int cnt=0;
            for(int j=0;j<n;j++){
               if(dist[i][j]<=distanceThreshold){
                cnt++;
               }
            }
            if(ans2>=cnt){
                ans1=i;
                ans2=cnt;
            }
        }
        return ans1;
    }
};