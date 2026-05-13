#include<iostream>
#include<vector>
using namespace std;
vector<vector<long long>> mult(const vector<vector<long long>>& arr, const  vector<vector<long long>>& brr) {
    int n1 = arr.size();
    int m1 = brr.size();
    int n2 = arr[0].size();
    vector<vector<long long>>ans(n1, vector<long long>(m1, 0));
    for (int i = 0;i < n1;i++) {
        for (int j = 0;j < m1;j++) {
            for (int z = 0;z < n2;z++) {
                ans[i][j] += arr[i][z] * brr[z][j];
            }
        }
    }
    return ans;
}
vector<vector<long long>> power(vector<vector<long long>>& arr, int k) {
    vector<vector<long long>>res = { {1,0,0},{0,1,0},{0,0,1} };
    while (k) {
        if (k & 1)res = mult(res, arr);
        arr = mult(arr, arr);
        k >>= 1;
    }
    return res;
}
class Solution {
public:
    int tribonacci(int n) {
        if (n == 0)return 0;
        if (n == 1)return 1;
        if (n == 2)return 1;
        vector<vector<long long>>cst = { { 1,1,0 }
        };
        vector<vector<long long>>arr = { {1,1,0},{1,0,1},{1,0,0} };
        vector<vector<long long>>ans = mult(cst, power(arr, n - 2));
        return ans[0][0];
    }
};