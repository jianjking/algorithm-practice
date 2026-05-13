#include <bits/stdc++.h>
using namespace std;

const int mx = 5 * 1000000;   // 节点池
int        zuo[mx], you[mx];
long long  sum[mx], addv[mx];
long long  nums[100000 + 5];  // 原数组每组重读
int        head[100000 + 5];  // 版本根（只需到 m 即可）
int        cnt, t;

inline void up(int i){
    sum[i] = sum[zuo[i]] + sum[you[i]];
}

int build(int l,int r){
    int num = ++cnt;
    addv[num] = 0;
    if(l == r){
        sum[num] = nums[l];
        return num;
    }
    int mid = (l + r) >> 1;
    zuo[num] = build(l, mid);
    you[num] = build(mid + 1, r);
    up(num);
    return num;
}

// 标记永久化的持久化区间加：整段覆盖只改本节点；部分覆盖递归后补回本节点标记贡献
int addtion(int x,int y,int l,int r,long long v,int cur){
    int num = ++cnt;                 // 克隆
    zuo[num] = zuo[cur];
    you[num] = you[cur];
    sum[num] = sum[cur];
    addv[num]= addv[cur];

    if(x <= l && y >= r){
        sum[num]  += (r - l + 1LL) * v;
        addv[num] += v;
        return num;
    }
    int mid = l + (r - l) / 2;
    if(x <= mid)  zuo[num] = addtion(x, y, l,     mid, v, zuo[num]);
    if(y >  mid)  you[num] = addtion(x, y, mid+1, r,   v, you[num]);

    // 补回本节点永久化标记对整段的贡献
    sum[num] = sum[zuo[num]] + sum[you[num]] + addv[num] * (r - l + 1LL);
    return num;
}

// 查询：携带祖先懒标 add；整段覆盖返回 sum[cur] + add*len
long long query(int x,int y,int l,int r,long long add,int cur){
    if(x <= l && y >= r){
        return sum[cur] + (r - l + 1LL) * add;
    }
    int mid = l + (r - l) / 2;
    long long nadd = add + addv[cur];
    long long ans = 0;
    if(x <= mid) ans += query(x, y, l,     mid, nadd, zuo[cur]);
    if(y >  mid) ans += query(x, y, mid+1, r,   nadd, you[cur]);
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    bool first = true; // 控制组间空行
    while ( (cin >> n >> m) ){
        if (!first) cout << '\n';
        first = false;

        for(int i = 1; i <= n; ++i) cin >> nums[i];

        cnt = 0;                 // 重置节点池
        head[0] = build(1, n);   // 版本0
        t = 0;                   // 当前时间戳

        for(int i = 0; i < m; ++i){
            char op; cin >> op;
            if(op == 'C'){
                int l, r; long long d; cin >> l >> r >> d;
                head[t + 1] = addtion(l, r, 1, n, d, head[t]);
                ++t;
            }else if(op == 'Q'){
                int l, r; cin >> l >> r;
                cout << query(l, r, 1, n, 0, head[t]) << '\n';
            }else if(op == 'H'){
                int l, r, tt; cin >> l >> r >> tt;
                cout << query(l, r, 1, n, 0, head[tt]) << '\n';
            }else{ // 'B'
                int x; cin >> x;
                t = x;
            }
        }
    }
    return 0;
}
