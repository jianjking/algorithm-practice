#include<iostream>
#include<vector>
#include<queue>
#include<tuple>
using namespace std;
using ll = long long;
struct compare {
    bool operator()(const tuple<ll, ll, int>& a, const tuple<ll, ll, int>& b)const {
        return get<0>(a) > get<0>(b);
    }
};
class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        priority_queue<tuple<ll, ll, int>, vector<tuple<ll, ll, int>>, compare>f;
        for (auto& p : workerTimes)f.push({ p,p,1 });
        ll time = 0;
        while (mountainHeight > 0) {
            auto a = f.top();
            f.pop();
            time = get<0>(a);
            get<2>(a)++;
            f.push({ get<0>(a) + get<2>(a) * get<1>(a),get<1>(a),get<2>(a) });
            mountainHeight--;
        }
        return time;
    }
};