#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n,k;
int ans = INF;

vector<vector<pair<int,int>>> g;
vector<int> sz;
vector<bool> vis;

vector<int> best;
vector<int> used;
vector<pair<int,int>> cur;

void getsize(int u,int fa){
    sz[u]=1;
    for(auto&[v,w]:g[u]){
        if(v==fa||vis[v])continue;
        getsize(v,u);
        sz[u]+=sz[v];
    }
}

int getroot(int u,int fa){
    getsize(u,fa);
    int half=sz[u]/2;

    while(true){
        bool flag=true;

        for(auto&[v,w]:g[u]){
            if(v==fa||vis[v])continue;

            if(sz[v]>half){
                flag=false;
                fa=u;
                u=v;
                break;
            }
        }

        if(flag)return u;
    }
}

void dfs(int u,int fa,int dis,int dep){
    if(dis>k)return;

    cur.push_back({dis,dep});

    for(auto&[v,w]:g[u]){
        if(v==fa||vis[v])continue;
        dfs(v,u,dis+w,dep+1);
    }
}

void calu(int u){
    used.clear();

    best[0]=0;
    used.push_back(0);

    for(auto&[v,w]:g[u]){
        if(vis[v])continue;

        cur.clear();
        dfs(v,u,w,1);

        for(auto&[dis,dep]:cur){
            int need=k-dis;

            if(need>=0&&best[need]!=INF){
                ans=min(ans,best[need]+dep);
            }
        }

        for(auto&[dis,dep]:cur){
            if(best[dis]==INF){
                used.push_back(dis);
            }
            best[dis]=min(best[dis],dep);
        }
    }

    for(int x:used){
        best[x]=INF;
    }
}

void solve(int u){
    vis[u]=true;

    calu(u);

    for(auto&[v,w]:g[u]){
        if(vis[v])continue;

        int root=getroot(v,u);
        solve(root);
    }
}

int main(){
    cin>>n>>k;

    g.assign(n,vector<pair<int,int>>());
    sz.assign(n,0);
    vis.assign(n,false);
    best.assign(k+1,INF);

    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin>>u>>v>>w;

        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    int root=getroot(0,-1);
    solve(root);

    if(ans==INF)cout<<-1<<endl;
    else cout<<ans<<endl;

    return 0;
}