#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int ans=INT_MAX;
vector<vector<pair<int,int>>>graph;
vector<pair<int,int>>query;
int sz[MAXN];
bool vis[MAXN];
int belong[MAXN];
int dist[MAXN];
void getsz(int u,int fa){
    sz[u]=1;
    for(auto&[p,w]:graph[u]){
        if(p==fa||vis[p])continue;
        getsz(p,u);
        sz[p]+=sz[u];
    }
}
int getrt(int u,int fa){
    getsz(u,fa);
    int half=sz[u]/2;
    while(true){
        bool flag=true;
        for(auto&[p,w]:graph[u]){
            if(p==fa||vis[p])continue;
            if(sz[p]>half){
                flag=false;
                fa=u;
                u=p;
                break;
            }
        }
        if(flag)return u;
    }
}
void dfs(int son,int fa,int val,int sign){
    dist[son]=val;
    belong[son]=sign;
    for(auto&[p,w]:graph[son]){
        if(p==fa)continue;
        dfs(p,son,val+w,sign);
    }
}
void solve(int u){
    while(true){
        int rt=getrt(u,0);
        vis[rt]=true;
        for(auto&[p,w]:graph[u]){
             dfs(p,u,w,p);
        }
        int son=0;
        int mxdist=INT_MIN;
        for(int i=0;i<m;i++){
             int cur=dist[query[i].first]+dist[query[i].second];
             if(cur>mxdist){
                 mxdist=cur;
                 son=belong[query[i].first]==belong[query[i].second]?belong[query[i].first]:0;
             }
             else if(cur==mxdist){
                if(belong[query[i].first]!=belong[query[i].second]||(belong[query[i].first]||son!=belong[query[i].first])){
                    son=0;
                }
             }
        }
        ans=min(ans,mxdist);
        if(son==0)break;
        u=son;
    }
}
int n,m;
int main(){
   cin>>n>>m;
graph.assign(n+1,vector<pair<int,int>>());
query.assign(m,pair<int,int>());
 for(int i=1;i<n;i++){
    int u,v,w;
    cin>>u>>v>>w;
    graph[u].push_back({v,w});
    graph[v].push_back({u,w});
 }
for(int i=0;i<m;i++){
    cin>>query[i].first>>query[i].second;
}
solve(1);
cout<<ans<<'\n';
}