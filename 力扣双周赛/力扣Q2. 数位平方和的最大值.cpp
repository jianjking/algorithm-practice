#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        string s;
        while(num&&sum){
            if(sum>9){
                s+='9';
                sum-=9;
            }
            else{
                s+='0'+sum-0;
                sum=0;
            }
            num--;
        }
        if(num==0&&sum>0)return "";
         while(num){
            num--;
            s+="0";
         }
        return s;
    }
};©leetcode