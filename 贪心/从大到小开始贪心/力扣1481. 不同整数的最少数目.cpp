#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());
        vector<int>cnt;
        int n = arr.size();
        int ans = 1;
        if (n <= 1)return k < n;
        for (int i = 1;i < n;i++) {
            while (i < n && arr[i] == arr[i - 1]) {
                i++;
                ans++;
            }
            cnt.push_back(ans);
            ans = 1;
        }
        if (arr[n - 1] != arr[n - 2])cnt.push_back(ans);
        sort(cnt.begin(), cnt.end());
        ans = cnt.size();
        int m = cnt.size();
        for (int i = 0;i < m;i++) {
            if (k >= cnt[i]) {
                ans--;
                k -= cnt[i];
            }
            if (k <= 0) {
                return ans;
            }
        }
        return ans;
    }
};
