#include<bits/stdc++.h>
using namespace std;
struct compare{
   bool operator()(const pair<int,double>&a,const pair<int,double>&b)const{
    if(a.second!=b.second)return a.second>b.second;
    return a.first<b.first;
   }
};
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
          vector<vector<pair<int,double>>>graph(n);
          int m=edges.size();
          for(int i=0;i<m;i++){
            graph[edges[i][0]].push_back({edges[i][1],succProb[i]});
             graph[edges[i][1]].push_back({edges[i][0],succProb[i]});
          }
        vector<double>dist(n,0);
        dist[start_node]=1;
        set<pair<int,double>,compare>q;
        q.insert({start_node,1});
        while(!q.empty()){
        pair<int,double>top=*q.begin();
        int u=top.first;
        double v=top.second;
        if(u==end_node)return v;
        q.erase(q.begin());
        if(dist[u]>v)continue;
        for(auto&p:graph[u]){
            if(dist[p.first]<v*p.second){
                dist[p.first]=v*p.second;
                q.insert({p.first,dist[p.first]});
            }
        }
        }
        return 0;
    }
};