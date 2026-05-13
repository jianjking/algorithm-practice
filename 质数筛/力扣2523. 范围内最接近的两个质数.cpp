#include<iostream>
#include<vector>
using namespace std;
const int limit = 1e6;
class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        vector<bool>yu(1e6 + 1, false);
        vector<int>arr;
        for (int i = 2;i <= limit;i++) {
            if (yu[i])continue;
            arr.push_back(i);
            for (int j = 2 * i;j <= limit;j += i) {
                yu[j] = true;
            }
        }
        auto p1 = lower_bound(arr.begin(), arr.end(), left) - arr.begin();
        auto p2 = upper_bound(arr.begin(), arr.end(), right) - arr.begin() - 1;
        if (p1 >= p2)return { -1,-1 };
        int a1, b1;
        int cha = INT_MAX;
        for (int i = p1 + 1;i <= p2;i++) {
            if (cha > arr[i] - arr[i - 1]) {
                a1 = arr[i - 1];
                b1 = arr[i];
                cha = arr[i] - arr[i - 1];
            }
        }
        return { a1,b1 };
    }
};