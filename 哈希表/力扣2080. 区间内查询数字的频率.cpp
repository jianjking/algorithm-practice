#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class RangeFreqQuery {
public:
    unordered_map<int, vector<int>>cnt;
    RangeFreqQuery(vector<int>& arr) {
        cnt.clear();
        int n = arr.size();
        for (auto& p : cnt) {
            p.second.resize(n);
        }
        for (int i = 0;i <n;i++) {
            cnt[arr[i]].push_back(i);
        }
    }

    int query(int left, int right, int value) {
        auto l = lower_bound(cnt[value].begin(), cnt[value].end(), left) - cnt[value].begin();
        auto r = upper_bound(cnt[value].begin(), cnt[value].end(), right) - cnt[value].begin();
        return r - l;
    }
};
