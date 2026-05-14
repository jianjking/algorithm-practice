#include<bits/stdc++.h>
using namespace std;
int root(int s,vector<int>&father){
    while(father[s]!=s){
        s=father[s];
    }
    return s;
}
void unio(int u,int v,vector<int>&father,vector<int>&sz,vector<int>&edge,int&ball){
        u=root(u,father);
        v=root(v,father);
        if(u==v){
            if(sz[u]>edge[u]){
                ball++;
            }
            edge[u]++;
            return;
        }
        if(sz[u]>edge[u]||sz[v]>edge[v]){
            ball++;
        }
        if(sz[u]<sz[v]){
                father[u]=v;
                sz[v]+=sz[u];
                edge[v]++;
                edge[v]+=edge[u];
            }
            else{
                father[v]=u;
                sz[u]+=sz[v];
                edge[u]++;
                edge[u]+=edge[v];
            }
}
void undo(int u,int v,vector<int>&father,vector<int>&sz,vector<int>&edge,int&ball){
    if(u==v){
        edge[u]--;
        if(sz[u]>edge[u])ball--;
        return;
    }
    int son=father[u]==u?v:u;
    int fa=father[u]==u?u:v;
    sz[fa]-=sz[son];
    edge[fa]--;
    edge[fa]-=edge[son];
    father[son]=son;
    if(sz[son]>edge[son]||sz[fa]>edge[fa])ball--;
}
void dfs(int son,int fa,vector<int>&father,vector<vector<int>>&nums,vector<int>&sz,vector<int>&edge,vector<vector<int>>&s,vector<vector<int>>&graph,vector<int>&ans,int&cur,int &ball){
             s[cur++]={root(nums[son][0],father),root(nums[son][1],father)};
         unio(nums[son][0],nums[son][1],father,sz,edge,ball);
         ans[son]=ball;
         for(auto&p:graph[son]){
            if(p!=fa){
                dfs(p,son,father,nums,sz,edge,s,graph,ans,cur,ball);
            }
         }
         undo(s[cur-1][0],s[cur-1][1],father,sz,edge,ball);
         cur--;

}
int main(){
     int n;
     cin>>n;
     vector<vector<int>>nums(n+1,vector<int>(2,0));
     for(int i=1;i<=n;i++){
        cin>>nums[i][0]>>nums[i][1];
     }
     vector<int>father(n+1,0);
     vector<int>sz(n+1,1);
    vector<int>edge(n+1,0);
    vector<vector<int>>s(n+1);
    int cur=0;
     for(int i=1;i<=n;i++){
        father[i]=i;
     }
     vector<vector<int>>graph(n+1);
     for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
     }
     vector<int>ans(n+1,0);
     int ball=0;
     dfs(1,-1,father,nums,sz,edge,s,graph,ans,cur,ball);
     for(int i=2;i<=n;i++){
        cout<<ans[i]<<" ";
     }
}