#include<bits/stdc++.h>
using namespace std;

struct node{
    long long x;
    long long r;
    long long q;
    int ledge;
    int redge;
};

int lowbit(int i){
   return i&(-i);
}

void add(int i,vector<int>&tree,int v){
    int n=tree.size()-1;
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
    }
}

int query(int i,vector<int>&tree){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
    }
    return ans;
}

long long ans=0;

void cdq(int l,int r,vector<node>&arr,int k,vector<int>&tree){
    if(l>=r)return;

    int mid=(l+r)/2;

    cdq(l,mid,arr,k,tree);
    cdq(mid+1,r,arr,k,tree);

    int i=l,j=l-1;

    for(int z=mid+1;z<=r;z++){
        while(j+1<=mid && arr[j+1].q<=arr[z].q+k){
            j++;
            add(arr[j].x,tree,1);
        }

        while(i<=j && arr[i].q<arr[z].q-k){
            add(arr[i].x,tree,-1);
            i++;
        }

        ans+=query(arr[z].redge,tree)-query(arr[z].ledge-1,tree);
    }

    for(int u=i;u<=j;u++){
        add(arr[u].x,tree,-1);
    }

    sort(arr.begin()+l,arr.begin()+r+1,[](node a,node b){
        return a.q<b.q;
    });
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    cin>>n>>k;

    vector<node>arr(n);
    vector<long long>nums;

    for(int i=0;i<n;i++){
        cin>>arr[i].x>>arr[i].r>>arr[i].q;
        nums.push_back(arr[i].x);
    }

    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());

    for(int i=0;i<n;i++){
        long long v=arr[i].x;

        arr[i].x=lower_bound(nums.begin(),nums.end(),v)-nums.begin()+1;
        arr[i].ledge=lower_bound(nums.begin(),nums.end(),v-arr[i].r)-nums.begin()+1;
        arr[i].redge=upper_bound(nums.begin(),nums.end(),v+arr[i].r)-nums.begin();
    }

    sort(arr.begin(),arr.end(),[](node a,node b){
        if(a.r!=b.r)return a.r>b.r;
        if(a.x!=b.x)return a.x<b.x;
        return a.q<b.q;
    });

    vector<int>tree(nums.size()+1,0);

    cdq(0,n-1,arr,k,tree);

    cout<<ans<<'\n';

    return 0;
}