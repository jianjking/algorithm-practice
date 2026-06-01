#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e4+10;
int ans=0;
int vis[MAXN];
int sz[MAXN];
int all[3];
int cur[3];
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
void getsize(int u,int fa,vector<vector<pair<int,int>>>&graph){
    sz[u]=1;
    for(auto&p:graph[u]){
        if(p.first!=fa&&!vis[p.first]){
            getsize(p.first,u,graph);
            sz[u]+=sz[p.first];
        }
    }
}
int getheaven(int u,int fa,vector<vector<pair<int,int>>>&graph){
    getsize(u,fa,graph);
    int total=sz[u];
    int half=total/2;
    int father=fa;

    bool pos=false;
    while(!pos){
        pos=true;
        for(auto&p:graph[u]){
            int v=p.first;
            if(!vis[v]&&v!=father&&sz[v]>half){
                father=u;
                u=v;
                pos=false;
                break;
            }
        }
    }
    return u;
}
void dfs(int u,int fa,int w,vector<vector<pair<int,int>>>&graph){
     cur[w]++;
     for(auto&p:graph[u]){
        if(p.first!=fa&&!vis[p.first]){
            dfs(p.first,u,(p.second+w)%3,graph);
        }
     }
}
void calu(int u,vector<vector<pair<int,int>>>&graph){
      all[0]=1;
      all[1]=0;
      all[2]=0;
      ans++;
      for(auto&p:graph[u]){
        cur[0]=0;
        cur[1]=0;
        cur[2]=0;
        if(!vis[p.first]){
            dfs(p.first,u,p.second,graph);
            ans+=(cur[0]*all[0]+cur[1]*all[2]+cur[2]*all[1])*2;
            all[0]+=cur[0];
            all[1]+=cur[1];
            all[2]+=cur[2];
        }
      }
}
void solve(int u,vector<vector<pair<int,int>>>&graph){
    vis[u]=true;
    calu(u,graph);
   for(auto&p:graph[u]){
    if(!vis[p.first]){
        solve(getheaven(p.first,u,graph),graph);
    }
   }
}
int main(){
    int n;
    cin>>n;
    vector<vector<pair<int,int>>>graph(n+1);
    for(int i=1;i<n;i++){
        int x,y,w;
        cin>>x>>y>>w;
        graph[x].push_back({y,w%3});
        graph[y].push_back({x,w%3});
    }
    int u=getheaven(1,0,graph);
    solve(u,graph);
    int g=gcd(ans,n*n);
    cout<<ans/g<<'/'<<n*n/g<<'\n';
}