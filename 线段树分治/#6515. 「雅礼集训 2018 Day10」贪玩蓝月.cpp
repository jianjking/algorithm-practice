#include<bits/stdc++.h>
using namespace std;
void addedge(int id,int lt,int rt,int l,int r,int nums,vector<vector<int>>&tree){
    if(lt>rt)return;

    if(lt<=l&&r<=rt){
        tree[nums].push_back(id);
        return;
    }

    int mid=(l+r)/2;

    if(lt<=mid){
        addedge(id,lt,rt,l,mid,2*nums,tree);
    }

    if(rt>mid){
        addedge(id,lt,rt,mid+1,r,2*nums+1,tree);
    }
}
void dfs(int l,int r,int nums,vector<bool>&vis,vector<int>&zuo,vector<int>&you,vector<vector<int>>&tree,vector<vector<long long>>&copy,vector<long long>&dp,vector<int>&val,vector<int>&weight,int depth,int p){
    copy[depth]=dp; 

    for(auto&u:tree[nums]){
         vector<long long>pre=dp;
         for(int i=0;i<p;i++){
            if(pre[i]!=INT_MIN){
                int tmp=(i+weight[u])%p;
                dp[tmp]=max(dp[tmp],pre[i]+val[u]);
            }
         }
     }
     if(l==r){
        if(vis[l]){
            long long mx=INT_MIN;
            for(int i=zuo[l];i<=you[l];i++){
                   mx=max(mx,dp[i]);
            }
            if(mx!=INT_MIN)cout<<mx<<'\n';
            else cout<<-1<<'\n';
        }
        dp=copy[depth];
        return;
     }
     int mid=l+(r-l)/2;
     dfs(l,mid,2*nums,vis,zuo,you,tree,copy,dp,val,weight,depth+1,p);
     dfs(mid+1,r,2*nums+1,vis,zuo,you,tree,copy,dp,val,weight,depth+1,p);
          dp=copy[depth];
}
int main(){
    int nums;
    cin>>nums;
    int m,p;
    cin>>m>>p;
    vector<int>weight(m+1);
    vector<int>val(m+1);
    vector<int>from(m+1,1);
    vector<int>to(m+1,m);
    vector<bool>query(m+1,false);
    vector<int>zuo(m+1,0);
    vector<int>you(m+1,0);
    int n=1;
    deque<int>q;
    for(int i=1;i<=m;i++){
        string s;
        cin>>s;
        if(s=="IF"){
            int w,v;
            cin>>w>>v;
            weight[n]=w;
            val[n]=v;
            from[n]=i;
            q.push_front(n);
            n++;
        }
        else if(s=="IG"){
             int w,v;
            cin>>w>>v;
            weight[n]=w;
            val[n]=v;
            from[n]=i;
            q.push_back(n);
            n++;
        }
        else if(s=="DF"){
            int num=q.front();
            q.pop_front();
            to[num]=i-1;
        }
        else if(s=="DG"){
           int num=q.back();
           q.pop_back();
           to[num]=i-1;
        }
        else{
            int l,r;
            cin>>l>>r;
            query[i]=true;
            zuo[i]=l;
            you[i]=r;
        }
    }
    vector<vector<int>>tree(4*m+5);
    for(int i=1;i<n;i++){
        if(from[i]<=to[i]){
            addedge(i,from[i],to[i],1,m,1,tree);
        }
    }
    vector<vector<long long>>copy(22,vector<long long>(p,0));
    vector<long long>dp(p,INT_MIN);
    dp[0]=0;
    dfs(1,m,1,query,zuo,you,tree,copy,dp,val,weight,1,p);
}