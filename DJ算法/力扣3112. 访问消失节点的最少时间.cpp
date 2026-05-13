#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct compare{
    bool operator()(pair<int,int>&a,pair<int,int>&b){
        return a.second>b.second;
    }
}
class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        vector<vector<pair<int,int>>>arr(n);
        for(auto&p:edges){
            arr[p[0]].push_back({p[1],p[2]});
            arr[p[1]].push_back({p[0],p[2]});
        }
        vector<int>dist(n,INT_MAX);
        dist[0]=0;
        
   priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;
    heap.push({0,0});
    while(!heap.empty()){
       pair<int,int> tmp=heap.top();
       heap.pop();
       int  u=tmp.first;
    int v=tmp.second;
    if(dist[u]<v)continue;
      for(auto&p:arr[u]){
         int v1=v+p.second;
         int u1=p.first;
         if(disappear[u1]<=v1)continue;
         if(dist[u1]>v1){
            dist[u1]=v1;
            heap.push({u1,v1});
         }
      }
    }
    for(int i=0;i<n;i++){
        if(dist[i]==INT_MAX)dist[i]=-1;
    }    
    return dist;
}
};