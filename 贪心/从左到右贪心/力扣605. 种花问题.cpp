#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool canPlaceFlowers(vector<int>& arr, int n) {
        int m = arr.size();
        for (int i = 0;i < m;i++) {
            if (arr[i] == 0) {
                if ((i + 1 >= m || arr[i + 1] == 0) && (i - 1 < 0 || arr[i - 1] == 0)) {
                    n--;
                    arr[i] = 1;
                }
            }
            if (n <= 0)return true;
        }
        return false;
    }
};