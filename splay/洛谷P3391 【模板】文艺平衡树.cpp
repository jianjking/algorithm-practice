#include <bits/stdc++.h>
using namespace std;

// P3391 文艺平衡树 - Splay (数组版) - 区间翻转
// 约束：1 <= n, m <= 1e5

const int MX = 200000 + 50; // 至少要 >= n + 2，取安全余量
int val[MX], zuo[MX], you[MX], sz[MX], father[MX];
bool vis[MX];               // 翻转懒标记
int cnt = 0, head = 0;

// --- 基本维护 ---
inline void up(int x){
    sz[x] = (x ? (sz[zuo[x]] + sz[you[x]] + 1) : 0);
}
inline void down(int x){
    if(!x || !vis[x]) return;
    vis[zuo[x]] ^= 1;
    vis[you[x]] ^= 1;
    swap(zuo[x], you[x]);
    vis[x] = 0;
}
inline int lr(int x){ // x 是否是其父的右儿子
    return you[father[x]] == x;
}
int newnode(int v, int fa){
    ++cnt;
    val[cnt] = v;
    zuo[cnt] = you[cnt] = 0;
    sz[cnt] = 1;
    father[cnt] = fa;
    vis[cnt] = 0;
    return cnt;
}

// --- 用有序数组 0..n+1 一次性建“完全平衡”BST（递归深度 ~ logn，安全）---
int build(int L, int R, int fa){
    if(L > R) return 0;
    int M = (L + R) >> 1;
    int id = newnode(M, fa);
    zuo[id] = build(L, M - 1, id);
    you[id] = build(M + 1, R, id);
    up(id);
    return id;
}

// --- 旋转 & splay ---
void rotate(int x){
    int y = father[x];
    int z = father[y];
    down(y); down(x); // 局部保证干净（也可以放在 splay 循环里）
    int isRight = (you[y] == x); // x 是 y 的右儿子？
    int B = isRight ? zuo[x] : you[x];

    // y <-> B
    if(isRight){
        you[y] = B; if(B) father[B] = y;
        zuo[x] = y; father[y] = x;
    }else{
        zuo[y] = B; if(B) father[B] = y;
        you[x] = y; father[y] = x;
    }
    father[x] = z;
    if(z){
        if(you[z] == y) you[z] = x;
        else            zuo[z] = x;
    }else{
        head = x;
    }
    up(y); up(x);
}

void splay(int x, int target){
    // 先把根->x 的路径全部下放干净，防止“假左右”导致错误旋
    static int stk[MX]; int top = 0, t = x;
    while(t){ stk[++top] = t; t = father[t]; }
    while(top) down(stk[top--]);

    while(father[x] != target){
        int y = father[x];
        int z = father[y];
        if(z != target){
            // zig-zig or zig-zag
            if( (you[z]==y) == (you[y]==x) ) rotate(y);
            else rotate(x);
        }
        rotate(x);
    }
    if(target == 0) head = x;
}

// --- 第 k 小（1-based，含哨兵）---
int kth(int k){
    int cur = head;
    while(cur){
        down(cur);
        int ls = sz[zuo[cur]];
        if(k == ls + 1) return cur;
        if(k <= ls) cur = zuo[cur];
        else { k -= ls + 1; cur = you[cur]; }
    }
    return 0; // 理论上不会发生
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; 
    if(!(cin >> n >> m)) return 0;

    // 建 0..n+1 两个哨兵 + 正常序列（值即为位置）
    cnt = 0; head = build(0, n+1, 0);

    while(m--){
        int l, r; cin >> l >> r;
        // 标准套路：把第 l 个节点旋到根；把第 r+2 个节点旋到根的右儿子；
        // 需要翻转的区间就是 you[head] 的左儿子
        int L = kth(l);
        splay(L, 0);
        int R = kth(r + 2);
        splay(R, head);
        int seg = zuo[you[head]];
        if(seg) vis[seg] ^= 1;
    }

    // 迭代中序 + 缓冲输出（只输出 1..n；一行、空格分隔）
    vector<int> out; out.reserve(n);
    vector<int> st; st.reserve(64);
    int cur = head;
    while(cur || !st.empty()){
        while(cur){
            down(cur);
            st.push_back(cur);
            cur = zuo[cur];
        }
        int x = st.back(); st.pop_back();
        if(val[x] >= 1 && val[x] <= n) out.push_back(val[x]);
        down(x);
        cur = you[x];
    }

    for(int i=0;i<n;i++){
        if(i) cout << ' ';
        cout << out[i];
    }
    cout << '\n';
    return 0;
}

