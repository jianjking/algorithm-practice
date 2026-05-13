#include<bits/stdc++.h>
using namespace std;
struct compare{
    bool operator()(const pair<long long,int>&a,const pair<long long,int>&b)const{
        if(a.first==b.first){
            return a.second<b.second;
        }
        return a.first<b.first;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long h;
    cin>>h;
    long long x,y,z;
    cin>>x>>y>>z;
    int n=(int)min({x,y,z});
    vector<vector<pair<int,long long>>>graph(n);
    for(int i=0;i<n;i++){
        if(x!=n){
            graph[i].push_back({(int)((i+x)%n),x});
        }
        if(y!=n){
            graph[i].push_back({(int)((i+y)%n),y});
        }
        if(z!=n){
            graph[i].push_back({(int)((i+z)%n),z});
        }
    }
    const long long INF = (1LL<<62);
    vector<long long>dist(n,INF);
    dist[0]=0;
    set<pair<long long,int>,compare>s;
    s.insert({0,0});
    while(!s.empty()){
        auto t=*s.begin();
        s.erase(s.begin());
        if(t.first>dist[t.second])continue;
        int u=t.second;
        for(auto [v,w]:graph[u]){
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                s.insert({dist[v],v});
            }
        }
    }
    long long ans=0;
    for(int i=0;i<n;i++){
        if(dist[i]<h){
            ans+=(h-1-dist[i])/(long long)n+1;
        }
    }
    cout<<ans<<'\n';
}
