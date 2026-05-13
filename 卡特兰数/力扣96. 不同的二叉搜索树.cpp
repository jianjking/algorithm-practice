#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numTrees(int n) {
        if(n==1)return 1;
        vector<int>nums(n+1,1);
        for(int i=2;i<=n;i++){
            nums[i]=0;
            for(int j=0;j<i;j++){
               nums[i]+=nums[j]*nums[i-1-j];
            }
        }
        return nums[n];
    }
};