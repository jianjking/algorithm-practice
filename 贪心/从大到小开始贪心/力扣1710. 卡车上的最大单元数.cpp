#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        sort(boxTypes.begin(), boxTypes.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] > b[1];
            });
        int n = boxTypes.size();
        int ans = 0;
        for (int i = 0;i < n && truckSize>0;i++) {
            if (truckSize >= boxTypes[i][0]) {
                truckSize -= boxTypes[i][0];
                ans += boxTypes[i][0] * boxTypes[i][1];
            }
            else {
                ans += boxTypes[i][1] * truckSize;
                break;
            }
        }
        return ans;

    }
};