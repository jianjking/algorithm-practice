#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    int root(char a, vector<int>& father) {
        if (a - 'a' != father[a - 'a'])father[a - 'a'] = root(father[a - 'a'] + 'a', father);
        return father[a - 'a'];
    }
    void unio(char a, char b, vector<int>& father) {
        int c = root(a, father);
        int d = root(b, father);
        if (c == d)return;
        father[c] = d;
    }
    bool equationsPossible(vector<string>& equations) {
        vector<int>father(26);
        for (int i = 0;i < 26;i++) {
            father[i] = i;
        }
        int n = equations.size();
        for (int i = 0;i < n;i++) {
            char aa = equations[i][0];
            char cc = equations[i][3];
            char bb = equations[i][1];
            if (bb == '=') {
                unio(aa, cc, father);
            }
        }
        for (int i = 0;i < n;i++) {
            char aa = equations[i][0];
            char cc = equations[i][3];
            char bb = equations[i][1];
            if (bb == '!') {
                if (root(aa, father) == root(cc, father))return false;
            }
        }
        return true;
    }
};