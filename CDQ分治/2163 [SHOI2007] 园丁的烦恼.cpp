#include<bits/stdc++.h>
using namespace std;

struct node{
   int x;
   int y;
   int v;
   int nums;
};

void cdq(int l,int r,vector<node>&arr,vector<int>&ans){
    if(l>=r)return;

    int mid=(l+r)/2;

    cdq(l,mid,arr,ans);
    cdq(mid+1,r,arr,ans);

    int i=l;
    int cnt=0;

    for(int j=mid+1;j<=r;j++){
        while(i<=mid&&arr[i].y<=arr[j].y){
            if(arr[i].nums==0){
                cnt++;
            }
            i++;
        }

        if(arr[j].nums>0){
            ans[arr[j].nums]+=arr[j].v*cnt;
        }
    }

    vector<node>tmp;
    tmp.reserve(r-l+1);

    int p1=l;
    int p2=mid+1;

    while(p1<=mid&&p2<=r){
        if(arr[p1].y<=arr[p2].y){
            tmp.push_back(arr[p1++]);
        }
        else{
            tmp.push_back(arr[p2++]);
        }
    }

    while(p1<=mid){
        tmp.push_back(arr[p1++]);
    }

    while(p2<=r){
        tmp.push_back(arr[p2++]);
    }

    for(int i=l;i<=r;i++){
        arr[i]=tmp[i-l];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m;

    vector<node>arr;

    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        arr.push_back({x,y,1,0});
    }

    for(int i=1;i<=m;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;

        arr.push_back({c,d,1,i});
        arr.push_back({c,b-1,-1,i});
        arr.push_back({a-1,d,-1,i});
        arr.push_back({a-1,b-1,1,i});
    }

    sort(arr.begin(),arr.end(),[](node a,node b){
         if(a.x!=b.x)return a.x<b.x;
         if(a.nums!=b.nums)return a.nums<b.nums;
         if(a.y!=b.y)return a.y<b.y;
         return a.v<b.v;
    });

    vector<int>ans(m+1,0);

    cdq(0,(int)arr.size()-1,arr,ans);

    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }

    return 0;
}