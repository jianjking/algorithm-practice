#include<bits/stdc++.h>
using namespace std;
int main(){
    int total=2*1e3;
    vector<vector<int>>nums(total+1,vector<int>(total+1,1));
    int t,k;
    cin>>t>>k;
    for(int i=2;i<=total;i++){
        for(int j=1;j<i;j++){
            nums[i][j]=(nums[i-1][j]+nums[i-1][j-1])%k;
        }
    }
    vector<vector<long long>>sum(total+2,vector<long long>(total+2,0));
    for(int i=1;i<=total+1;i++){
        for(int j=1;j<=total+1;j++){
            sum[i][j]=sum[i-1][j]-sum[i-1][j-1]+sum[i][j-1];
            if(nums[i-1][j-1]==0)sum[i][j]++;
        }
    }
    for(int i=0;i<t;i++){
        int n,m;
        cin>>n>>m;
        cout<<sum[n+1][m+1]<<'\n';
    }
}