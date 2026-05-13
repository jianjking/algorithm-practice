#include<vector>
#include<iostream>
using namespace std;
//还有这个还可以用dfs解我真不会了
//其实加一个size数组就不会这么麻烦进行计数了，但我懒得写了算了，算我让着你，我还是写写吧 但好像每蛋用我也不会了就交给你了
class Solution {
public:
    vector<int>father;
    vector<int>sum;
    vector<int>size1;
    int root(int a) {
        vector<int>stack;
        while (a != father[a]) {
            stack.push_back(a);
            a = father[a];
        }
        while (!stack.empty()) {
            int b = stack.back();
            father[b] = a;
            stack.pop_back();
        }
        return a;
    }
    void merge(int a, int b) {
        int c = root(a);
        int d = root(b);
        if (c == d)return;
        father[c] = d;
      
    }
    long long countPairs(int n, vector<vector<int>>& edges) {
        if (edges.empty())return (long)n * (n - 1) / 2;
        father.resize(n);
        sum.resize(n, 0);
        size1.resize(n, 1);
        for (int i = 0;i < n;i++)father[i] = i;
        for (auto& p : edges) {
            int a = p[0];
            int b = p[1];
            merge(a, b);
        }
        int d = n + 1;
        int cnt = 0;
        for (int i = 0;i < n;i++) {
            int c = root(i);
            if (d != c) {
                d = c;
                cnt++;
            }
            sum[c]++;
        }

        long long ans = 0;
        vector<int>arr;
        for (int i = 0;i < n;i++) {
            if (sum[i] != 0) {
                arr.push_back(sum[i]);
            }
        }
        for (int i = 0;i < arr.size();i++) {
            for (int j = i + 1;j < arr.size();j++) {
                ans += (long long)arr[i] * arr[j];
            }
        }
        return cnt == 1 ? 0 : ans;
    }
};