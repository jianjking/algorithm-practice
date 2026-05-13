#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int sum = 0;
        int n = machines.size();
        for (auto& p : machines) {
            sum+=p;
        }
        if (sum % n)return -1;
        int ans = 0;
        int avg = sum / n;
        int leftsum = 0;
        for (int i = 0;i < n;leftsum+=machines[i],i++) {
            int left = avg * i-leftsum;
            int right = avg * (n - 1 - i) - sum + leftsum + machines[i];
            int a;
            if (left > 0 && right > 0) {
                a = left + right;
            }
            else {
                a = max(abs(left), abs(right));
            }
            ans = max(ans, a);
        }
        return ans;
    }
};