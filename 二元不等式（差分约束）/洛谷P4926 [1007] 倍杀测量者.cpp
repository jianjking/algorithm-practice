#include<bits/stdc++.h>
using namespace std;

double limit=1e-6;

bool check(double mid,vector<vector<pair<int,int>>>&first,vector<vector<pair<int,int>>>&second,unordered_map<int,int>&mp,int &n){
    const double INF=1e100;
    vector<double>dist(n+2,INF);
    vector<vector<pair<int,double>>>graph(n+2);
    vector<bool>vis(n+2,false);

    for(int i=1;i<=n;i++){
        for(auto &[v,k]:first[i]){
            if(k - mid > limit) graph[i].push_back({v, -log(k - mid - limit)});
        }
    }
    for(int i=1;i<=n;i++){
        for(auto &[v,k]:second[i]){
            graph[i].push_back({v, log(k + mid)});
        }
    }
    for(int i=1;i<=n;i++){
        graph[0].push_back({i,0.0});
    }
    for(int i=1;i<=n;i++){
        if(mp.count(i) && mp[i]>0){
            double L=log((double)mp[i]);
            graph[n+1].push_back({i, +L});
            graph[i].push_back({n+1, -L});
        }
    }

    dist[0]=0.0;
    queue<int>q;
    q.push(0);
    vis[0]=true;
    vector<int>cnt(n+2,0);
    cnt[0]=1;
    int V=n+2;

    while(!q.empty()){
        int u=q.front(); q.pop();
        vis[u]=false;
        for(auto &[v,w]:graph[u]){
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                if(!vis[v]){
                    vis[v]=true;
                    q.push(v);
                    if(++cnt[v]>=V) return true;
                }
            }
        }
    }
    return false;
}

int main(){
    int n,m,t;
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>m>>t;
    vector<vector<pair<int,int>>> first(n+1), second(n+1);
    for(int i=1;i<=m;i++){
        int op,x,y,k;
        cin>>op>>x>>y>>k;
        if(op==1) first[x].push_back({y,k});
        else      second[x].push_back({y,k});
    }
    unordered_map<int,int> mp;
    for(int i=0;i<t;i++){
        int name,value;
        cin>>name>>value;
        mp[name]=value;
    }

    double l=0,r=1e9,ans=-1;
    while(r-l>=limit){
        double mid=(l+r)/2;
        if(check(mid,first,second,mp,n)){
            ans=mid;
            l=mid+limit;
        }else{
            r=mid-limit;
        }
    }
    cout.setf(std::ios::fixed);
    cout<<setprecision(10)<<ans<<'\n';
    return 0;
}

