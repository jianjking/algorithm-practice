#include<bits/stdc++.h> 
using namespace std;
struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b)const {
        if(a.first==b.first)return a.second>b.second;
        return a.first<b.first;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k;
    cin>>k;
    vector<vector<pair<int,int>>>graph(k);
    for(int i=0;i<k;i++){
        graph[i].emplace_back((i*10)%k,0);
        graph[i].emplace_back((i+1)%k,1);
    }
    vector<int>dist(k,INT_MAX);
    dist[1]=0;
    set<pair<int,int>,compare>q;
    q.insert({0,1});
   while(!q.empty()){
        auto [d,u]=*q.begin();
        q.erase(q.begin());
        if(dist[u]<d)continue;
        for(auto [v,w]:graph[u]){
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                q.insert({dist[v],v});
            }
        }
    }
    cout<<dist[0]+1<<'\n';

}