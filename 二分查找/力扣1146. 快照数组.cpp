#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class SnapshotArray {
public:
    int sid = 0;
    vector<vector<pair<int, int>>> hist; // hist[i]: {snap_id, val} 递增

    SnapshotArray(int length) : hist(length) {
        // 预置一个基线：在 snap_id = -1 时值为 0，方便二分
        for (auto& v : hist) v.push_back({ -1, 0 });
    }

    void set(int index, int val) {
        auto& v = hist[index];
        if (v.back().first == sid) {
            v.back().second = val;     // 同一快照内多次 set，覆盖
        }
        else {
            v.push_back({ sid, val });   // 新的快照号，追加记录
        }
    }

    int snap() {
        return sid++;                  // 返回旧的，再自增
    }

    int get(int index, int snap_id) const {
        const auto& v = hist[index];
        // 二分找最后一个 snap_id <= 目标 snap_id
        int l = 0, r = (int)v.size() - 1, ans = 0;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (v[m].first <= snap_id) { ans = v[m].second; l = m + 1; }
            else r = m - 1;
        }
        return ans;
    }
};
