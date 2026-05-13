#include<iostream>
#include <vector>
#include<queue>
using namespace std;
struct GGG {
    int a;
    int b;
    double c;
};
struct compare {
    bool operator()(const GGG& a, const GGG& b)const {
        return a.c < b.c;
    }
};
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        priority_queue<GGG, vector<GGG>, compare>heap;
        int n = classes.size();
        for (int i = 0;i < n;i++) {
            int a = classes[i][0];
            int b = classes[i][1];
            GGG c = { a,b,(a + 1) / (double)(b + 1) - (double)a / b };
            heap.push(c);
        }
        while (extraStudents) {
            GGG c = heap.top();
            c.a++;
            c.b++;
            c.c = (double)(c.a + 1) / (c.b + 1) - (double)c.a / c.b;
            heap.pop();
            heap.push(c);
            extraStudents--;
        }
        double ans = 0;
        while (!heap.empty()) {
            GGG d = heap.top();
            ans += (double)d.a / d.b;
            heap.pop();
        }
        return ans / n;
    }
};