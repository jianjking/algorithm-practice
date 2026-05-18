#include<bits/stdc++.h>
using namespace std;

struct str{
    int e;
    int c;
    int time;
};

struct str1{
    int u;
    int v;
    int color;
};

int root(int f,int color,vector<vector<int>>&fa){
    while(fa[color][f]!=f) f=fa[color][f];
    return f;
}

bool unio(int u,int v,int color,vector<vector<int>>&fa,vector<vector<int>>&sz,vector<str1>&s,int&cur){
    if(u==v) return false;
    if(sz[color][u]<sz[color][v]) swap(u,v);
    fa[color][v]=u;
    sz[color][u]+=sz[color][v];
    s[cur++]={u,v,color};
    return true;
}

void undo(vector<vector<int>>&fa,vector<vector<int>>&sz,vector<str1>&s,int&cur){
    cur--;
    int f=s[cur].u;
    int son=s[cur].v;
    int color=s[cur].color;
    fa[color][son]=son;
    sz[color][f]-=sz[color][son];
}

void addedge(int qid,int lt,int rt,int l,int r,int nums,vector<vector<int>>&tree){
    if(lt<=l&&r<=rt){
        tree[nums].push_back(qid);
        return;
    }
    int mid=(l+r)/2;
    if(lt<=mid){
        addedge(qid,lt,rt,l,mid,2*nums,tree);
    }
    if(rt>mid){
        addedge(qid,lt,rt,mid+1,r,2*nums+1,tree);
    }
}

void dfs(
    int l,int r,int nums,int n,
    vector<pair<int,int>>&edge,
    vector<str>&query,
    vector<vector<int>>&fa,
    vector<vector<int>>&sz,
    vector<str1>&s,
    int&cur,
    vector<vector<int>>&tree,
    vector<int>&last
){
    int cnt=0;

    for(auto &p:tree[nums]){
        int color=query[p].c;
        if(color==0) continue;

        int u=edge[query[p].e].first;
        int v=edge[query[p].e].second;

        int fu=root(u,color,fa);
        int fv=root(v,color,fa);
        int fun=root(u+n,color,fa);
        int fvn=root(v+n,color,fa);

        if(unio(fu,fvn,color,fa,sz,s,cur)) cnt++;
        if(unio(fv,fun,color,fa,sz,s,cur)) cnt++;
    }

    if(l==r){
        int u=edge[query[l].e].first;
        int v=edge[query[l].e].second;
        int color=query[l].c;

        int fu=root(u,color,fa);
        int fv=root(v,color,fa);

        if(fu==fv){
            query[l].c=last[query[l].e];
            cout<<"NO"<<'\n';
        }
        else{
            last[query[l].e]=query[l].c;
            cout<<"YES"<<'\n';
        }
    }
    else{
        int mid=l+(r-l)/2;
        dfs(l,mid,2*nums,n,edge,query,fa,sz,s,cur,tree,last);
        dfs(mid+1,r,2*nums+1,n,edge,query,fa,sz,s,cur,tree,last);
    }

    for(int i=0;i<cnt;i++){
        undo(fa,sz,s,cur);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,k,q;
    cin>>n>>m>>k>>q;

    vector<pair<int,int>>edge(m+1);
    for(int i=1;i<=m;i++){
        cin>>edge[i].first>>edge[i].second;
    }

    vector<str>query(q+1);
    for(int i=1;i<=q;i++){
        cin>>query[i].e>>query[i].c;
        query[i].time=i;
    }

    vector<int>pos(m+1,q+1);
    vector<vector<int>>tree(4*q+5);

    for(int i=q;i>=1;i--){
        int id=query[i].e;
        if(i+1<=pos[id]-1){
            addedge(i,i+1,pos[id]-1,1,q,1,tree);
        }
        pos[id]=i;
    }

    vector<vector<int>>fa(k+1,vector<int>(2*n+1));
    vector<vector<int>>sz(k+1,vector<int>(2*n+1));

    for(int i=1;i<=k;i++){
        for(int j=1;j<=2*n;j++){
            fa[i][j]=j;
            sz[i][j]=1;
        }
    }

    vector<str1>s(2*m+5);
    int cur=0;

    vector<int>last(m+1,0);

    dfs(1,q,1,n,edge,query,fa,sz,s,cur,tree,last);

    return 0;
}