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
    int minTime(int n, vector<vector<int>>& edges) {
        vector<vector<vector<int>>>graph(n);
        for(auto&p:edges){
           graph[p[0]].push_back({p[1],p[2],p[3]});
        }
        vector<int>dist(n,INT_MAX);
        dist[0]=0;
        set<pair<int,int>,compare>q;
        q.insert({0,0});
        while(!q.empty()){
            int f=(*q.begin()).first;
            int s=(*q.begin()).second;
            q.erase(q.begin());
            if(f==n-1)return s;
            if(dist[f]<s)continue;
            for(auto&p:graph[f]){
                if(s>p[2])continue;
                int tmp=max(p[1]+1,s+1);
                if(dist[p[0]]>tmp){
                    dist[p[0]]=tmp;
                    q.insert({p[0],dist[p[0]]});
                }
            }
        }
        return -1;
    }
};