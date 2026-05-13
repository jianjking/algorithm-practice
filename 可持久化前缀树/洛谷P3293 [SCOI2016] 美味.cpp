#include <bits/stdc++.h>
using namespace std;

const int maxn = 2*1e5 + 5;      // n, m 上限
const int maxt = 60 * maxn;      // 结点池(足够)
const int VALMAX = 200000;       // 值域：a ∈ [0..1e5-1]，a+x < 2e5，所以设到 2e5

int zuo[maxt], you[maxt], sz[maxt];
int root[maxn];
int cnt = 0;

// 在值域 [L..R] 上，把 pre 的计数在位置 x 加 1，返回新根
int insert(int pre, int x, int L, int R){
    int now = ++cnt;
    zuo[now] = zuo[pre];
    you[now] = you[pre];
    sz[now]  = sz[pre] + 1;
    if(L == R) return now;
    int mid = (L + R) >> 1;
    if(x <= mid)  zuo[now] = insert(zuo[pre], x, L, mid);
    else          you[now] = insert(you[pre], x, mid+1, R);
    return now;
}

// 查询当前结点 cur 覆盖区间 [L..R] 与询问区间 [ql..qr] 的交的计数
int query(int cur, int L, int R, int ql, int qr){
    if(!cur || ql > R || qr < L) return 0;
    if(ql <= L && R <= qr) return sz[cur];
    int mid = (L + R) >> 1;
    int res = 0;
    if(ql <= mid) res += query(zuo[cur], L, mid, ql, qr);
    if(qr >  mid) res += query(you[cur], mid+1, R, ql, qr);
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 建前缀可持久化线段树：root[i] 表示 a[1..i] 的计数分布
    root[0] = 0;
    for(int i = 1; i <= n; i++){
        int a; cin >> a;                  // a 可能为 0
        root[i] = insert(root[i-1], a, 0, VALMAX);
    }

    while(m--){
        int b, add, l, r;                 // 题意：b, x, l, r
        cin >> b >> add >> l >> r;

        int res = 0;
        // 最高需要到 bit=17（因为 a+x < 2e5 < 2^18）
        for(int k = 17; k >= 0; k--){
            // 把 “s 的高位前缀= res 的高位前缀 且 第 k 位为 1” 映射到 t = a + x 的区间
            int top   = (((res >> (k+1)) ^ (b >> (k+1))) << (k+1));
            int needK = 1 ^ ((b >> k) & 1);
            int lowT  = top | (needK << k);
            int highT = lowT + ((1 << k) - 1);

            // 映射回 a 的区间：a ∈ [lowT - add, highT - add]
            int ql = lowT  - add;
            int qr = highT - add;

            // 和值域 [0..VALMAX] 取交
            if(qr < 0 || ql > VALMAX){
                // 空区间，啥也不做
            }else{
                ql = max(ql, 0);
                qr = min(qr, VALMAX);
                int cntIn = query(root[r], 0, VALMAX, ql, qr)
                          - query(root[l-1], 0, VALMAX, ql, qr);
                if(cntIn > 0) res |= (1 << k);
            }
        }
        // res 就是 max (b ^ (a + add)) 的值
        cout << res << '\n';
    }
    return 0;
}
