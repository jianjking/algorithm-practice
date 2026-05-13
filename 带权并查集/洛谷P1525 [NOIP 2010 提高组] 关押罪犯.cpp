#include<bits/stdc++.h>
using namespace std;
int root(int i,vector<int>&fa){
    if(fa[i]==i)return i;
    return root(fa[i],fa);
}
void merge(int u,int v,vector<int>&fa){
    u=root(u,fa);
    v=root(v,fa);
    fa[u]=v;
}
int main(){
    int n,m;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    vector<int>fa(n+1,0);
    vector<int>enermy(n+1,0);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    vector<vector<int>>nums(m,vector<int>(3,0));
    for(int i=0;i<m;i++){
        cin>>nums[i][0]>>nums[i][1]>>nums[i][2];
    }
    sort(nums.begin(),nums.end(),[](vector<int>&a,vector<int>&b){
        if(a[2]!=b[2])return a[2]>b[2];
        if(a[1]!=b[1])return a[1]<b[1];
        return a[0]<b[0];
    });
    for(int i=0;i<m;i++){
        int u=nums[i][0];
        int v=nums[i][1];
        int w=nums[i][2];
        if(enermy[u]==0&&enermy[v]==0){
             enermy[u]=v;
             enermy[v]=u;
        }
        else if(enermy[u]==0){
            enermy[u]=v;
            merge(u,enermy[v],fa);
        }
        else if(enermy[v]==0){
            enermy[v]=u;
            merge(v,enermy[u],fa);
        }
        else{
           if(root(u,fa)==root(v,fa)){
            cout<<w<<'\n';
            return 0;
           }
           merge(v,enermy[u],fa);
           merge(u,enermy[v],fa);
        }
    }
    cout<<0<<'\n';
}