#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minSetSize(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int a = 1;
        vector<int>num;
        for (int i = 1;i < n;i++) {
            while (i < n&& arr[i] == arr[i - 1]) {
                a++;
                i++;
            }
            num.push_back(a);
            a = 1;
        }
        if (arr[n - 1] != arr[n - 2])num.push_back(1);
        sort(num.begin(), num.end(), [](int a, int b) {
            return a > b;
            });
        int ans = 0;
        int tmp = n;
        for (int i = 0;i < num.size();i++) {
            tmp -= num[i];
            ans++;
            if (tmp <= n / 2)return ans;

        }
        return 0;
    }
};