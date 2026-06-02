#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;

int n,limitl;
long long limitw;

int sz[MAXN];
bool vis[MAXN];
int tree[MAXN];

vector<vector<pair<int,int>>>g;
vector<pair<long long,int>>path;

long long ans=0;

int lowbit(int x){
    return x&(-x);
}

void add(int x,int v){
    if(x<=0)return;
    if(x>n)return;

    for(int i=x;i<=n;i+=lowbit(i)){
        tree[i]+=v;
    }
}

int query(int x){
    if(x<=0)return 0;
    if(x>n)x=n;

    int res=0;

    for(int i=x;i>0;i-=lowbit(i)){
        res+=tree[i];
    }

    return res;
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

void dfs(int u,int fa,long long sum,int len){
    if(sum>limitw||len>limitl)return;

    path.push_back({sum,len});

    for(auto&[v,w]:g[u]){
        if(v==fa||vis[v])continue;

        dfs(v,u,sum+w,len+1);
    }
}

long long countpath(){
    if(path.empty())return 0;

    sort(path.begin(),path.end());

    long long res=0;

    for(auto&[w,len]:path){
        add(len+1,1);
    }

    int l=0;
    int r=path.size()-1;

    while(l<r){
        if(path[l].first+path[r].first>limitw){
            add(path[r].second+1,-1);
            r--;
        }
        else{
            add(path[l].second+1,-1);

            int need=limitl-path[l].second;

            res+=query(need+1);

            l++;
        }
    }

    if(l==r){
        add(path[l].second+1,-1);
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

    ans+=countpath();

    for(auto&[v,w]:g[u]){
        if(vis[v])continue;

        path.clear();

        dfs(v,u,w,1);

        ans-=countpath();
    }

    path.clear();
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
    cin>>n>>limitl>>limitw;

    g.assign(n+1,vector<pair<int,int>>());

    for(int i=1;i<n;i++){
        int v,w;
        cin>>v>>w;

        g[v].push_back({i+1,w});
        g[i+1].push_back({v,w});
    }

    solve(getrt(1,0));

    cout<<ans<<'\n';

    return 0;
}