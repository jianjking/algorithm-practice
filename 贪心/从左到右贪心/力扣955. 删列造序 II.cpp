#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int n = A.size(), m = A[0].size();
        int ans = 0;
        vector<bool> locked(n - 1, false);

        for (int j = 0; j < m; ++j) {
            bool canKeep = true;
            for (int i = 0; i < n - 1; ++i) {
                if (!locked[i] && A[i][j] > A[i + 1][j]) {
                    canKeep = false;
                    break;
                }
            }
            if (!canKeep) {
                ++ans;
                continue;
            }
            for (int i = 0; i < n - 1; ++i) {
                if (!locked[i] && A[i][j] < A[i + 1][j]) {
                    locked[i] = true;
                }
            }
        }
        return ans;
    }
};
