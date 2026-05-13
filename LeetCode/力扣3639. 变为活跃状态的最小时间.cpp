#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minTime(string s, vector<int>& order, int k) {
        set<int>nums;
        int n=order.size();
        nums.insert(-1);
        nums.insert(n);
        int sum=0;
        for(int t=0;t<n;t++){
              int tmp=order[t];
              auto p=nums.lower_bound(tmp);
              p--;
              int l=*p;
              int r=*nums.upper_bound(tmp);
             sum+=(r-tmp)*(tmp-l);
             nums.insert(tmp);
             if(sum>=k)return t;
        }
       return -1;
    }
};