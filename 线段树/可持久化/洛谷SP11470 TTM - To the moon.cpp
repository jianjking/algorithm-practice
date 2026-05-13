#include<bits/stdc++.h>
using namespace std;
const int mx=5*1e6;
int zuo[mx];
int you[mx];
int sum[mx];
int add[mx];
int head[mx];
int nums[mx];
int h;
int cnt;
int copy(int i){
    cnt++;
    add[cnt]=add[i];
    sum[cnt]=sum[i];
    zuo[cnt]=zuo[i];
    you[cnt]=you[i];
   return cnt;
}
void up(int i){
    sum[i]=sum[zuo[i]]+sum[you[i]];
}
void lazy(int l,int r,int i,int v){
    add[i]+=v;
    sum[i]+=(r-l+1)*v;
}
void down(int l,int r,int i){
    if(add[i]==0)return;
   zuo[i]=copy(zuo[i]);
   you[i]=copy(you[i]);
   int mid=l+(r-l)/2;
   lazy(l,mid,zuo[i],add[i]);
   lazy(mid+1,r,you[i],add[i]);
   add[i]=0;
}
int build(int l,int r){
    int num=++cnt;
    if(l==r){
        sum[num]=nums[l];
        return num;
    }
    int mid=l+(r-l)/2;
    zuo[num]=build(l,mid);
    you[num]=build(mid+1,r);
    up(num);
    return num;
}
int addtion(int x,int y,int l,int r,int v,int cur){
    int xxx=copy(cur);
    if(l<=x&&r>=y){
        lazy(x,y,xxx,v);
        return xxx;
    }
    else{
        down(x,y,xxx);
        int mid=x+(y-x)/2;
        if(l<=mid){
            zuo[xxx]=addtion(x,mid,l,r,v,zuo[xxx]);
        }
        if(r>mid){
            you[xxx]=addtion(mid+1,y,l,r,v,you[xxx]);
        }
        up(xxx);
    }
}
int query(int x,int y,int l,int r,int cur){
    if(x<=l&&y>=r){
        return sum[cur];
    }
    int mid=l+(r-l)/2;
    down(l,r,cur);
    int sum=0;
    if(x<=mid){
       sum+=query(x,y,l,mid,zuo[cur]);
    }
    if(y>mid){
        sum+=query(x,y,mid+1,r,you[cur]);
    }
    return sum;
}
int main(){
    int n,m;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    h=0;
    cnt=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    build(1,n);
    int t=0;
    for(int i=0;i<m;i++){
        char ch;
        cin>>ch;
        if(ch=='C'){
         int l,r,v;
         cin>>l>>r>>v;
         head[++t]=addtion(1,n,l,r,v,head[t]);
        }
        else if(ch=='Q'){
            int l,r;
            cin>>l>>r;
            cout<<query(l,r,1,n,head[t])<<'\n';
        }
        else if(ch=='H'){
            int l,r,t1;
            cin>>l>>r>>t1;
            cout<<query(l,r,1,n,head[t1])<<'\n';
        }
        else{
            int x;
            cin>>x;
            t=x;
        }
    }
}