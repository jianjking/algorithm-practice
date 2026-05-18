#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,v;
    cin>>n>>v;
   vector<vector<pair<int,int>>>val(n+1);
   for(int i=1;i<=n;i++){
     int w,c,k;
     cin>>w>>c>>k;
    val[k].push_back({w,c});
   }
   for(int i=1;i<=n;i++){
    sort(val[i].begin(),val[i].end(),[](pair<int,int>&a,pair<int,int>&b){
        if(a.first!=b.first)return a.first>b.first;
        return a.second>b.second;
    });
   }
   vector<long long>dp(v+1,0);
   for(int i=1;i<=n;i++){
      for(auto&p:val[i]){
        for(int j=p.first;j<=v;j++){
            dp[j]=max(dp[j],dp[j-p.first]+p.second);
        }
      }
   }
   long long ans=LLONG_MIN;
   for(int i=0;i<=v;i++){
      ans=max(ans,dp[i]);
   }
   cout<<ans<<'\n';
}