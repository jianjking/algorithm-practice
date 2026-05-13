#include <bits/stdc++.h>
using namespace std;

const int MX = 100000 + 5;

// 静态数组
int zuo[MX], you[MX], sz[MX], val[MX], priorv[MX];
int cnt = 0;         // 已用节点个数（下标从 1 起）
int head = 0;        // 根下标

// xorshift32：简单够用
static uint32_t seed_ = 0x9e3779b9u;
inline uint32_t rnd() {
    seed_ ^= seed_ << 13;  seed_ ^= seed_ >> 17;  seed_ ^= seed_ << 5;
    return seed_;
}

inline void up(int i){
    if(!i) return;
    sz[i] = sz[zuo[i]] + sz[you[i]] + 1;   // ⚠️ 别忘了 +1
}

// FHQ split：把以 cur 为根的树按 nums 分裂
// <= nums 的放到 you[l]，> nums 的放到 zuo[r]（0 号作哨兵）
void split(int l, int r, int cur, int nums){
    if(cur == 0){
        you[l] = 0;
        zuo[r] = 0;
    }else{
        if(val[cur] <= nums){
            you[l] = cur;
            split(cur, r, you[cur], nums);
        }else{
            zuo[r] = cur;
            split(l, cur, zuo[cur], nums);
        }
        up(cur); // ✅ 回溯更新的是“当前节点”，不是 l/r
    }
}

// FHQ merge：按随机优先级（小堆/大堆都行，保持一致即可）
int mergeTreap(int L, int R){
    if(L == 0 || R == 0) return L + R;
    if(priorv[L] <= priorv[R]){ // 小的优先
        you[L] = mergeTreap(you[L], R);
        up(L);
        return L;
    }else{
        zuo[R] = mergeTreap(L, zuo[R]);
        up(R);
        return R;
    }
}

// 插入一个 nums（不做词频压缩：重复值新开节点）
void add(int &head, int nums){
    split(0, 0, head, nums);     // <=nums 到 you[0]，>nums 到 zuo[0]
    val[++cnt] = nums;
    priorv[cnt] = (int)rnd();
    zuo[cnt] = you[cnt] = 0;
    sz[cnt] = 1;
    head = mergeTreap(mergeTreap(you[0], cnt), zuo[0]);
}

// 删除一个 nums（若有多个只删一个）
void remove_one(int &head, int nums){
    split(0, 0, head, nums);       // you[0] : <=nums,  zuo[0] : >nums
    int lm = you[0], r = zuo[0];
    split(0, 0, lm, nums - 1);     // you[0] : <=nums-1,  zuo[0] : ==nums
    int l = you[0], m = zuo[0];    // m 可能是空；否则 m 的根是一个等于 nums 的节点
    // 删一个：把 m 的根去掉，只把它的左右合回去
    int m2 = mergeTreap(zuo[m], you[m]);  // m 的左右子树
    head = mergeTreap(mergeTreap(l, m2), r);
}

// rank(x) = 比 x 小的数字个数 + 1
int get_rank(int &head, int x){
    split(0, 0, head, x - 1);
    int ans = sz[you[0]] + 1;
    head = mergeTreap(you[0], zuo[0]);
    return ans;
}

// 第 k 小（1-based），保证 1 <= k <= sz[head]
int kth(int cur, int k){
    while(cur){
        int ls = sz[zuo[cur]];
        if(k <= ls) cur = zuo[cur];
        else if(k == ls + 1) return val[cur];
        else { k -= ls + 1; cur = you[cur]; }
    }
    return INT_MIN; // 不应到达
}

// 前驱：严格小于 x 的最大值；不存在返回 INT_MIN
int predecessor(int cur, int x){
    int ans = INT_MIN;
    while(cur){
        if(val[cur] < x){ ans = val[cur]; cur = you[cur]; }
        else cur = zuo[cur];
    }
    return ans;
}

// 后继：严格大于 x 的最小值；不存在返回 INT_MAX
int successor(int cur, int x){
    int ans = INT_MAX;
    while(cur){
        if(val[cur] > x){ ans = val[cur]; cur = zuo[cur]; }
        else cur = you[cur];
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q; 
    if(!(cin >> Q)) return 0;

    // 若多组测评，记得清空全局（本题单组即可）
    head = 0; cnt = 0;
    // 可选：memset(zuo,0,sizeof zuo); memset(you,0,sizeof you);
    // 可选：memset(sz,0,sizeof sz); memset(val,0,sizeof val); memset(priorv,0,sizeof priorv);

    while(Q--){
        int op, x; 
        cin >> op >> x;
        if(op == 1){
            add(head, x);
        }else if(op == 2){
            remove_one(head, x);
        }else if(op == 3){
            cout << get_rank(head, x) << '\n';
        }else if(op == 4){
            // kth 查询默认保证合法
            cout << kth(head, x) << '\n';
        }else if(op == 5){
            cout << predecessor(head, x) << '\n';
        }else{ // op == 6
            cout << successor(head, x) << '\n';
        }
    }
    return 0;
}
