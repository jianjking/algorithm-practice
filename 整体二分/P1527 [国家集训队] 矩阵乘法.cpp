#include<bits/stdc++.h>
using namespace std;
struct str{
   int row;
   int col;
   int val;
};
struct str1{
  int num;
  int x1;
  int y1;
  int x2;
  int y2;
  int k;
};
int lowbit(int i){
    return i&(-i);
}
void addnum(int x,int y,vector<vector<int>>&tree,int edge){
   int n=tree[0].size()-1;
   for(int i=x;i<=n;i+=lowbit(i)){
      for(int j=y;j<=n;j+=lowbit(j)){
        tree[i][j]+=edge;
      }
   }
}
int querysum(int x,int y,vector<vector<int>>&tree){
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i)){
        for(int j=y;j>0;j-=lowbit(j)){
            ans+=tree[i][j];
        }
    }
    return ans;
}
int sum(int x1,int y1,int x2,int y2,vector<vector<int>>&tree){
    return querysum(x2,y2,tree)-querysum(x2,y1-1,tree)-querysum(x1-1,y2,tree)+querysum(x1-1,y1-1,tree);
}
void dfs(int l,int r,int ql,int qr,vector<str1>&query,vector<str>&nums,vector<int>&ans, vector<vector<int>>&tree){
    if(ql>qr)return;
    if(l==r){
        for(int i=ql;i<=qr;i++){
            ans[query[i].num]=nums[l].val;
        }
        return;
    }
    int mid=(l+r)/2;
    for(int i=l;i<=mid;i++){
        addnum(nums[i].row,nums[i].col,tree,1);
    }
    vector<str1>qql;
    vector<str1>qqr;
   for(int i=ql;i<=qr;i++){
         int x1=query[i].x1;
         int x2=query[i].x2;
         int y1=query[i].y1;
         int y2=query[i].y2;
         int cnt=sum(x1,y1,x2,y2,tree);
         if(cnt>=query[i].k){
            qql.push_back(query[i]);
         }
         else{
            query[i].k-=cnt;
              qqr.push_back(query[i]);
         }
   }
    for(int i=l;i<=mid;i++){
        addnum(nums[i].row,nums[i].col,tree,-1);
    }
    int cur=ql;
    for(int i=0;i<qql.size();i++){
        query[cur++]=qql[i];
    }
    for(int i=0;i<qqr.size();i++){
        query[cur++]=qqr[i];
    }
   dfs(l,mid,ql,ql+qql.size()-1,query,nums,ans,tree);
   dfs(mid+1,r,ql+qql.size(),qr,query,nums,ans,tree);
}
int main(){
    int n,q;
    cin>>n>>q;
    vector<str>nums(n*n+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>nums[n*(i-1)+j].val;
            nums[n*(i-1)+j].row=i;
            nums[n*(i-1)+j].col=j;
        }
    }
    sort(nums.begin()+1,nums.end(),[](str&a,str&b){
        if(a.val!=b.val)return a.val<b.val;
        if(a.row!=b.row)return a.row<b.row;
        return a.col<b.col;
    });
    vector<str1>query(q+1);
    for(int i=1;i<=q;i++){
        cin>>query[i].x1>>query[i].y1>>query[i].x2>>query[i].y2>>query[i].k;
        query[i].num=i;
    }
    vector<int>ans(q+1);
    vector<vector<int>>tree(n+1,vector<int>(n+1,0));
    dfs(1,n*n,1,q,query,nums,ans,tree);
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<'\n';
    }

}