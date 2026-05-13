#include <bits/stdc++.h>
using namespace std;

// 题目上限：n<=1000, m<=3e5, 值<2^31
// 节点数 ~ m * 31，留点余量
const int MAXM   = 300000 + 5;
const int MAXN   = 1000 + 5;
const int BIT    = 30;                 // 最高到第30位(含)，共31位
const int MAXT   = (MAXM * (BIT + 2)) + 5; // 充足余量

int tree[MAXT][2];
int pass_[MAXT];                       // 为避免与你原来的 pass 宏重名风险，改叫 pass_
int root[MAXM];
int arr[MAXN];
int xroad[MAXN][2];                    // [row][0]=root[l-1]侧的指针；[row][1]=root[r]侧的指针
int cnt;

int insert_(int prev, int val){
    int now = ++cnt;
    // 头结点复制
    tree[now][0] = tree[prev][0];
    tree[now][1] = tree[prev][1];
    pass_[now]   = pass_[prev] + 1;
    int cur = now;
    for(int b = BIT; b >= 0; --b){
        int bitv = (val >> b) & 1;
        int prev_child = tree[prev][bitv];       // 旧版本在该位的子
        int nxt = ++cnt;
        // 复制旧子到新子
        tree[nxt][0] = tree[prev_child][0];
        tree[nxt][1] = tree[prev_child][1];
        pass_[nxt]   = pass_[prev_child] + 1;

        tree[cur][bitv] = nxt;                   // 挂新子
        cur  = nxt;
        prev = prev_child;                       // 继续沿旧版本对应分支下探
    }
    return now;
}

int query(int x1, int x2, int y1, int y2, int kth){
    // 初始化每一行在两个版本上的位置
    for(int i = x1; i <= x2; ++i){
        xroad[i][0] = root[y1 - 1];
        xroad[i][1] = root[y2];
    }
    int ans = 0;
    for(int b = BIT; b >= 0; --b){
        long long sum = 0; // 可能到 1e3 * 3e5 量级，用 long long 更稳
        // 先统计如果这一位取 1，一共能取到多少个元素（跨所有行）
        for(int row = x1; row <= x2; ++row){
            int xb   = (arr[row] >> b) & 1;
            int want = xb ^ 1; // 为了 XOR 的这一位为1，需要 y 的该位 != xb
            int rnode = tree[xroad[row][1]][want];
            int lnode = tree[xroad[row][0]][want];
            sum += (pass_[rnode] - pass_[lnode]);
        }

        if(sum >= kth){
            // 这一位取 1
            ans |= (1 << b);
            for(int row = x1; row <= x2; ++row){
                int xb   = (arr[row] >> b) & 1;
                int want = xb ^ 1;
                xroad[row][1] = tree[xroad[row][1]][want];
                xroad[row][0] = tree[xroad[row][0]][want];
            }
        }else{
            // 这一位只能取 0
            kth -= sum;
            for(int row = x1; row <= x2; ++row){
                int xb   = (arr[row] >> b) & 1;
                int same = xb; // 为了 XOR 的这一位为0，需要 y 的该位 == xb
                xroad[row][1] = tree[xroad[row][1]][same];
                xroad[row][0] = tree[xroad[row][0]][same];
            }
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if(!(cin >> n >> m)) return 0;

    for(int i = 1; i <= n; ++i) cin >> arr[i];
    // 构建 Y 的持久化 01-Trie 前缀
    root[0] = 0; // 空版本
    for(int i = 1; i <= m; ++i){
        int y; cin >> y;
        root[i] = insert_(root[i-1], y);
    }

    int q; cin >> q;
    while(q--){
        int u, d, l, r, k;
        cin >> u >> d >> l >> r >> k;
        cout << query(u, d, l, r, k) << '\n';
    }
    return 0;
}
