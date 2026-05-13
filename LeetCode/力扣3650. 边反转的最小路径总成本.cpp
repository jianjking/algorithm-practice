#include<bits/stdc++.h>
using namespace std;
struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b)const{
        if(a.second!=b.second)return a.second<b.second;
        return a.first<b.first;
    }
};
class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>>graph(n);
        for(auto&p:edges){
            graph[p[0]].push_back({p[1],p[2]});
            graph[p[1]].push_back({p[0],2*p[2]});
        }
        vector<int>dist(n,INT_MAX/2);
        set<pair<int,int>,compare>q;
        q.insert({0,0});
        dist[0]=0;
        while(!q.empty()){
            pair<int,int>top=*q.begin();
            q.erase(q.begin());
            int f=top.first;
            int s=top.second;
            if(dist[f]<s)continue;
            if(f==n-1)return s;
            for(auto&p:graph[f]){
                int f1=p.first;
                int s1=p.second;
                if(dist[f1]>dist[f]+s1){
                    dist[f1]=dist[f]+s1;
                    q.insert({f1,dist[f1]});
                }
            }
        }
        return -1;
    }
}; 
