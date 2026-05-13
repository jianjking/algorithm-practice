#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<vector<long long>>nums(n,vector<long long>(n,1));
    for(int i=1;i<n;i++){
        for(int j=1;j<i;j++){
          nums[i][j]=nums[i-1][j-1]+nums[i-1][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            cout<<nums[i][j]<<" ";
        }
        cout<<'\n';
    }
}