#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<tuple>
using namespace std;
struct compare {
    bool operator()(const tuple<int, int, int>& a, const tuple<int, int, int>& b)const {
        if (get<0>(a) != get<0>(b))return get<0>(a) > get<0>(b);
        return get<2>(a) < get<2>(b);
    }
};
struct pare {
    bool operator()(const int& a, const int& b) {
        return a > b;
    }
};
class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int n = times.size();
        vector<int>nums;
        nums.reserve(2 * n);
        for (int i = 0;i < n;i++) {
            nums.push_back(times[i][0]);
            nums.push_back(times[i][1]);
        }
        sort(nums.begin(), nums.end());
        auto p = unique(nums.begin(), nums.end());
        nums.erase(p, nums.end());
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, compare>f;
        int cnt = 0;
        vector<bool>vis(n, false);
        priority_queue<int, vector<int>, pare>f1;
        for (int i = 0;i < n;i++) {
            int tmp = lower_bound(nums.begin(), nums.end(), times[i][0]) - nums.begin();
            f.push({ tmp,i,-1 });

        }
        while (true) {
            tuple<int, int, int>tmp = f.top();
            f.pop();
            int a = get<0>(tmp);
            int b = get<1>(tmp);
            int c = get<2>(tmp);
            if (b == targetFriend) {
                if (f1.empty()) {
                    return cnt;
                }
                else {
                    return min(f1.top(), cnt);
                }
            }
            if (c == -1) {
                int d = lower_bound(nums.begin(), nums.end(), times[b][1]) - nums.begin();
                if (f1.empty()) {

                    f.push({ d,b,cnt++ });
                }
                else {
                    f.push({ d,b,f1.top() });
                    f1.pop();
                }
            }
            else {
                f1.push({ c });
            }
        }
        return -1;
    }
};