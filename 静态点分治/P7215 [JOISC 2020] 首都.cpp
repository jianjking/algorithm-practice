#include<bits/stdc++.h>
using namespace std;

int n,k;
const int MAXN=200000+5;
const int MAXK=200000+5;
const int INF=1e9;

vector<vector<int>>graph;
vector<vector<int>>color;

bool visc[MAXK];
int sz[MAXN];
bool vis[MAXN];
int belong[MAXN];
int father[MAXN];
int nodec[MAXN];
bool push[MAXN];

vector<int>used1;
vector<int>used2;

int ans=INF;

void getsz(int u,int fa){
    sz[u]=1;
    for(auto&p:graph[u]){
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
        for(auto&v:graph[u]){
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

void sign(int u,int fa,int flag){
    belong[u]=flag;
    father[u]=fa;
    for(auto&p:graph[u]){
        if(p==fa||vis[p])continue;
        sign(p,u,flag);
    }
}

void clear_used(){
    for(auto&g:used1){
        push[g]=false;
    }
    used1.clear();

    for(auto&g:used2){
        visc[g]=false;
    }
    used2.clear();
}

void calu(int u){
    sign(u,0,u);

    queue<int>q;
    q.push(u);
    push[u]=true;
    used1.push_back(u);

    int cnt=0; // 统计当前闭包里有多少种颜色

    while(!q.empty()){
        int f=q.front();
        q.pop();

        // 1. 处理当前点自己的颜色
        int c=nodec[f];
        if(!visc[c]){
            visc[c]=true;
            used2.push_back(c);
            cnt++;

            // 这个颜色的所有点都必须加入
            for(auto&p:color[c]){
                if(belong[p]!=u){
                    clear_used();
                    return;
                }

                if(!push[p]){
                    push[p]=true;
                    used1.push_back(p);
                    q.push(p);
                }
            }
        }

        // 2. 为了连通，父亲也必须加入
        if(father[f]!=0&&!push[father[f]]){
            push[father[f]]=true;
            used1.push_back(father[f]);
            q.push(father[f]);
        }
    }

    ans=min(ans,cnt);
    clear_used();
}

void solve(int u){
    vis[u]=true;
    calu(u);

    for(auto&p:graph[u]){
        if(vis[p])continue;
        solve(getrt(p,u));
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k;
    graph.assign(n+1,vector<int>());
    color.assign(k+1,vector<int>());

    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i=1;i<=n;i++){
        int c;
        cin>>c;
        nodec[i]=c;
        color[c].push_back(i);
    }

    solve(getrt(1,0));

    cout<<ans-1<<'\n';
    return 0;
}