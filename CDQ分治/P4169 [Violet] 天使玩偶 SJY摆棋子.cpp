#include<bits/stdc++.h>
using namespace std;
struct node{
  int op;
  int x;
  int y;
};
int lowbit(int i){
    return i&(-i);
}
void add(int i,vector<int>&tree,int v){
    int n=tree.size()-1;
    while(i<=n){
       tree[i]=max(tree[i],v);
       i+=lowbit(i);
    }
}
int query(int i,vector<int>&tree){
    int ans=INT_MIN;
    while(i>0){
        ans=max(ans,tree[i]);
        i-=lowbit(i);
    }
    return ans;
}
void clear(int i,vector<int>&tree){
     int n=tree.size()-1;
    while(i<=n){
       tree[i]=INT_MIN;
       i+=lowbit(i);
    }
}
void cdq(int l,int r,vector<node>&tmp,vector<int>&ans,vector<int>&tree){
    if(l>=r)return;
    int mid=(l+r)/2;
    cdq(l,mid,tmp,ans,tree);
    cdq(mid+1,r,tmp,ans,tree);
    int i,j;
    for( i=l,j=mid+1;j<=r;j++){
        while(i<=mid&&tmp[i].x<=tmp[j].x){
           if(tmp[i].op==0){
              add(tmp[i].y,tree,tmp[i].x+tmp[i].y);
           }
           i++;
        }
        if(tmp[j].op>0){
            if(query(tmp[j].y,tree)==INT_MIN)continue;
            ans[tmp[j].op]=min(ans[tmp[j].op],tmp[j].x+tmp[j].y-query(tmp[j].y,tree));
        }
    }
    for(int z=l;z<i;z++){
        clear(tmp[z].y,tree);
    }
    sort(tmp.begin()+l,tmp.begin()+r+1,[](node a,node b){
        return a.x<b.x;
    });
}
int main(){
    int n,m;
    cin>>n>>m;
    vector<node>arr;
      int limit=INT_MIN;
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        x++;
        y++;
            limit=max(limit,max(x,y));
        arr.push_back({0,x,y});
    }
    int cnt=1;
    for(int i=0;i<m;i++){
        int t;
        cin>>t;
        if(t==1){
            int x,y;
            cin>>x>>y;
            x++;
        y++;
            limit=max(limit,max(x,y));
            arr.push_back({0,x,y});
        }
        else{
            int x,y;
            cin>>x>>y;
            x++;
            y++;
               limit=max(limit,max(x,y));
            arr.push_back({cnt++,x,y});
        }
    }
    limit++;
    vector<int>ans(cnt,INT_MAX);
    vector<int>tree(limit,INT_MIN);
   vector<node>tmp=arr;
   cdq(0,tmp.size()-1,tmp,ans,tree);
   for(int i=0;i<arr.size();i++){
    tmp[i].op=arr[i].op;
    tmp[i].x=limit-arr[i].x;
    tmp[i].y=arr[i].y;
   }
    cdq(0,tmp.size()-1,tmp,ans,tree);
     for(int i=0;i<arr.size();i++){
    tmp[i].op=arr[i].op;
    tmp[i].x=limit-arr[i].x;
    tmp[i].y=limit-arr[i].y;
   }
   cdq(0,tmp.size()-1,tmp,ans,tree);
       for(int i=0;i<arr.size();i++){
    tmp[i].op=arr[i].op;
    tmp[i].x=arr[i].x;
    tmp[i].y=limit-arr[i].y;
   }
   cdq(0,tmp.size()-1,tmp,ans,tree);
   for(int i=1;i<cnt;i++){
    cout<<ans[i]<<'\n';
   }


}