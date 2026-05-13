#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minFlips(string target) {
        int ans = 0;
        int n = target.size();
        for (int i = 0;i < n;i++) {
            if ((ans % 2 == 0&&target[i]!='0')||(ans%2==1&&target[i]!='1') ){
                ans++;
            }
            
        }
        return ans;
    }
};