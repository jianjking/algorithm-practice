#include<bits/stdc++.h>
using namespace std;

struct cow{
    long long v;
    long long x;
};

const long long mod = 998244353;
long long ans = 0;

void cdq(int l,int r,vector<cow>&arr){
    if(l>=r) return;

    int mid=(l+r)/2;

    cdq(l,mid,arr);
    cdq(mid+1,r,arr);

    long long lsum=0;
    long long rsum=0;

    for(int i=l;i<=mid;i++){
        rsum += arr[i].x;
    }

    int i=l;

    for(int j=mid+1;j<=r;j++){
        while(i<=mid && arr[i].x < arr[j].x){
            lsum += arr[i].x;
            rsum -= arr[i].x;
            i++;
        }

        long long cntl = i - l;
        long long cntr = mid - i + 1;

        long long dis = cntl * arr[j].x - lsum + rsum - cntr * arr[j].x;

        ans = (ans + arr[j].v % mod * (dis % mod)) % mod;
    }

    vector<cow> tmp;
    int p1=l;
    int p2=mid+1;

    while(p1<=mid && p2<=r){
        if(arr[p1].x <= arr[p2].x){
            tmp.push_back(arr[p1++]);
        }else{
            tmp.push_back(arr[p2++]);
        }
    }

    while(p1<=mid) tmp.push_back(arr[p1++]);
    while(p2<=r) tmp.push_back(arr[p2++]);

    for(int k=0;k<tmp.size();k++){
        arr[l+k]=tmp[k];
    }
}

int main(){
    int n;
    cin>>n;

    vector<cow> arr(n);

    for(int i=0;i<n;i++){
        cin>>arr[i].v>>arr[i].x;
    }

    sort(arr.begin(),arr.end(),[](cow a,cow b){
        if(a.v!=b.v) return a.v<b.v;
        return a.x<b.x;
    });

    cdq(0,n-1,arr);

    cout<<ans%mod<<'\n';

    return 0;
}