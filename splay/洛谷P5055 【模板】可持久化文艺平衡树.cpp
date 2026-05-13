#include<bits/stdc++.h>
using namespace std;
const int mxn=2*1e5+5;
const int mx=mxn*100;
int head[mxn];
int zuo[mx];
int you[mx];
bool vis[mx];
int sum[mx];
int sz[mx];
int prior[mx];
int val[mx];
int cnt=0;
int cnth=0;
unsigned int tmp=123563131;
int rmd(){
    tmp^=tmp>>5;
    tmp^=tmp<<3;
    tmp^=tmp>>8;
    return tmp;
}
void up(int i){
    sz[i]=sz[zuo[i]]+sz[you[i]]+1;
    sum[i]=sum[zuo[i]]+sum[you[i]]+val[i];
}
int copy(int i){
    val[++cnt]=val[i];
    vis[cnt]=vis[i];
    zuo[cnt]=zuo[i];
    you[cnt]=you[i];
    sz[cnt]=sz[i];
    sum[cnt]=sum[i];
    prior[cnt]=prior[i];
}
void down(int i){
    if(!vis[i])return;
    if(zuo[i]!=0){
        zuo[i]=copy(zuo[i]);
    }
    if(you[i]!=0){
        you[i]=copy(you[i]);
    }
    vis[i]=false;
    swap(zuo[i],you[i]);
    vis[zuo[i]]=!vis[zuo[i]];
    vis[you[i]]=!vis[you[i]];
}
void split(int l,int r,int cur,int rank){
    if(cur==0){
        you[l]=0;
        zuo[r]=0;
    }
    else{
        cur=copy(cur);
        down(cur);
        if(sz[zuo[cur]]+1<=rank){
            you[l]=cur;
            split(you[l],r,you[cur],rank-sz[zuo[cur]]-1);
        }
        else{
          zuo[r]=cur;
          split(l,zuo[r],zuo[cur],rank);
        }
        up(cur);
    }
}
int merge(int l,int r){
    if(l==0||r==0){
        return l+r;
    }
    else{
        if(prior[l]>=prior[r]){
            l=copy(l);
            down(l);
            you[l]=merge(you[l],r);
            up(l);
            return l;
        }
        else{
            r=copy(r);
            down(r);
            zuo[r]=merge(l,zuo[r]);
            up(r);
            return r;
        }
    }
}
int main(){
    int ans=0;
    int n;
    ios::sync_with_stdio(0);
    cin>>n;
    cnth=0;
    for(int i=0;i<n;i++){
        int v,op;
        cin>>v>>op;
        if(op==1){
           int p,x;
           cin>>p>>x;
           ans^=p;
           ans^=x;
           split(0,0,head[v],p);
          val[++cnt]=x;
          prior[cnt]=rmd();
          sz[cnt]=1;
           head[++cnth]=merge(merge(you[0],cnt),zuo[0]);
           you[0]=0;
           zuo[0]=0;
        }
        else if(op==2){
        int p;
        cin>>p;
        ans^=p;
        split(0,0,head[v],p-1);
        int l=you[0];
        split(0,0,zuo[0],1);
        head[++cnth]=merge(l,zuo[0]);
        you[0]=0;
        zuo[0]=0;
        }
        else if(op==3){
           int l,r;
           cin>>l>>r;
           ans^=l;
           ans^=r;
           split(0,0,head[v],l-1);
           int l1=you[0];
           split(0,0,zuo[0],r);
           vis[you[0]]=true;
           head[++cnth]=merge(merge(l1,you[0]),zuo[0]);
           zuo[0]=0;
           you[0]=0;
        }
        else{
            int l,r;
            cin>>l>>r;
            split(0,0,head[v],l-1);
           int l1=you[0];
           split(0,0,zuo[0],r);
           ans=sum[you[0]];
           head[++cnth]=merge(merge(l1,you[0]),zuo[0]);
        }
    }
    cout<<ans<<'\n'
}