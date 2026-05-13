#include<bits/stdc++.h>
using namespace std;
int root(int i,vector<int>&fa,vector<int>&dist){
    if(fa[i]==i)return i;
    int f=root(fa[i],fa,dist);
    dist[i]+=dist[fa[i]];
    fa[i]=f;
    return f;
}
bool merge(int l,int r,int s,vector<int>&fa,vector<int>&dist){
      int lf=root(l,fa,dist);
      int rf=root(r,fa,dist);
      if(lf==rf){
         return (dist[l]-dist[r])==s;
      }
      else{
         fa[lf]=rf;
         dist[lf]=s+dist[r]-dist[l];
      }
      return true;

}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    for(int z=0;z<t;z++){
        int n,m;
        cin>>n>>m;
        n++;
        vector<int>fa(n+1,0);
        vector<int>dist(n+1,0);
        for(int i=1;i<=n;i++){
            fa[i]=i;
        }
        bool an=true;
        for(int i=0;i<m;i++){
            int l,r,s;
            cin>>l>>r>>s;
            if(!merge(l,r+1,s,fa,dist)){
                an=false;
                break;
            }
        }
        if(an)cout<<"true"<<'\n';
        else cout<<"false"<<'\n';
    }
}