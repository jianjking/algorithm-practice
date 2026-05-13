#include<bits/stdc++.h>
using namespace std;
const int mx=6*1e7;
int zuo[mx];
int you[mx];
int val[mx];
int head[mx];
int cnt;
int h;
int build(int l,int r){
    int num=cnt++;
    if(l==r){
        int nums;
        cin>>nums;
        val[num]=nums;
        return num; 
    }
    int mid=l+(r-l)/2;
    zuo[num]= build(l,mid);
    you[num]= build(mid+1,r);
    return num;
}
int update(int l,int r,int cur,int target,int vals){
    int num=cnt++;
    zuo[num]=zuo[cur];
    you[num]=you[cur];
    val[num]=val[cur];
    if(l==r){
        val[num]=vals;
        return num;
    }
    int mid=l+(r-l)/2;
    if(target<=mid){
     zuo[num]=update(l,mid,zuo[cur],target,vals);
    }
    else{
        you[num]=update(mid+1,r,you[cur],target,vals);
    }
    return num;
}
void query(int l,int r,int target,int cur){
    if(l==r){
        cout<<val[cur]<<'\n';
        return;
    }
    int mid=l+(r-l)/2;
    if(target<=mid)query(l,mid,target,zuo[cur]);
    else query(mid+1,r,target,you[cur]);
}
int main(){
    cnt=0;
    h=0;
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    head[h++]=build(1,n);
    for(int i=0;i<m;i++){
        int v,op;
        cin>>v>>op;
        if(op==1){
            int x,vals;
            cin>>x>>vals;
            head[h++]=update(1,n,head[v],x,vals);
        }
        else{
            head[h++]=head[v];
            int target;
            cin>>target;
            query(1,n,target,head[h-1]);
        }
    }
}