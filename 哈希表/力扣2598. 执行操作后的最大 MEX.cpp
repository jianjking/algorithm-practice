#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        vector<int>cnt(value,0);
        for(auto&p:nums){
            p=p%value;
            if(p<0)p+=value;
            cnt[p]++;
        }
       int mx=INT_MAX;
       int ans=0;
       for(int i=0;i<value;i++){
        if(cnt[i]<mx){
          mx=cnt[i];
          ans=i;
        }
       }
       return mx*value+ans;

}
};