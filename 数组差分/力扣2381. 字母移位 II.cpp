#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n = s.size();
        vector<int>diff(n, 0);
        for (auto& p : shifts) {
            int tmp = p[2] == 0 ? -1 : 1;
            diff[p[0]] += tmp;
            if (p[1] < n)diff[p[1] + 1]--;
        }
        for (int i = 1; i < n; i++) {
            diff[i] += diff[i - 1];
        }
        for (int i = 0; i < n;i++) {
            s[i] = (((s[i] - 'a' + diff[i]) % 26) + 26) % 26 + 'a';
        }
        return s;
    }
};