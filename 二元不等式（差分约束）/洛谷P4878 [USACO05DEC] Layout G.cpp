#include<bits/stdc++.h>
using namespace std;
bool bellman_ford(int n,vector<vector<pair<int,int>>>&graph,vector<int>&dist,vector<bool>&vis,vector<int>&cnt,queue<int>&q){
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(auto &[v,w]:graph[u]){
            if(dist[u]!=INT_MAX && dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                if(!vis[v]){
                    vis[v]=true;
                    q.push(v);
                    cnt[v]++;
                    if(cnt[v]>n)return false;
                }
            }
        }
    }
    return true;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,ml,md;
    cin>>n>>ml>>md;
    vector<vector<pair<int,int>>>graph(n+1);
    for(int i=0;i<ml;i++){
        int a,b,c;
        cin>>a>>b>>c;
        graph[a].push_back({b,c});
    }
    for(int i=0;i<md;i++){
        int a,b,c;
        cin>>a>>b>>c;
        graph[b].push_back({a,-c});
    }
    for(int i=1;i<n;i++){
        graph[i+1].push_back({i,0});
    }
    for(int i=0;i<=n;i++){
        graph[0].push_back({i,0});
    }

    vector<int>dist(n+1,INT_MAX);
    dist[0]=0;
    vector<bool>vis(n+1,0);
    vector<int>cnt(n+1,0);
    queue<int>q;
    q.push(0);
    vis[0]=true;
    if(!bellman_ford(n,graph,dist,vis,cnt,q)){
        cout<<-1;
    return 0;}
    vis.assign(n+1,false);
    cnt.assign(n+1,0);
    dist.assign(n+1,INT_MAX);
    dist[1]=0;
    q.push(1);
    vis[1]=true;
    if(!bellman_ford(n,graph,dist,vis,cnt,q)){
        cout<<-1;
    }
    else{
        if(dist[n]==INT_MAX)cout<<-2;
        else cout<<dist[n];
    }
}