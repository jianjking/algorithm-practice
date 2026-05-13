#include<Iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<long long>arr;
        int m = queries.size();
        vector<int>ans(m);
        while (n) {
            int tmp = n & (-n);
            n -= tmp;
            arr.push_back(tmp);
        }

        for (int i = 0;i < m;i++) {
            long long sum = 1;
            for (int j = queries[i][0];j <= queries[i][1];j++) {
                sum = (sum * arr[j]) % mod;
            }
            ans[i] = sum;
        }
        return ans;
    }
};