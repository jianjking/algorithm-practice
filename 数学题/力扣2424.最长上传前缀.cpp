#include<iostream>
#include<vector>
using namespace std;
class LUPrefix {
public:
    vector<bool>dp;
    int cnt ;
    LUPrefix(int n) {
        cnt = 1;
        dp.resize(n, false);
    }
    void update() {
        while (dp[cnt])cnt++;
    }
    void upload(int video) {
        dp[video] = true;
    }
   
    int longest() {
        return cnt - 1;
    }
};
