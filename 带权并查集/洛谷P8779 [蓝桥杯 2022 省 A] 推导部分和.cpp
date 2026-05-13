
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int root(int i,vector<ll>&fa,vector<ll>&dist){
    if(fa[i]==i)return i;
    int f=root(fa[i],fa,dist);
    dist[i]+=dist[fa[i]];
    fa[i]=f;
    return f;
}
void unionation(int l,int r,ll s,vector<ll>&fa,vector<ll>&dist){
     int lf=root(l,fa,dist);
     int rf=root(r,fa,dist);
     if(lf==rf)return;
     fa[lf]=rf;
     dist[lf]=dist[r]+s-dist[l];
}
void query(int l,int r,vector<ll>&fa,vector<ll>&dist){
     int lf=root(l,fa,dist);
     int rf=root(r,fa,dist);
     if(lf!=rf){
        cout<<"UNKNOWN"<<'\n';
        return;
     }
     else{
        cout<<dist[l]-dist[r]<<'\n';
     }

}
int main(){
    int n,m,q;
    cin>>n>>m>>q;
    n++;
    vector<ll>dist(n+1,0);
    vector<ll>fa(n+1,0);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=0;i<m;i++){
        ll l,r,s;
        cin>>l>>r>>s;
        unionation(l,r+1,s,fa,dist);
    }
    for(int i=0;i<q;i++){
        ll l,r;
        cin>>l>>r;
        query(l,r+1,fa,dist);
    }
}
