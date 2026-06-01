#include<bits/stdc++.h>
using namespace std;
unordered_set<int>pre;
unordered_set<int>cur;
void getsize(int x,int fa,vector<vector<pair<int,int>>>&g,vector<int>&sz,vector<bool>&vis){
    sz[x]=1;
    for(auto&p:g[x]){
        int t=p.first;
        if(t==fa||vis[t])continue;
        getsize(t,x,g,sz,vis);
        sz[x]+=sz[t];
    }
}
int findheave(int x,int fa,vector<vector<pair<int,int>>>&g,vector<int>&sz,vector<bool>&vis){
    getsize(x,fa,g,sz,vis);
    int half=sz[x]/2;
    while(true){
        bool find=true;
    for(auto&p:g[x]){
        int y=p.first;
        if(y==fa||vis[y])continue;
        if(sz[y]>half){
            find=false;
            fa=x;
            x=y;
            break;
        }
    }
    if(find)return x;
}
}
void dfs(int x,int fa,vector<vector<pair<int,int>>>&g,vector<bool>&vis,int sum,vector<int>&query,vector<bool>&ans){
    cur.insert(sum);
    for(auto&p:g[x]){
        int t=p.first;
        if(t==fa||vis[t])continue;
        dfs(t,x,g,vis,sum+p.second,query,ans);
    }
}
void calu(int x,vector<vector<pair<int,int>>>&g,vector<bool>&vis,vector<int>&query,vector<bool>&ans){
    pre.clear();
    pre.insert(0);
    for(auto&p:g[x]){
        if(vis[p.first])continue;
        dfs(p.first,x,g,vis,p.second,query,ans);
        for(int i=0;i<query.size();i++){
    if(ans[i])continue;
    int q=query[i];
    for(int v:cur){
        if(pre.count(q-v)){
            ans[i]=true;
            break;
        }
    }
}
        for(int v:cur)pre.insert(v);
        cur.clear();
    }
}
void solve(int u,vector<vector<pair<int,int>>>&g,vector<int>&sz,vector<bool>&vis,vector<int>&query,vector<bool>&ans){
    vis[u]=true;
    calu(u,g,vis,query,ans);
    for(auto&p:g[u]){
        int t=p.first;
        if(vis[t])continue;
        solve(findheave(t,u,g,sz,vis),g,sz,vis,query,ans);
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>>g(n+1);
    for(int i=1;i<n;i++){
        int x,y,w;
        cin>>x>>y>>w;
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }
    vector<int>query(m);
    for(int i=0;i<m;i++){
        cin>>query[i];
    }
    vector<bool>ans(m,false);
    vector<int>sz(n+1);
    vector<bool>vis(n+1,false);
    int root=findheave(1,0,g,sz,vis);
    solve(root,g,sz,vis,query,ans); 
    for(int i=0;i<m;i++){
        if(ans[i])cout<<"AYE\n";
        else cout<<"NAY\n";
    }
}