#include <vector>
using namespace std;

// --- 自己的 swap ---
static inline void myswap(int &x, int &y){ int t = x; x = y; y = t; }

// --- 原地反转 [L..R] ---
static inline void reverse_range(vector<int>& a, int L, int R){
    while (L < R){ myswap(a[L], a[R]); ++L; --R; }
}

// --- 右旋 [L..R] 按 (R-M) 位：等价于三次反转 ---
static inline void rotate_right(vector<int>& a, int L, int M, int R){
    // 把区间分成 [L..M] 和 [M+1..R]，右边块搬到前面
    reverse_range(a, L,   M);
    reverse_range(a, M+1, R);
    reverse_range(a, L,   R);
}

// --- 循环领袖：对 l 开始的 2*m 个元素做置换 i -> (2*i) mod (2*m+1)（1-based）---
static inline void cycle_leader(vector<int>& a, int l, int m){
    int mod = 2*m + 1;                // 工作段长度 = 2m
    // 依次处理起点 1,3,9,...(< 2m+1) 的所有环
    for (int start = 1; start < mod; start *= 3){
        int cur = start;
        int tmp = a[l + cur - 1];     // 1-based 到 0-based 的偏移
        do{
            cur = (cur * 2) % mod;    // 置换映射
            myswap(tmp, a[l + cur - 1]);
        } while (cur != start);
    }
}

// --- 完美洗牌：把 [l..r]（长度必须为偶数 2n）重排成交替 a1,b1,a2,b2,... ---
void perfect_shuffle(vector<int>& a, int l, int r){
    int n = (r - l + 1) / 2;          // 一半长度 n（即 m）
    while (n > 0){
        // 取最大 p = 3^k，使 p <= 2n+1；令 m = (p-1)/2，本轮处理前缀 2m
        int p = 1;
        while (p * 3 <= 2*n + 1) p *= 3;
        int m = (p - 1) / 2;          // 1 <= m <= n

        // 1) 块旋转：把 [a_{m+1}..a_n | b_1..b_m] 右旋 m 位
        //    对应下标：左块 [l+m .. l+n-1]，右块 [l+n .. l+n+m-1]
        rotate_right(a, l + m, l + n - 1, l + n + m - 1);

        // 2) 对前 2m 元素做循环领袖置换 => a1,b1,a2,b2,...,am,bm
        cycle_leader(a, l, m);

        // 3) 缩小到剩余部分继续
        l += 2*m;
        n -= m;
    }
}
