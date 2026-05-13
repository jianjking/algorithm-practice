#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>>graph(n+1);
    vector<int>dist(n+1,INT_MAX);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        graph[v].push_back({u,w});
    } 
    for(int i=1;i<=n;i++){
        graph[0].push_back({i,0});
    }
    dist[0]=0;
    queue<int>q;
    q.push(0);
    vector<bool>in_queue(n+1,false);
    in_queue[0]=true;
    vector<int>cnt(n+1,0);
    cnt[0]=1;
    while(!q.empty()){
        int top=q.front();
        q.pop();
        in_queue[top]=false;
        for(auto&[to,w]:graph[top]){
            if(dist[to]>dist[top]+w){
                dist[to]=dist[top]+w;
                if(!in_queue[to]){
                    q.push(to);
                    in_queue[to]=true;
                    cnt[to]++;
                    if(cnt[to]>n){
                        cout<<"NO\n";
                        return 0;
                    }
                }
            }
        }
        }
     for(int i=1;i<=n;i++){
            if(dist[i]==INT_MAX)cout<<"2147483647 ";
            else cout<<dist[i]<<" ";
    }}
