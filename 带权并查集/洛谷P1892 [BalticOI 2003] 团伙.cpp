#include<bits/stdc++.h>
using namespace std;
int root(int i,vector<int>&fa){
    if(i==fa[i])return i;
    fa[i]=root(fa[i],fa);
    return fa[i];
}
void merge(int u,int v,vector<int>&fa){
    u=root(u,fa);
    v=root(v,fa);
    if(u==v)return;
    fa[u]=v;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<int>fa(n+1,0);
    vector<int>enermy(n+1,0);
    vector<int>frd(n+1,0);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=0;i<m;i++){
        char ch;
        int p,q;
        cin>>ch>>p>>q;
        if(ch=='E'){
            if(enermy[p]==0&&enermy[q]==0){
            enermy[p]=q;
            enermy[q]=p;
        }
        else if(enermy[p]==0){
            enermy[p]=q;
            merge(p,enermy[q],fa);
        }
        else if(enermy[q]==0){
            enermy[q]=p;
            merge(q,enermy[p],fa);
        }
        else{
            merge(p,enermy[q],fa);
            merge(q,enermy[p],fa);
        }
        
       if(enermy[p]==0&&enermy[q]==0){
            enermy[p]=q;
            enermy[q]=p;
        }
        else if(enermy[p]==0){
            enermy[p]=q;
            merge(p,enermy[q],fa);
        }
        else if(enermy[q]==0){
            enermy[q]=p;
            merge(q,enermy[p],fa);
        }
    else{
            merge(p,enermy[q],fa);
            merge(q,enermy[p],fa);
        }
    }
    else{
        
            merge(p,q,fa);
       
    }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(fa[i]==i)ans++;
    }
    cout<<ans<<'\n';
}