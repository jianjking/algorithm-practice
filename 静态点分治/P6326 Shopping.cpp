#include<bits/stdc++.h>
using namespace std;

struct node{
    int w;
    int c;
    int d;
};

int n,m;
vector<node>item;
vector<int>sz;
vector<bool>vis;
vector<vector<int>>graph;
vector<vector<int>>dp;

int cntd=0;
int val[25];
int price[25];

vector<int>seg;
vector<int>ending;

int ans=0;

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

        for(auto&p:graph[u]){
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

void dfs(int u,int fa){
    seg[++cntd]=u;

    for(auto&p:graph[u]){
        if(p==fa||vis[p])continue;
        dfs(p,u);
    }

    ending[u]=cntd;
}

void calu(int u){
    cntd=0;
    dfs(u,0);

    for(int i=cntd;i>=1;i--){
        int num=seg[i];

        int cur=0;
        int tmp=item[num].d-1;

        for(int k=1;k<=tmp;k<<=1){
            val[cur]=k*item[num].w;
            price[cur]=k*item[num].c;
            cur++;
            tmp-=k;
        }

        if(tmp>0){
            val[cur]=tmp*item[num].w;
            price[cur]=tmp*item[num].c;
            cur++;
        }

        // 选择当前节点 num，至少买一件
        for(int j=m;j>=item[num].c;j--){
            dp[i][j]=dp[i+1][j-item[num].c]+item[num].w;
        }

        // 当前节点 num 额外还能买 d[num]-1 件，用二进制拆分做 01 背包
        for(int k=0;k<cur;k++){
            for(int j=m;j>=price[k];j--){
                dp[i][j]=max(dp[i][j],dp[i][j-price[k]]+val[k]);
            }
        }

        // 不选择当前节点 num，跳过 num 的整棵子树
        for(int j=0;j<=m;j++){
            dp[i][j]=max(dp[i][j],dp[ending[num]+1][j]);
        }
    }

    ans=max(ans,dp[1][m]);

    for(int i=1;i<=cntd;i++){
        for(int j=0;j<=m;j++){
            dp[i][j]=0;
        }
    }
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

    int t;
    cin>>t;

    while(t--){
        cin>>n>>m;

        ans=0;

        item.assign(n+1,{});
        sz.assign(n+1,1);
        vis.assign(n+1,false);
        dp.assign(n+2,vector<int>(m+1,0));
        graph.assign(n+1,vector<int>());
        seg.assign(n+1,0);
        ending.assign(n+1,0);

        for(int i=1;i<=n;i++){
            cin>>item[i].w;
        }

        for(int i=1;i<=n;i++){
            cin>>item[i].c;
        }

        for(int i=1;i<=n;i++){
            cin>>item[i].d;
        }

        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        solve(getrt(1,0));

        cout<<ans<<'\n';
    }

    return 0;
}