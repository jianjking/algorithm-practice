#include<bits/stdc++.h>
using namespace std;
void add(int x,int lt,int rt,int l,int r,int nums,vector<vector<int>>&tree){
    if(lt<=l&&rt>=r){
        tree[nums].push_back(x);
        return;
    }
    int mid=l+(r-l)/2;
    if(lt<=mid){
        add(x,lt,rt,l,mid,2*nums,tree);
    }
    if(rt>mid){
        add(x,lt,rt,mid+1,r,2*nums+1,tree);
    }
}
void dfs(int l,int r,int nums,vector<vector<int>>&tree,bitset<10001>&dp,vector<bitset<10001>>&copy,bitset<10001>&ans,int depth){
    copy[depth]=dp;
    for(auto&p:tree[nums]){
        dp|=dp<<p;
    }
    if(l==r){
        ans|=dp;
        dp=copy[depth];
        return;
    }
    int mid=(l+r)/2;
    dfs(l,mid,2*nums,tree,dp,copy,ans,depth+1);
    dfs(mid+1,r,2*nums+1,tree,dp,copy,ans,depth+1);
    dp=copy[depth];
}
int main(){
    int n,q;
    cin>>n>>q;
    bitset<10001>dp;
    dp.set(0);
    vector<vector<int>>tree(4*n+5);
    for(int i=1;i<=q;i++){
        int l,r,x;
        cin>>l>>r>>x;
        add(x,l,r,1,n,1,tree);
    }
    bitset<10001>ans=dp;
    vector<bitset<10001>>copy(22);
    dfs(1,n,1,tree,dp,copy,ans,1);
    int cnt=0;
    for(int i=1;i<=n;i++){
       if(ans[i])cnt++;
    }
    cout<<cnt<<'\n';
      for(int i=1;i<=n;i++){
       if(ans[i])cout<<i<<" ";
    }
}