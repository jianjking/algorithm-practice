#include<bits/stdc++.h>

class Solution {
public:

    int findInMountainArray(int target, MountainArray &mountainArr) {
        int l=0;
        int n=mountainArr.length();
        int r=n-1;
        int mx;
        while(l<=r){
            int mid=l+(r-l)/2;
            int pre=INT_MIN;
            int back=INT_MAX;
            int value=mountainArr.get(mid);
            if(mid+1<n) back=mountainArr.get(mid+1);
            if(mid-1>=0) pre=mountainArr.get(mid-1);
            if(back<value&&pre<value){
                mx=mid;
                break;
            }
            if(back>value){
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        if(mountainArr.get(mx)==target){
            return mx;
        }
        int x=0;
        int y=mx;
        while(x<=y){
       int mid=x+(y-x)/2;
       int value=mountainArr.get(mid);
       if(value==target){
        return mid;
       }
       else if(value<target){
        x=mid+1;
       }
       else{
         y=mid-1;
       }
    }
    x=mx+1;
    y=n-1;
    while(x<=y){
       int mid=x+(y-x)/2;
       int value=mountainArr.get(mid);
       if(value==target){
        return mid;
       }
       else if(value<target){
        y=mid-1;
       }
       else{
         x=mid+1;
       }
    }
    return -1;
    }
};