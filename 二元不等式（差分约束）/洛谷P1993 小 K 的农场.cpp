#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>>graph(n+1);
    vector<int>dist(n+1,INT_MAX);
    vector<bool>vis(n+1,false);
    vector<int>cnt(n+1,0);
    for(int i=0;i<m;i++){
        int op;
        cin>>op;
        if(op==1){
            int u,v,w;
            cin>>u>>v>>w;
            graph[v].push_back({u,-w});
        }
        else if(op==2){
            int u,v,w;
            cin>>u>>v>>w;
            graph[u].push_back({v,w});
        }
        else{
            int u,v;
            cin>>u>>v;
            graph[u].push_back({v,0});
            graph[v].push_back({u,0});
        }

    }
    for(int i=1;i<=n;i++){
        graph[0].push_back({i,0});
    }
    queue<int>q;
    q.push(0);
    dist[0]=0;
    cnt[0]++;
    while(!q.empty()){
        int top=q.front();
        q.pop();
        vis[top]=false;
        for(auto&[u,v]:graph[top]){
            if(dist[u]>dist[top]+v){
                dist[u]=dist[top]+v;
                if(!vis[u]){
                    vis[u]=true;
                    q.push(u);
                    cnt[u]++;
                    if(cnt[u]>n){
                        cout<<"No"<<'\n';
                        return 0;
                    }
                }
            }
        }
    }
    cout<<"Yes"<<'\n';
}