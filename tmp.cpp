#include<bits/stdc++.h>
using namespace std;
struct edge{
  int to;
  int c;
  int d;
};
struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b)const {
        if(a.first!=b.first)return a.first<b.first;
        return a.second<b.second;      
    }
};
bool dj(vector<int>&dist,set<pair<int,int>,compare>&s,vector<vector<edge>>&graph,int limit,int mid){
    while(!s.empty()){
        pair<int,int>tmp=*s.begin();
        s.erase(s.begin());
        int v=tmp.first;
        int u=tmp.second;
        for(auto&p:graph[u]){
            if(p.c>=mid&&v+p.d<dist[p.to]){
                dist[p.to]=p.d+v;
                s.insert({dist[p.to],p.to});
            }
        }
    }
    return dist[dist.size()-1]<=limit;
}
int main(){
    int t;
    cin>>t;
    while(t--){
    int n,m,limit;
    cin>>n>>m>>limit;
    vector<vector<edge>>graph(n+1);
for(int i=1;i<=m;i++){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    graph[a].push_back({b,c,d});
    graph[b].push_back({a,c,d});
}
int l=1;
int r=1e7;
vector<int>dist(n+1,INT_MAX);
set<pair<int,int>,compare>s;
int ans=0;
while(l<=r){
    dist.assign(n+1,INT_MAX);
    s.clear();
    dist[1]=0;
    int mid=(l+r)/2;
    s.insert({dist[1],1});
   if(dj(dist,s,graph,limit,mid)){
     ans=mid;
     l=mid+1;
   }
   else{
    r=mid-1;
   }
    
}
cout<<ans<<'\n';
    
}
}