#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    void add(int a, int b, vector<int>& tree) {
        int n = tree.size();
        while (a < n) {
            tree[a] += b;
            a += a & (-a);
        }
    }
    long long query(int a, vector<int>& tree) {
        long long sum = 0;
        while (a > 0) {
            sum += tree[a];
            a -= a & (-a);
        }
        return sum;
    }
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int>graph;
        int n = nums1.size();
        int cnt = 0;
        for (int i = 0;i < n;i++) {
            graph[nums1[i]] = i + 1;
        }
        for (int i = 0;i < n;i++) {
            nums2[i] = graph[nums2[i]];
        }
        vector<int>tree(n + 1, 0);
        long long ans = 0;
        //n-nums2[i]-i+tmp;
        for (int i = 0;i < n;i++) {
            long long tmp = query(nums2[i] - 1, tree);
            ans += tmp * (n - nums2[i] - i + tmp);
            add(nums2[i], 1, tree);
        }
        return ans;
    }

};