#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

// 头结点下标、已用节点数
int head = 0, cnt = 0;

// 节点信息
int keyv[MAXN];     // key
int lch[MAXN];      // 左儿子
int rch[MAXN];      // 右儿子
int siz[MAXN];      // 子树大小

inline void up(int i){
    siz[i] = siz[lch[i]] + siz[rch[i]] + 1;
}

// split: 按 num 分裂 i 子树，<=num 的放到 rch[0]，>num 的放到 lch[0]
// 维持“0 号哨兵位”风格，等价于你的 Java 写法
void split(int l, int r, int i, int num){
    if(i == 0){
        rch[l] = 0;
        lch[r] = 0;
    }else{
        if(keyv[i] <= num){
            rch[l] = i;
            split(i, r, rch[i], num);
        }else{
            lch[r] = i;
            split(l, i, lch[i], num);
        }
        up(i);
    }
}

// merge: 不用优先级；谁 val 大谁当根
// 前置条件：左树所有值 <= 右树所有值（由 split 保证）
int merge(int L, int R){
    if(L == 0 || R == 0) return L + R;
    // 因为 max(L) <= min(R)，通常 keyv[R] >= keyv[L]
    // 按你要求：谁的根 val 大谁当根
    if(keyv[L] >= keyv[R]){
        rch[L] = merge(rch[L], R);
        up(L);
        return L;
    }else{
        lch[R] = merge(L, lch[R]);
        up(R);
        return R;
    }
}

// 加入一个 x（不做词频压缩：重复会新开节点）
void add(int x){
    split(0, 0, head, x);
    keyv[++cnt] = x;
    lch[cnt] = rch[cnt] = 0;
    siz[cnt] = 1;
    head = merge(merge(rch[0], cnt), lch[0]);
}

// 删除一个 x（若有多个只删一个）
void remove_one(int x){
    split(0, 0, head, x);          // <=x -> rch[0], >x -> lch[0]
    int lm = rch[0], r = lch[0];
    split(0, 0, lm, x - 1);        // <=x-1 -> rch[0], ==x -> lch[0]
    int l = rch[0], m = lch[0];    // m 的根就是一个 x
    // 删除 m 的根节点（不回收编号），把它的左右并回去
    head = merge(merge(l, merge(lch[m], rch[m])), r);
}

// rank(x) = 比 x 小的数的个数 + 1
int get_rank(int x){
    split(0, 0, head, x - 1);
    int ans = siz[rch[0]] + 1;
    head = merge(rch[0], lch[0]);
    return ans;
}

// 第 k 小（1-based）
int kth(int i, int k){
    if(siz[lch[i]] >= k) return kth(lch[i], k);
    else if(siz[lch[i]] + 1 < k) return kth(rch[i], k - siz[lch[i]] - 1);
    else return keyv[i];
}
int kth(int k){ return kth(head, k); }

// 前驱：< x 的最大值，不存在返回 INT_MIN
int predecessor(int i, int x){
    if(i == 0) return INT_MIN;
    if(keyv[i] >= x) return predecessor(lch[i], x);
    return max(keyv[i], predecessor(rch[i], x));
}
int predecessor(int x){ return predecessor(head, x); }

// 后继：> x 的最小值，不存在返回 INT_MAX
int successor(int i, int x){
    if(i == 0) return INT_MAX;
    if(keyv[i] <= x) return successor(rch[i], x);
    return min(keyv[i], successor(lch[i], x));
}
int successor(int x){ return successor(head, x); }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q; 
    if(!(cin >> Q)) return 0;
    // 全局数组是静态区，默认 0；显式清空以防多组测评（可选）
    // memset(lch,0,sizeof lch); memset(rch,0,sizeof rch);
    // memset(siz,0,sizeof siz); memset(keyv,0,sizeof keyv);
    head = 0; cnt = 0;

    while(Q--){
        int op, x; 
        cin >> op >> x;
        if(op == 1) add(x);
        else if(op == 2) remove_one(x);
        else if(op == 3) cout << get_rank(x) << '\n';
        else if(op == 4) cout << kth(x) << '\n';
        else if(op == 5) cout << predecessor(x) << '\n';
        else /* op == 6 */ cout << successor(x) << '\n';
    }
    return 0;
}
