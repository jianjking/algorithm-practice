#include<bits/stdc++.h>
using namespace std;
int root(int i,vector<int>&fa,vector<int>&dist){
    if(fa[i]==i)return i;
    int f=root(fa[i],fa,dist);
    dist[i]+=dist[fa[i]];
    fa[i]=f;
    return f;
}
void merge(int l,int r,vector<int>&fa,vector<int>&sz,vector<int>&dist){
     int lf=root(l,fa,dist);
     int rf=root(r,fa,dist);
     if(lf==rf)return;
     fa[lf]=rf;
     dist[lf]=sz[rf];
     sz[rf]+=sz[lf];
}
void query(int l,int r,vector<int>&fa,vector<int>&dist){
       int lf=root(l,fa,dist);
     int rf=root(r,fa,dist);
     if(lf!=rf){
        cout<<-1<<'\n';
        return;
     }
    cout<<abs(dist[l]-dist[r])-1<<'\n';
}
int main(){
    int t;
    cin>>t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int>fa(3*1e5+5,0);
    vector<int>sz(3*1e5+5,1);
    vector<int>dist(3*1e5+5,0);
    for(int i=1;i<=3*1e5;i++){
        fa[i]=i;
    }
    for(int i=0;i<t;i++){
        char ch;
        int l,r;
        cin>>ch>>l>>r;
        if(ch=='M'){
            merge(l,r,fa,sz,dist);
        }
        else{
            query(l,r,fa,dist);
        }
    }
}