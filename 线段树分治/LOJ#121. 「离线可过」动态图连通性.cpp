#include<bits/stdc++.h>
using namespace std;
int root(int f,vector<int>&father){
    while(f!=father[f])f=father[f];
    return f;
}
void unio(int u,int v,vector<int>&father,vector<int>&sz,vector<pair<int,int>>&s,int&cur){
    if(sz[u]>sz[v]){
    father[v]=u;
    sz[u]+=sz[v];
    s[cur++]={u,v};
    }
    else{
        father[u]=v;
        sz[v]+=sz[u];
        s[cur++]={v,u};
    }
}
void undo(vector<int>&father,vector<int>&sz,vector<pair<int,int>>&s,int&cur){
    int f=s[cur-1].first;
    int son=s[cur-1].second;
    cur--;
    father[son]=son;
    sz[f]-=sz[son];
}
void addedge(int u,int v,int lt,int rt,int l,int r,int nums,vector<vector<pair<int,int>>>&tree){
    if(lt<=l&&rt>=r){
        tree[nums].push_back({u,v});
        return;
    }
    int mid=l+(r-l)/2;
    if(lt<=mid){
       addedge(u,v,lt,rt,l,mid,2*nums,tree);
    }
    if(rt>mid){
        addedge(u,v,lt,rt,mid+1,r,2*nums+1,tree);
    }

}
void dfs(int l, int r, int nums, vector<vector<pair<int, int>>> &tree, vector<vector<int>> &op,
         vector<int> &father, vector<int> &sz, vector<pair<int, int>> &s, int cur) {
    int unionCnt = 0;

    for (auto &p : tree[nums]) {
        int u = p.first;
        int v = p.second;
        int fu = root(u, father);
        int fv = root(v, father);

        if (fu == fv)
            continue;

        unio(fu, fv, father, sz, s, cur);
        unionCnt++;
    }

    if (l == r) {
        if (op[l][0] == 2) {
            int u = op[l][1];
            int v = op[l][2];

            if (root(u, father) == root(v, father)) {
                cout << "Y" << '\n';
            } else {
                cout << "N" << '\n';
            }
        }

        for (int i = 0; i < unionCnt; i++) {
            undo(father, sz, s, cur);
        }

        return;
    }

    int mid = l + (r - l) / 2;

    dfs(l, mid, 2 * nums, tree, op, father, sz, s, cur);
    dfs(mid + 1, r, 2 * nums + 1, tree, op, father, sz, s, cur);

    for (int i = 0; i < unionCnt; i++) {
        undo(father, sz, s, cur);
    }
}
int main(){
    int n,m;
    cin>>n>>m;
   vector<vector<int>>last(n+1,vector<int>(n+1,0));
   vector<vector<int>>op(m+1,vector<int>(3));
   vector<vector<pair<int,int>>>tree(4*m+5);
   vector<int>father(n+1);
   vector<int>sz(n+1);
   vector<pair<int,int>>s(m);
   int cur=0;
   for(int i=1;i<=n;i++){
    father[i]=i;
    sz[i]=1;
   }
   for(int i=1;i<=m;i++){
     cin>>op[i][0]>>op[i][1]>>op[i][2];
      int mn=min(op[i][1],op[i][2]);
      int mx=max(op[i][1],op[i][2]);
     if(op[i][0]==1){
        addedge(mn,mx,last[mn][mx],i-1,1,m,1,tree);
        last[mn][mx]=0;
     }
     else if(op[i][0]==0){
        last[mn][mx]=i;
     }

   }
   for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(last[i][j]){
            addedge(i,j,last[i][j],m,1,m,1,tree);
        }
    }
   }
   dfs(1,m,1,tree,op,father,sz,s,cur);
  
}