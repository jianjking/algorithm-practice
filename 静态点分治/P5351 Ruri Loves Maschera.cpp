#include<bits/stdc++.h>
using namespace std;

int n,L,R;
const int MAXN=1e5+5;

vector<vector<pair<int,int>>>g;

int sz[MAXN];
bool vis[MAXN];

vector<pair<int,int>>path;
int tree[MAXN];

long long ans=0;

int lowbit(int i){
    return i&(-i);
}

void add(int i,int v){
    if(i<=0)return;
    if(i>n)return;

    while(i<=n){
         tree[i]+=v;
         i+=lowbit(i);
    }
}

int query(int i){
    if(i<=0)return 0;
    if(i>n)i=n;

    int ans=0;

    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
    }

    return ans;
}

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
                flag=false;
                fa=u;
                u=v;
                break;
            }
        }

        if(flag)return u;
    }
}

void dfs(int u,int fa,int w,int len){
    if(len>R)return;

    path.push_back({w,len});

    for(auto&[v,ww]:g[u]){
        if(v==fa||vis[v])continue;

        dfs(v,u,max(w,ww),len+1);
    }
}

long long calc(){
    long long res=0;

    sort(path.begin(),path.end(),[](pair<int,int>&a,pair<int,int>&b){
        if(a.first!=b.first)return a.first<b.first;
        return a.second<b.second;
    });

    for(int i=0;i<path.size();i++){
        add(path[i].second+1,1);
    }

    for(int i=(int)path.size()-1;i>=0;i--){
        add(path[i].second+1,-1);

        int l=L-path[i].second;
        int r=R-path[i].second;

        res+=1LL*path[i].first*(query(r+1)-query(l));
    }

    return res;
}

void calu(int u){
    path.clear();

    path.push_back({0,0});

    for(auto&[v,w]:g[u]){
        if(vis[v])continue;
        dfs(v,u,w,1);
    }

    ans+=calc();

    path.clear();

    for(auto&[v,w]:g[u]){
        if(vis[v])continue;

        dfs(v,u,w,1);

        ans-=calc();

        path.clear();
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
   cin>>n>>L>>R;
   g.assign(n+1,vector<pair<int,int>>());
   for(int i=1;i<n;i++){
    int u,v,w;
    cin>>u>>v>>w;
    g[u].push_back({v,w});
    g[v].push_back({u,w});
   }
   solve(getrt(1,0));
   cout<<ans*2<<'\n';
   return 0;
}