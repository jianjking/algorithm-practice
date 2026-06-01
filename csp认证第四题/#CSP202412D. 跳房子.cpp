#include<bits/stdc++.h>
using namespace std;
struct compare{
   bool operator()(const pair<int,int>&a,const pair<int,int>&b)const{
    if(a.second!=b.second)return a.second<b.second;
    return a.first<b.first;
   }
};
int main(){
    int n;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    vector<vector<pair<int,int>>>graph(n+1);
    vector<int>arr(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    arr[n]=0;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=i+1;j<=min(n,i+k);j++){
              graph[i].push_back({j-arr[j],1});
        }
    }
    vector<int>dist(n+1,INT_MAX);
    dist[1]=0;
    set<pair<int,int>,compare>q;
    q.insert({1,0});
    while(!q.empty()){
        int u=(*q.begin()).first;
        int v=(*q.begin()).second;
        q.erase(q.begin());
        if(v>dist[u])continue;
        for(auto&p:graph[u]){
            if(dist[p.first]>v+p.second){
                dist[p.first]=v+p.second;
                q.insert({p.first,dist[p.first]});
            }
        }
    }
    if(dist[n]==INT_MAX)dist[n]=-1;
    cout<<dist[n]<<'\n';

}