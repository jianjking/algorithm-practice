#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int n=arr1.size();
        int m=arr2.size();
        unordered_map<int,int>cnt;
        for(int i=0;i<m;i++){
            for(int j=31;j>=0;j--){
                if((arr2[i]>>j)&1)cnt[j]++;
            }
        }
        int ans=0;
        for(int i=31;i>=0;i--){
          long long sum=0;
          for(int j=0;j<n;j++){
            if((arr1[j]>>i)&1){
                sum+=cnt[i];
            }
          }
          if(sum%2){
            ans|=1<<i;
          }
        }
        return ans;
    }
};