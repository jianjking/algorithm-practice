#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    size_t operator()(const pair<int,int>& p) const noexcept {
        // 把两个 32 位合成 64 位，再异或一下，避免负数影响用无符号
        uint64_t x = static_cast<uint32_t>(p.first);
        uint64_t y = static_cast<uint32_t>(p.second);
        return (x << 32) ^ y;
    }
};

class DetectSquares {
public:
    unordered_map<pair<int,int>, int, PairHash> cnt;

    DetectSquares() {}  // 不必手动 clear

    void add(vector<int> point) {
        cnt[{point[0], point[1]}]++;
    }

    // 辅助：查询而不插入
    int get(int x, int y) {
        auto it = cnt.find({x, y});
        return (it == cnt.end() ? 0 : it->second);
    }

    int count(vector<int> point) {
        int x = point[0], y = point[1];
        int ans = 0;

        // 只枚举“同一横坐标的点”（也可以只枚举同一纵坐标的点）
        // 为了和你原思路接近，这里遍历所有已存在的点，然后筛选 y 相同的
        for (auto &kv : cnt) {
            int x1 = kv.first.first;
            int y1 = kv.first.second;
            if (y1 != y || x1 == x) continue; // 不是同一行/或同列同点，跳过
            int len = abs(x1 - x);
            int c   = kv.second; // (x1,y) 的计数
            // 两个正方形：上、下
            ans += c * ( get(x,  y+len) * get(x1, y+len)
                       + get(x,  y-len) * get(x1, y-len) );
        }
        return ans;
    }
};
