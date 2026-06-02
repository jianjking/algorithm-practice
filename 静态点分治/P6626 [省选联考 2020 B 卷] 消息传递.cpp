#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
const int MAXq=1e5+5;

int n,m;
vector<vector<int>>g;
bool vis[MAXN];
int sz[MAXN];
int dis[MAXN];
int ans[MAXq];

vector<pair<int,int>>query;
vector<vector<pair<int,int>>>q;
vector<int>used;

void adddis(int dep){
    if(dis[dep]==0)used.push_back(dep);
    dis[dep]++;
}

void cleardis(){
    for(auto&p:used){
        dis[p]=0;
    }
    used.clear();
}

void getsz(int u,int fa){
    sz[u]=1;
    for(auto&p:g[u]){
        if(vis[p]||p==fa)continue;
        getsz(p,u);
        sz[u]+=sz[p];
    }
}

int getrt(int u,int fa){
    getsz(u,fa);
    int half=sz[u]/2;

    while(true){
        bool flag=true;

        for(auto&p:g[u]){
            if(p==fa||vis[p])continue;

            if(sz[p]>half){
                fa=u;
                u=p;
                flag=false;
                break;
            }
        }

        if(flag)return u;
    }
}

void dfs(int u,int fa,int dep){
    adddis(dep);

    for(auto&p:q[u]){
        if(dep>p.first)continue;
        query.push_back({p.first-dep,p.second});
    }

    for(auto&p:g[u]){
        if(vis[p]||p==fa)continue;
        dfs(p,u,dep+1);
    }
}

void calu(int u){
    adddis(0);

    for(auto&p:q[u]){
        query.push_back({p.first,p.second});
    }

    for(auto&p:g[u]){
        if(vis[p])continue;
        dfs(p,u,1);
    }

    for(auto&p:query){
        ans[p.second]+=dis[p.first];
    }

    cleardis();
    query.clear();

    for(auto&p:g[u]){
       if(vis[p])continue;

       dfs(p,u,1);

       for(auto&p:query){
           ans[p.second]-=dis[p.first];
       }

       cleardis();
       query.clear();
    }
}

void solve(int u){
    vis[u]=true;

    calu(u);

    for(auto&p:g[u]){
        if(vis[p])continue;
        solve(getrt(p,u));
    }
}

int main(){
    int t;
    cin>>t;

    while(t--){
        cin>>n>>m;

        g.assign(n+1,vector<int>());
        q.assign(n+1,vector<pair<int,int>>());

        for(int i=0;i<=n;i++){
            vis[i]=false;
            sz[i]=0;
        }

        for(int i=0;i<m;i++){
            ans[i]=0;
        }

        for(int i=0;i<n-1;i++){
            int a,b;
            cin>>a>>b;

            g[a].push_back(b);
            g[b].push_back(a);
        }

        for(int i=0;i<m;i++){
            int x,k;
            cin>>x>>k;

            q[x].push_back({k,i});
        }

        solve(getrt(1,0));

        for(int i=0;i<m;i++){
            cout<<ans[i]<<'\n';
        }
    }

    return 0;
}