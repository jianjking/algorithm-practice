#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<int>arr(n);
        for (int i = 0;i < n;i++) {
            int cnt = 0;
            for (int j = 0;j < m;j++) {
                if (grid[i][j] == 0)
                    cnt++;
                else cnt = 0;
            }
            arr[i] = cnt;
        }
        int ans = 0;
        for (int i = 0;i < n;i++) {
            if (arr[i] >= m - i - 1)continue;
            else {
                bool a = false;
                for (int j = i + 1;j < n;j++) {
                    if (arr[j] >= m - i - 1) {
                        for (int z = j - 1;z >= i;z--) {
                            swap(arr[z], arr[z + 1]);
                            a = true;
                            ans++;

                        }
                        break;
                    }
                }
                if (!a)return -1;
            }
        }
        return ans;
    }
};