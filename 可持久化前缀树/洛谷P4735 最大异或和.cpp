#include<bits/stdc++.h>
using namespace std;
const int maxn=6*1e5+5;
const int maxt=maxn*60;
int cntd;
int tree[maxt][2];
int root[maxn];
int pass[maxt];
const int BIT=30;
int insert(int i,int val){
    int num=++cntd;
    tree[num][0]=tree[i][0];
    tree[num][1]=tree[i][1];
    pass[num]=pass[i]+1;
    for(int t=BIT,pre=num,cur;t>=0;t--){
        int v=(val>>t)&1;
        cur=++cntd;
        i=tree[i][v];
        tree[cur][0]=tree[i][0];
        tree[cur][1]=tree[i][1];
        pass[cur]=pass[i]+1;
        tree[pre][v]=cur;
        pre=cur;
    }
    return num;
}
int query(int lroot,int rroot,int val){
    int res=0;
     for(int i=BIT;i>=0;i--){
        int second=(val>>i)&1;
        int first=second^1;
        if(pass[tree[rroot][first]]-pass[tree[lroot][first]]>0){
            res|=(1<<i);
            lroot=tree[lroot][first];
            rroot=tree[rroot][first];
        }
        else{
            lroot=tree[lroot][second];
            rroot=tree[rroot][second];
        }
     }
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int sum=0;
    int n,m;
    cin>>n>>m;
    root[0]=insert(0,0);
    for(int i=1;i<=n;i++){
       int x;
       cin>>x;
       sum^=x;
       root[i]=insert(root[i-1],sum);
    }
    for(int i=1;i<=m;i++){
        char ch;
        cin>>ch;
        if(ch=='A'){
            int x;
            cin>>x;
            sum^=x;
            root[n+1]=insert(root[n],sum);
            n++;
        }
        else{
            int l,r,x;
            cin>>l>>r>>x;
            if(l==1)cout<<query(0,root[r-1],sum^x)<<'\n';
            else cout<<query(root[l-2],root[r-1],sum^x)<<'\n';
        }
    }
}