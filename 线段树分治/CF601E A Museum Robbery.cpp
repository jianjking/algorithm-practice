#include<bits/stdc++.h>
using namespace std;

const long long mod1=10000019;
const long long mod2=1000000007;

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

void dfs(int l,int r,int nums,
         vector<int>&op,
         vector<vector<int>>&tree,
         vector<long long>&dp,
         vector<vector<long long>>&back,
         vector<int>&val,
         vector<int>&weight,
         int k,
         vector<long long>&pw,
         int depth){

    back[depth]=dp;

    for(auto id:tree[nums]){
        for(int j=k;j>=weight[id];j--){
            dp[j]=max(dp[j],dp[j-weight[id]]+val[id]);
        }
    }

    if(l==r){
        if(op[l]==3){
            long long res=0;

            for(int i=1;i<=k;i++){
                res=(res+dp[i]%mod2*pw[i-1])%mod2;
            }

            cout<<res<<'\n';
        }

        dp=back[depth];
        return;
    }

    int mid=l+(r-l)/2;

    dfs(l,mid,2*nums,op,tree,dp,back,val,weight,k,pw,depth+1);
    dfs(mid+1,r,2*nums+1,op,tree,dp,back,val,weight,k,pw,depth+1);

    dp=back[depth];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    cin>>n>>k;

    vector<int>val(1),weight(1),from(1),to(1);

    for(int i=1;i<=n;i++){
        int v,w;
        cin>>v>>w;

        val.push_back(v);
        weight.push_back(w);
        from.push_back(1);
        to.push_back(0);
    }

    int q;
    cin>>q;

    for(int i=1;i<=n;i++){
        to[i]=q;
    }

    vector<int>op(q+1);

    for(int i=1;i<=q;i++){
        cin>>op[i];

        if(op[i]==1){
            int v,w;
            cin>>v>>w;

            val.push_back(v);
            weight.push_back(w);
            from.push_back(i);
            to.push_back(q);
        }
        else if(op[i]==2){
            int x;
            cin>>x;
            to[x]=i-1;
        }
    }

    vector<vector<int>>tree(4*q+5);

    int tot=val.size()-1;

    for(int i=1;i<=tot;i++){
        if(from[i]<=to[i]){
            addedge(i,from[i],to[i],1,q,1,tree);
        }
    }

    vector<long long>pw(k+1,1);

    for(int i=1;i<=k;i++){
        pw[i]=pw[i-1]*mod1%mod2;
    }

    vector<long long>dp(k+1,0);
    vector<vector<long long>>back(35,vector<long long>(k+1,0));

    dfs(1,q,1,op,tree,dp,back,val,weight,k,pw,1);

    return 0;
}