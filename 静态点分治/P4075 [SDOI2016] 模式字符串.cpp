#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const ull mod = 499;

int n,m;
vector<ull> pre;
vector<ull> suf;

vector<int> val;
vector<vector<int>> graph;
vector<int> sz;
vector<int> deep;
vector<int> vis;

vector<long long> alls;
vector<long long> allc;
vector<long long> curs;
vector<long long> curc;

long long ans;

void getsz(int u,int fa){
    sz[u]=1;
    for(auto &p:graph[u]){
        if(p==fa||vis[p])continue;
        getsz(p,u);
        sz[u]+=sz[p];
    }
}

int getrt(int u,int fa){
    getsz(u,fa);
    int half=sz[u]/2;

    while(true){
        bool flag=true;

        for(auto &p:graph[u]){
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

void dfs(int u,int fa,int dep,ull hash){
    deep[u]=dep;

    hash=hash*mod+val[u];

    int id=(dep-1)%m+1;
    int need=m-(dep-1)%m;

    if(hash==pre[dep]){
        curc[id]++;
        ans+=alls[need];
    }

    if(hash==suf[dep]){
        curs[id]++;
        ans+=allc[need];
    }

    for(auto &p:graph[u]){
        if(p==fa||vis[p])continue;

        dfs(p,u,dep+1,hash);

        deep[u]=max(deep[u],deep[p]);
    }
}

void calu(int u){
    int maxDep=0;

    allc[1]=1;
    alls[1]=1;

    for(auto &p:graph[u]){
        if(vis[p])continue;

        dfs(p,u,2,val[u]);

        int curDep=min(deep[p],m);

        for(int i=1;i<=curDep;i++){
            allc[i]+=curc[i];
            alls[i]+=curs[i];

            curc[i]=0;
            curs[i]=0;
        }

        maxDep=max(maxDep,curDep);
    }

    for(int i=1;i<=maxDep;i++){
        allc[i]=0;
        alls[i]=0;
    }
}

void solve(int u){
    vis[u]=1;

    calu(u);

    for(auto &p:graph[u]){
        if(vis[p])continue;
        solve(getrt(p,u));
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c;
    cin>>c;

    while(c--){
        ans=0;

        cin>>n>>m;

        string node;
        cin>>node;

        val.assign(n+1,0);
        graph.assign(n+1,vector<int>());
        sz.assign(n+1,0);
        deep.assign(n+1,0);
        vis.assign(n+1,0);

        pre.assign(n+1,0);
        suf.assign(n+1,0);

        allc.assign(m+1,0);
        alls.assign(m+1,0);
        curc.assign(m+1,0);
        curs.assign(m+1,0);

        for(int i=1;i<=n;i++){
            val[i]=node[i-1]-'A'+1;
        }

        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        string s;
        cin>>s;

        string tmp=s;
        reverse(tmp.begin(),tmp.end());

        ull now=1;

        for(int i=1;i<=n;i++){
            pre[i]=pre[i-1]+now*(s[(i-1)%m]-'A'+1);
            suf[i]=suf[i-1]+now*(tmp[(i-1)%m]-'A'+1);
            now*=mod;
        }

        solve(getrt(1,0));

        cout<<ans<<"\n";
    }

    return 0;
}