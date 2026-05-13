#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct compare {
    bool operator()(int a, int b) {
        return a > b;
    }
};
class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int n = heights.size();
        int ans = 0;
        priority_queue<int, vector<int>, compare>heap;
        for (int i = 1;i < n;i++) {
            if (heights[i - 1] >= heights[i]) {
                ans++;
            }
            else {
                if (ladders > 0) {
                    heap.push(heights[i] - heights[i - 1]);
                    ladders--;
                    ans++;
                }
                else {
                    if (!heap.empty() && heights[i] - heights[i - 1] > heap.top()) {
                        int a = heap.top();
                        bricks -= a;
                        heap.pop();
                        if (bricks < 0)return ans;
                        heap.push(heights[i] - heights[i - 1]);
                        ans++;
                    }
                    else {
                        if (bricks >= heights[i] - heights[i - 1]) {
                            bricks -= heights[i] - heights[i - 1];

                            ans++;
                        }
                        else {
                            return ans;
                        }
                    }




                }
            }
        }
        return ans;
    }
};