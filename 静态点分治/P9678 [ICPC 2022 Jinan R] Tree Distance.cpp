#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = (1LL << 60);

int n,q;

struct node{
    int l;
    int r;
    ll dist;
};

struct Query{
    int l;
    int r;
    int id;
};

vector<vector<pair<int,ll>>> graph;
vector<int> sz;
vector<int> vis;

vector<node> arr;
vector<pair<int,ll>> path;
stack<pair<int,ll>> s;

vector<ll> tree;
vector<ll> ans;

void getsz(int u,int fa){
    sz[u]=1;
    for(auto &p:graph[u]){
        int v=p.first;
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

        for(auto &[p,w]:graph[u]){
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

void dfs(int u,int fa,ll dist){
    path.push_back({u,dist});

    for(auto &[p,w]:graph[u]){
        if(p==fa||vis[p])continue;
        dfs(p,u,dist+w);
    }
}

void clearStack(){
    while(!s.empty())s.pop();
}

void stackAdd(pair<int,ll> cur){
    while(!s.empty()&&s.top().second>=cur.second){
        pair<int,ll> tmp=s.top();
        s.pop();

        int a=min(tmp.first,cur.first);
        int b=max(tmp.first,cur.first);
        ll d=tmp.second+cur.second;

        arr.push_back({a,b,d});
    }

    s.push(cur);
}

void calu(int u){
    path.clear();

    /*
        注意这里是 dfs(u,0,0)
        要把当前点分治的重心 u 自己也放进去。
    */
    dfs(u,0,0);

    sort(path.begin(),path.end(),[](pair<int,ll> a,pair<int,ll> b){
        return a.first<b.first;
    });

    clearStack();

    for(auto &p:path){
        stackAdd(p);
    }

    clearStack();

    for(int i=(int)path.size()-1;i>=0;i--){
        stackAdd(path[i]);
    }

    path.clear();
    clearStack();
}

void solve(int u){
    vis[u]=true;

    calu(u);

    for(auto &[p,w]:graph[u]){
        if(vis[p])continue;
        solve(getrt(p,u));
    }
}

void build(int l,int r,int i){
    tree[i]=INF;

    if(l==r)return;

    int mid=(l+r)/2;
    build(l,mid,i*2);
    build(mid+1,r,i*2+1);
}

void update(int pos,ll val,int l,int r,int i){
    if(l==r){
        tree[i]=min(tree[i],val);
        return;
    }

    int mid=(l+r)/2;

    if(pos<=mid){
        update(pos,val,l,mid,i*2);
    }
    else{
        update(pos,val,mid+1,r,i*2+1);
    }

    tree[i]=min(tree[i*2],tree[i*2+1]);
}

ll query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }

    int mid=(l+r)/2;
    ll res=INF;

    if(jobl<=mid){
        res=min(res,query(jobl,jobr,l,mid,i*2));
    }

    if(jobr>mid){
        res=min(res,query(jobl,jobr,mid+1,r,i*2+1));
    }

    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;

    graph.assign(n+1,vector<pair<int,ll>>());
    sz.assign(n+1,0);
    vis.assign(n+1,0);

    for(int i=1;i<n;i++){
        int a,b;
        ll w;
        cin>>a>>b>>w;

        graph[a].push_back({b,w});
        graph[b].push_back({a,w});
    }

    cin>>q;

    vector<Query> querys(q+1);
    ans.assign(q+1,-1);

    for(int i=1;i<=q;i++){
        cin>>querys[i].l>>querys[i].r;
        querys[i].id=i;
    }

    solve(getrt(1,0));

    sort(arr.begin(),arr.end(),[](node a,node b){
        return a.r<b.r;
    });

    sort(querys.begin()+1,querys.end(),[](Query a,Query b){
        return a.r<b.r;
    });

    tree.assign(n*4+5,INF);
    build(1,n,1);

    int j=0;

    for(int i=1;i<=q;i++){
        int l=querys[i].l;
        int r=querys[i].r;
        int id=querys[i].id;

        while(j<(int)arr.size()&&arr[j].r<=r){
            update(arr[j].l,arr[j].dist,1,n,1);
            j++;
        }

        if(l==r){
            ans[id]=-1;
        }
        else{
            ll res=query(l,r,1,n,1);

            if(res==INF)ans[id]=-1;
            else ans[id]=res;
        }
    }

    for(int i=1;i<=q;i++){
        cout<<ans[i]<<'\n';
    }

    return 0;
}