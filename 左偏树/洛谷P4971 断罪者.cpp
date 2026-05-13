#include<bits/stdc++.h>
using namespace std;
const int mx=2*1e6+5;
int zuo[mx];
int you[mx];
int father[mx];
int up[mx];
int nums[mx];
int dist[mx];
int merge(int a,int b){
    if(a==0||b==0)return a+b;
    if(nums[a]<nums[b]||(nums[a]==nums[b]&&a>b)){
        swap(a,b);
    }
    you[a]=merge(you[a],b);
    up[zuo[a]]=up[you[a]]=a;
    if(dist[zuo[a]]<dist[you[a]]){
        swap(zuo[a],you[a]);
    }
    dist[a]=dist[you[a]]+1;
    father[zuo[a]]=father[you[a]]=a;
    return a;
}
int root(int i){
    return father[i]=father[i]==i?i:root(father[i]);
}
int remove(int i){
    int h=root(i);
    int f=up[i];
father[zuo[i]]=zuo[i];
father[you[i]]=you[i];
int s=merge(zuo[i],you[i]);
father[i]=s;
up[s]=f;
if(i!=h){
    father[s]=h;
     if(zuo[f]==i){
        zuo[f]=s;
     }
     else{
        you[f]=s;
     }
     for(int d=dist[s];dist[f]>d+1;f=up[f],d++){
        dist[f]=d+1;
         if(dist[zuo[f]]<dist[you[f]]){
        swap(zuo[f],you[f]);
    }
}
}
zuo[i]=0;
you[i]=0;
up[i]=0;
dist[i]=0;
return father[s];
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t,w,k;
    cin>>t>>w>>k;
    for(int i=0;i<t;i++){
        int n,m;
        cin>>n>>m;
        memset(nums,0,4*mx);
        memset(zuo,0,4*mx);
        memset(you,0,4*mx);
        memset(father,0,4*mx);
        memset(dist,0,4*mx);
        memset(up,0,4*mx);
        dist[0]=-1;
        for(int i=1;i<=n;i++)father[i]=i;
        for(int j=1;j<=n;j++){
             cin>>nums[j];
        }
        for(int i=0;i<m;i++){
            int op;
            cin>>op;
            if(op==2){
                int a;
                cin>>a;
                nums[a]=0;
                int h=remove(a);
                merge(h,a);
            }
            else if(op==3){
                int a,b;
                cin>>a>>b;
                int h=root(a);
                nums[h]=max(nums[h]-b,0);
                int tmp=remove(h);
                merge(h,tmp);
            }
            else{
                int a,b;
                cin>>a>>b;
                merge(a,b);
            }
        }
        int mx=INT_MIN;
        long long sum=0;
        for(int i=1;i<=n;i++){
            if(father[i]==i){
                sum+=nums[i];
                mx=max(mx,nums[i]);
            }
        }
        if(w==2){
            sum-=mx;
        }
        else if(w==3){
            sum+=mx;
        }
        if(sum==0){
            cout<<"Gensokyo"<<' ';
        }
        else if(sum>k){
            cout<<"Hell"<<' ';
        }
        else{
            cout<<"Heaven"<<' ';
        }
        cout<<sum<<'\n';
    }
}