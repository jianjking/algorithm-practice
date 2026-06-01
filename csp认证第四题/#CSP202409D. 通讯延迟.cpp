#include<bits/stdc++.h>
using namespace std;
struct compare{
  bool operator()(const pair<int,double>&a,const pair<int,double>&b)const{
    if(a.second!=b.second)return a.second<b.second;
    return a.first<b.first;
  }
};
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,double>>>arr(n+m+1);
    vector<pair<int,int>>pos(n+m+1);
    for(int i=1;i<=n;i++){
        cin>>pos[i].first>>pos[i].second;
    }
    for(int i=n+1;i<=n+m;i++){
        cin>>pos[i].first>>pos[i].second;
        int r,t;
        cin>>r>>t;
        for(int j=1;j<=n;j++){
            if(pos[j].first>=pos[i].first-r&&pos[j].first<=pos[i].first+r&&pos[j].second>=pos[i].second-r&&pos[j].second<=pos[i].second+r){
                  arr[j].push_back({i,(double)t/2});
                  arr[i].push_back({j,(double)t/2});
            }
        }
    }
    vector<double>dist(n+m+1,DBL_MAX);
    dist[1]=0;
    set<pair<int,double>>s;
    s.insert({1,0});
    while(!s.empty()){
        int u=(*s.begin()).first;
        double v=(*s.begin()).second;
        s.erase(s.begin());
        if(dist[u]<v)continue;
        for(auto&p:arr[u]){
            if(dist[p.first]>v+p.second){
                dist[p.first]=v+p.second;
                s.insert({p.first,dist[p.first]});
            }
        }
    }
    if(dist[n]==DBL_MAX){
        cout<<"Nan"<<'\n';
    }
    else{
        cout<<dist[n]<<'\n';
    }

}