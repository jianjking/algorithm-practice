#include<bits/stdc++.h>
using namespace std;
struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b)const{
        if(a.first==b.first)return a.second>b.second;
        return a.first>b.first;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    unordered_set<int>nums;
    int mn=INT_MAX;
    for(int i=0;i<n;i++){
        int num;
        cin>>num;
        for(int j=0;j<=m;j++){
            if(num-j>0){
                nums.insert(num-j);
                mn=min(mn,num-j);
            }
        }
    }
    if(mn==1){
        cout<<-1<<'\n';
        return 0;
    }
    vector<vector<pair<int,int>>>graph(mn);
    for(int i=0;i<mn;i++){
        for(auto&p:nums){
            if(p!=mn){
                graph[i].push_back({(i+p)%mn,p});
            }
        }
    }
    vector<int>dist(mn,INT_MAX);
    dist[0]=0;
    set<pair<int,int>,compare>q;
    q.insert({0,0});
    while(!q.empty()){
        auto t=*q.begin();
        q.erase(q.begin());
        int d=t.first,u=t.second;
        if(d>dist[u])continue;
        for(auto&p:graph[u]){
            int v=p.first,w=p.second;
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                q.insert({dist[v],v});
            }
        }
    }
    int ans=0;
    for(int i=0;i<mn;i++){
        if(dist[i]==INT_MAX){
            cout<<"-1"<<endl;
            return 0;
        }
        ans=max(ans,dist[i]-mn);
    }
    cout<<ans<<'\n';
    
}