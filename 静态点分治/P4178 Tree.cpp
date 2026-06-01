#include<bits/stdc++.h>
using namespace std;
const int MAXN=4*1e4+5;
vector<vector<pair<int,int>>>g;
vector<int>dis;
int sz[MAXN];
bool vis[MAXN];
int n;
int k;
int ans=0;
void getsz(int u,int fa){
    sz[u]=1;
    for(auto&[v,w]:g[u]){
        if(v==fa||vis[v])continue;
        getsz(v,u);
        sz[u]+=sz[v];
    }
}
int getrt(int u,int fa){
    getsz(u,fa);
    int half=sz[u]/2;
    while(true){
        bool flag=true;
    for(auto&[v,w]:g[u]){
        if(v==fa||vis[v])continue;
        if(sz[v]>half){
            fa=u;
            u=v;
            flag=false;
            break;
        }
    }
    if(flag)return u;
}
}
void dfs(int u,int fa,int w){
   dis.push_back(w);
   for(auto&[v,ww]:g[u]){
     if(v==fa||vis[v])continue;
     dfs(v,u,w+ww);
   }
}
void calu(int u){
        dis.push_back(0);
     for(auto&[v,w]:g[u]){
        if(vis[v])continue;
           dfs(v,u,w);
     }
     sort(dis.begin(),dis.end());
     int l=0;
     int r=dis.size()-1;
     while(l<r){
        if(dis[l]+dis[r]<=k){
            ans+=r-l;
            l++;
        }
        else r--;
     }
     dis.clear();
     for(auto&[v,w]:g[u]){
        if(vis[v])continue;
        dfs(v,u,w);
        sort(dis.begin(),dis.end());
        l=0;
        r=dis.size()-1;
        while(l<r){
            if(dis[l]+dis[r]<=k){
                ans-=r-l;
                l++;
            }
            else r--;
        }
        dis.clear();
     }
}
void solve(int u){
     vis[u]=true;
     calu(u);
     for(auto&[v,w]:g[u]){
        if(vis[v])continue;
        solve(getrt(v,u));
     }
}
int main(){
    cin>>n>>k;
    g.assign(n+1,vector<pair<int,int>>());
   for(int i=1;i<n;i++){
    int u,v,w;
    cin>>u>>v>>w;
    g[u].push_back({v,w});
    g[v].push_back({u,w});
   }
   int rt=getrt(1,0);
   solve(rt);
   cout<<ans<<'\n';

}