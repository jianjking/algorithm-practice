#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int sum=0;
        int n=status.size();
        queue<int>q;
        unordered_set<int>key;
        unordered_set<int>box;
        vector<bool>vis(n,false);
        for(int i=0;i<n;i++){
           if(status[i]==1){
            key.insert(i);
           }
        }
        for(auto&p:initialBoxes){
            if(key.count(p)){
                q.push(p);
            }
            box.insert(p);
        }
        while(!q.empty()){
            int top=q.front();
        q.pop();
          if(vis[top])continue;
          vis[top]=true;
          sum+=candies[top];
          for(auto&p:containedBoxes[top]){
             box.insert(p);
            if(!vis[p]&&key.count(p)){
                q.push(p);
            }
          }
          for(auto&p:keys[top]){
            key.insert(p);
            if(!vis[p]&&box.count(p)){
                q.push(p);
            }
          }
        }
        return sum;
    }
};