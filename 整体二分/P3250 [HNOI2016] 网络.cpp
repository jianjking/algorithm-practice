#include<bits/stdc++.h>
using namespace std;

const int MAXN=200000+5;
const int MAXM=200000+5;

int father[MAXN];
int dfn[MAXN];
int depth[MAXN];
int sz[MAXN];
int st[MAXN][20];
int tree[MAXN];
int ans[MAXM];
int cnt=0;
int n,m;

struct str{
   int type;
   int u;
   int v;
   int d;
   int time;
};

int lowbit(int i){
    return i&(-i);
}

void add(int i,int v){
     while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
     }
}

int querysum(int i){
    int ans=0;
    while(i>0){
       ans+=tree[i];
       i-=lowbit(i);
    }
    return ans;
}

int lca(int u,int v){
     if(depth[u]<depth[v]) swap(u,v);

     for(int i=19;i>=0;i--){
        if(depth[st[u][i]]>=depth[v]){
            u=st[u][i];
        }
     }

     if(u==v) return u;

     for(int i=19;i>=0;i--){
        if(st[u][i]!=st[v][i]){
            u=st[u][i];
            v=st[v][i];
        }
     }

     return st[u][0];
}

void addnum(int u,int v,int edge){
    int f=lca(u,v);
    int ff=st[f][0];

    add(dfn[u],edge);
    add(dfn[v],edge);
    add(dfn[f],-edge);

    if(ff!=0){
        add(dfn[ff],-edge);
    }
}

void dfs(int son,int f,vector<vector<int>>&graph){
    father[son]=f;
    depth[son]=depth[f]+1;
    dfn[son]=++cnt;
    sz[son]=1;
    st[son][0]=f;

    for(int i=1;i<20;i++){
        st[son][i]=st[st[son][i-1]][i-1];
    }

    for(auto &p:graph[son]){
        if(p==f) continue;
        dfs(p,son,graph);
        sz[son]+=sz[p];
    }
}

void erfen(int l,int r,int ql,int qr,vector<str>&query){
    if(ql>qr) return;

    if(l==r){
        for(int i=ql;i<=qr;i++){
            if(query[i].type==2){
                ans[query[i].time]=l;
            }
        }
        return;
    }

    vector<str> qql;
    vector<str> qqr;

    int mid=(l+r)/2;

    int total=0; // 当前扫描到的时刻，重要度 > mid 的活跃请求数量

    for(int i=ql;i<=qr;i++){
        if(query[i].type==0){
            if(query[i].d>mid){
                addnum(query[i].u,query[i].v,1);
                total++;
                qqr.push_back(query[i]);
            }
            else{
                qql.push_back(query[i]);
            }
        }
        else if(query[i].type==1){
            if(query[i].d>mid){
                addnum(query[i].u,query[i].v,-1);
                total--;
                qqr.push_back(query[i]);
            }
            else{
                qql.push_back(query[i]);
            }
        }
        else{
            int x=dfn[query[i].d];

            int part=querysum(x+sz[query[i].d]-1)-querysum(x-1);

            if(total>part){
                qqr.push_back(query[i]);
            }
            else{
                qql.push_back(query[i]);
            }
        }
    }

    int pos=ql;

    for(int i=0;i<(int)qql.size();i++){
        query[pos++]=qql[i];
    }

    for(int i=0;i<(int)qqr.size();i++){
        query[pos]=qqr[i];

        // 撤销这一层加进树状数组的路径影响
        if(qqr[i].type==0){
            addnum(qqr[i].u,qqr[i].v,-1);
        }
        if(qqr[i].type==1){
            addnum(qqr[i].u,qqr[i].v,1);
        }

        pos++;
    }

    int lsiz=qql.size();

    erfen(l,mid,ql,ql+lsiz-1,query);
    erfen(mid+1,r,ql+lsiz,qr,query);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;

    vector<vector<int>>graph(n+1);

    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1,0,graph);

    vector<str> query(m+1);

    for(int i=1;i<=m;i++){
       cin>>query[i].type;

       if(query[i].type==0){
          cin>>query[i].u>>query[i].v>>query[i].d;
       }
       else if(query[i].type==1){
          int t;
          cin>>t;
          query[i].u=query[t].u;
          query[i].v=query[t].v;
          query[i].d=query[t].d;
       }
       else{
           cin>>query[i].d;
       }

       query[i].time=i;
    }

    for(int i=1;i<=m;i++){
        ans[i]=-1;
    }

    erfen(0,1000000001,1,m,query);

    for(int i=1;i<=m;i++){
        if(ans[i]==-1) continue;

        if(ans[i]==0){
            cout<<-1<<'\n';
        }
        else{
            cout<<ans[i]<<'\n';
        }
    }

    return 0;
}
