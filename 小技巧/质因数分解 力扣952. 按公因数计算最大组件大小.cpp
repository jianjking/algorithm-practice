#include<iostream>
#include<vector>
using namespace std;
const int MAX = 1e5 + 1;
class Solution {
public:
    vector<int>father;
    vector<int>size;
    vector<int>app;
    int root(int a) {
        if (a != father[a])father[a] = root(father[a]);
        return father[a];
    }
    void unio(int i, int j) {
        int fx = root(i);
        int fy = root(j);
        if (fx != fy) {
            size[fx] += size[fy];
            father[fy] = fx;
        }
    }
    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        father.assign(n, 0);
        app.assign(MAX, -1);
        size.assign(n, 1);
        for (int i = 0;i < n;i++) {
            father[i] = i;
        }
        //分解质因数
        for (int i = 0;i < n;i++) {
            int tmp = nums[i];
            for (int j = 2;j * j <= tmp;j++) {
                if (tmp % j == 0) {
                    if (app[j] == -1)app[j] = i;
                    else {
                        unio(i, app[j]);
                    }
                    while (tmp % j == 0) {
                        tmp /= j;
                    }
                }
            }
            if (tmp > 1) {

                if (app[tmp] == -1) app[tmp] = i;
                else                unio(i, app[tmp]);
            }
        }
        int ans = INT_MIN;
        for (auto& p : size) {
            ans = max(ans, p);
        }
        return ans;
    }
};