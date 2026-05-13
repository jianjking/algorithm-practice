#include<bits/stdc++.h>
using namespace std;
struct compare{
   bool operator()(const vector<int>&a,const vector<int>&b)const{
     if(a[0]!=b[0])return a[0]<b[0];
        if(a[1]!=b[1])return a[1]<b[1];
        return a[2]<b[2];
   }
};
class Solution {
public:
    long long maxSpending(vector<vector<int>>& values) {
        int m=values.size();
        int n=values[0].size();
        long long ans=0;
        set<vector<int>,compare>s;
        for(int i=0;i<m;i++){
            s.insert({values[i][n-1],i,n-1});
        }
        int cnt=1;
        while(!s.empty()){
            auto top=*s.begin();
            ans+=1LL*top[0]*cnt;
            cnt++;
            s.erase(s.begin());
            if(top[2]-1>=0){
                s.insert({values[top[1]][top[2]-1],top[1],top[2]-1});
            }
        }
        return ans;
    }
};
