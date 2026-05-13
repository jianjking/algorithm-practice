#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int>father;
    int cnt1;
    int cnt2;
    int root(int a) {
        if (a != father[a])a = root(father[a]);
        return father[a];
    }
    void unin(int a, int b) {
        int a1 = root(a);
        int b1 = root(b);
        if (a1 == b1) {
            cnt2++;
            return;
        }
        father[a1] = b1;
        cnt1--;
    }
    int makeConnected(int n, vector<vector<int>>& connections) {
        cnt1 = n;
        cnt2 = 0;
        father.assign(n, 0);
        for (int i = 0;i < n;i++) {
            father[i] = i;
        }
        int m = connections.size();
        for (int i = 0;i < m;i++) {
            int x1 = connections[i][0];
            int y1 = connections[i][1];
            unin(x1, y1);
        }
        if (cnt1 - 1 > cnt2)return -1;
        return cnt1 - 1;
    }
};