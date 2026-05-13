#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;
class Bitset {
private:
    vector<uint32_t> bits;  // 存储位的数组
    int sz;                 // 总位数
    int ones, zeros;        // 当前 1 和 0 的数量
    uint32_t last_mask;     // 用于屏蔽最后一块里多余的高位

public:
    Bitset(int size)
        : bits((size + 31) / 32, 0), sz(size), ones(0), zeros(size)
    {
        int tail = size % 32;
        if (tail == 0)
            last_mask = 0xFFFFFFFFu;
        else
            last_mask = (1u << tail) - 1;
    }

    void fix(int idx) {
        int blk = idx / 32, off = idx % 32;
        uint32_t mask = 1u << off;
        if ((bits[blk] & mask) == 0) {
            bits[blk] |= mask;
            ++ones;
            --zeros;
        }
    }

    void unfix(int idx) {
        int blk = idx / 32, off = idx % 32;
        uint32_t mask = 1u << off;
        if (bits[blk] & mask) {
            bits[blk] &= ~mask;
            --ones;
            ++zeros;
        }
    }

    void flip() {
        for (auto& b : bits) {
            b = ~b;
        }
        // 屏蔽掉尾部多余的高位
        bits.back() &= last_mask;
        swap(ones, zeros);
    }

    bool all() const {
        return ones == sz;
    }

    bool one() const {
        return ones > 0;
    }

    int count() const {
        return ones;
    }

    string toString() const {
        string s;
        s.reserve(sz);
        for (int i = 0; i < sz; ++i) {
            int blk = i / 32, off = i % 32;
            s.push_back(((bits[blk] >> off) & 1) ? '1' : '0');
        }
        return s;
    }
};
