#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
struct GGG {
    double a;
    int b;
};
struct compare {
    bool operator()(int a, int b) {
        return a < b;
    }
};
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<GGG>arr(n);
        for (int i = 0;i < n;i++) {
            GGG c;
            c.a = (double)wage[i] / quality[i];
            c.b = quality[i];
            arr[i] = c;
        }
        long long sum = 0;
        double ans = numeric_limits<double>::max();
        sort(arr.begin(), arr.end(), [](GGG a, GGG b) {
            return a.a < b.a;
            });
        priority_queue<int, vector<int>, compare>heap;
        for (int i = 0;i < n;i++) {
            if (heap.size() < k) {
                heap.push(arr[i].b);
                sum += arr[i].b;
                if (heap.size() == k) {
                    ans = min(ans, sum * arr[i].a);
                }
            }
            else {
                if (arr[i].b < heap.top()) {
                    sum -= heap.top();
                    sum += arr[i].b;
                    heap.pop();
                    heap.push(arr[i].b);
                    ans = min(ans, sum * arr[i].a);
                }
            }
        }
        return ans;
    }
};