#include<bits/stdc++.h>
using namespace std;

struct juice{
   int d;
   int p;
   long long l;
};

struct q{
  long long g;
  long long l;
  int num;
};

struct node{
  long long sumv;
  long long sump;
};

int use=0;
int mx=0;

void insert(int target,long long num,int l,int r,int nums,vector<node>&tree){
    if(l==r){
        tree[nums].sumv+=num;
        tree[nums].sump=tree[nums].sumv*l;
        return;
    }

    int mid=l+(r-l)/2;

    if(target<=mid){
        insert(target,num,l,mid,2*nums,tree);
    }
    else{
        insert(target,num,mid+1,r,2*nums+1,tree);
    }

    tree[nums].sumv=tree[2*nums].sumv+tree[2*nums+1].sumv;
    tree[nums].sump=tree[2*nums].sump+tree[2*nums+1].sump;
}

long long query(long long v,int l,int r,int nums,vector<node>&tree){
    if(l==r){
        return v*l;
    }

    int mid=l+(r-l)/2;

    if(tree[2*nums].sumv>=v){
        return query(v,l,mid,2*nums,tree);
    }
    else{
        return tree[2*nums].sump+query(v-tree[2*nums].sumv,mid+1,r,2*nums+1,tree);
    }
}

void dfs(int ql,int qr,int l,int r,vector<juice>&liquor,vector<q>&child,vector<node>&tree,vector<int>&ans){
    if(ql>qr)return;

    if(l==r){
        for(int i=ql;i<=qr;i++){
            ans[child[i].num]=l;
        }
        return;
    }

    int mid=l+(r-l)/2;

    while(use<mid){
        ++use;
        insert(liquor[use].p,liquor[use].l,1,mx,1,tree);
    }

    while(use>mid){
        insert(liquor[use].p,-liquor[use].l,1,mx,1,tree);
        use--;
    }

    vector<q>qql;
    vector<q>qqr;

    for(int i=ql;i<=qr;i++){
        if(tree[1].sumv>=child[i].l && query(child[i].l,1,mx,1,tree)<=child[i].g){
            qql.push_back(child[i]);
        }
        else{
            qqr.push_back(child[i]);
        }
    }

    int pos=ql;

    for(int i=0;i<(int)qql.size();i++){
        child[pos++]=qql[i];
    }

    for(int i=0;i<(int)qqr.size();i++){
        child[pos++]=qqr[i];
    }

    int lsiz=qql.size();

    dfs(ql,ql+lsiz-1,l,mid,liquor,child,tree,ans);
    dfs(ql+lsiz,qr,mid+1,r,liquor,child,tree,ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m;

    vector<juice>liquor(n+2);
    vector<q>child(m+1);

    for(int i=1;i<=n;i++){
        cin>>liquor[i].d>>liquor[i].p>>liquor[i].l;
        mx=max(mx,liquor[i].p);
    }

    for(int i=1;i<=m;i++){
        cin>>child[i].g>>child[i].l;
        child[i].num=i;
    }

    sort(liquor.begin()+1,liquor.begin()+n+1,[](juice a,juice b){
          return a.d>b.d;
    });

    vector<node>tree(4*mx+5,{0,0});
    vector<int>ans(m+1,0);

    dfs(1,m,1,n+1,liquor,child,tree,ans);

    for(int i=1;i<=m;i++){
        if(ans[i]==n+1){
            cout<<-1<<'\n';
        }
        else{
            cout<<liquor[ans[i]].d<<'\n';
        }
    }

    return 0;
}