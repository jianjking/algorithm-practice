#include<bits/stdc++.h>
using namespace std;

const int MAXN=200000+5;
const long long NEG=-(1LL<<60);

int n,m,l,r;
vector<vector<pair<int,int>>>graph;

long long val[MAXN];
int sz[MAXN];
bool vis[MAXN];

long long pretree[MAXN<<2];
long long curtree[MAXN<<2];

vector<pair<int,long long>>path;
vector<pair<int,long long>>prepath;

vector<int>used1;
vector<int>used2;

long long ans=NEG;

void build(long long *tree,int l,int r,int nums){
    tree[nums]=NEG;
    if(l==r)return;
    int mid=(l+r)/2;
    build(tree,l,mid,nums*2);
    build(tree,mid+1,r,nums*2+1);
}

void update(long long *tree,int target,long long v,int l,int r,int nums){
    if(l==r){
        tree[nums]=max(tree[nums],v);
        return;
    }
    int mid=(l+r)/2;
    if(target<=mid){
        update(tree,target,v,l,mid,nums*2);
    }
    else{
        update(tree,target,v,mid+1,r,nums*2+1);
    }
    tree[nums]=max(tree[nums*2],tree[nums*2+1]);
}

void change(long long *tree,int target,long long v,int l,int r,int nums){
    if(l==r){
        tree[nums]=v;
        return;
    }
    int mid=(l+r)/2;
    if(target<=mid){
        change(tree,target,v,l,mid,nums*2);
    }
    else{
        change(tree,target,v,mid+1,r,nums*2+1);
    }
    tree[nums]=max(tree[nums*2],tree[nums*2+1]);
}

long long query(long long *tree,int lt,int rt,int l,int r,int nums){
    if(lt<=l&&r<=rt)return tree[nums];
    int mid=(l+r)/2;
    if(rt<=mid){
        return query(tree,lt,rt,l,mid,nums*2);
    }
    else if(lt>mid){
        return query(tree,lt,rt,mid+1,r,nums*2+1);
    }
    else{
        return max(query(tree,lt,rt,l,mid,nums*2),
                   query(tree,lt,rt,mid+1,r,nums*2+1));
    }
}

long long ask(long long *tree,int lt,int rt){
    lt=max(lt,0);
    rt=min(rt,n);
    if(lt>rt)return NEG;
    return query(tree,lt,rt,0,n,1);
}

void getsz(int u,int fa){
    sz[u]=1;
    for(auto &[p,c]:graph[u]){
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
        for(auto &[p,c]:graph[u]){
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

void dfs(int u,int precolor,long long sum,int edge,int fa){
    path.push_back({edge,sum});

    for(auto &[p,c]:graph[u]){
        if(p==fa||vis[p])continue;

        if(c==precolor){
            dfs(p,c,sum,edge+1,u);
        }
        else{
            dfs(p,c,sum+val[c],edge+1,u);
        }
    }
}

void calu(int u){
    update(pretree,0,0,0,n,1);
    used2.push_back(0);

    int lastcolor=-1;

    path.clear();
    prepath.clear();
    used1.clear();

    for(auto &edgeinfo:graph[u]){
        int to=edgeinfo.first;
        int col=edgeinfo.second;

        if(vis[to])continue;

        if(lastcolor!=-1&&col!=lastcolor){
            for(auto &x:prepath){
                update(pretree,x.first,x.second,0,n,1);
                used2.push_back(x.first);
            }

            for(auto &x:used1){
                change(curtree,x,NEG,0,n,1);
            }

            used1.clear();
            prepath.clear();
        }

        lastcolor=col;

        path.clear();
        dfs(to,col,val[col],1,u);

        for(auto &[d,sum]:path){
            int l1=l-d;
            int r1=r-d;

            long long pre=ask(pretree,l1,r1);
            if(pre!=NEG){
                ans=max(ans,pre+sum);
            }

            long long cur=ask(curtree,l1,r1);
            if(cur!=NEG){
                ans=max(ans,cur+sum-val[col]);
            }
        }

        for(auto &[d,sum]:path){
            update(curtree,d,sum,0,n,1);
            used1.push_back(d);
            prepath.push_back({d,sum});
        }
    }

    for(auto &x:used1){
        change(curtree,x,NEG,0,n,1);
    }

    for(auto &x:used2){
        change(pretree,x,NEG,0,n,1);
    }

    used1.clear();
    used2.clear();
    path.clear();
    prepath.clear();
}

void solve(int u){
    vis[u]=true;
    calu(u);

    for(auto &[p,c]:graph[u]){
        if(vis[p])continue;
        solve(getrt(p,u));
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m>>l>>r;

    graph.assign(n+1,vector<pair<int,int>>());

    for(int i=1;i<=m;i++){
        cin>>val[i];
    }

    for(int i=1;i<n;i++){
        int u,v,c;
        cin>>u>>v>>c;
        graph[u].push_back({v,c});
        graph[v].push_back({u,c});
    }

    for(int i=1;i<=n;i++){
        sort(graph[i].begin(),graph[i].end(),[](pair<int,int>a,pair<int,int>b){
            return a.second<b.second;
        });
    }

    build(pretree,0,n,1);
    build(curtree,0,n,1);

    if(l<=0&&0<=r){
        ans=max(ans,0LL);
    }

    solve(getrt(1,0));

    cout<<ans<<"\n";

    return 0;
}