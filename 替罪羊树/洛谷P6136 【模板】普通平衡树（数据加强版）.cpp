#include <bits/stdc++.h>
using namespace std;

// ——容量加大到足够支撑 n+m 级别的不同插入——
const int MX = 2200000; // 可按评测机内存再调
int cnt;
int ci[MX];
int zuo[MX];
int you[MX];
int diffv[MX]; // 原 diff 改名，避免潜在冲突
int sz[MX];
int head;
int val[MX];
int father;
int topv;
int si;
const double xi = 0.7;

inline void build(){
    memset(ci, 0, sizeof(ci));
    memset(zuo, 0, sizeof(zuo));
    memset(you, 0, sizeof(you));
    memset(diffv, 0, sizeof(diffv));
    memset(sz, 0, sizeof(sz));
    memset(val, 0, sizeof(val));
    cnt = 0;
    head = 0;
}

inline void up(int i){
    diffv[i] = diffv[zuo[i]] + diffv[you[i]] + (ci[i] > 0 ? 1 : 0);
    sz[i]    = sz[zuo[i]]   + sz[you[i]]   + ci[i];
}

inline bool blance(int i){
    return max(diffv[zuo[i]], diffv[you[i]]) <= xi * diffv[i];
}

void dfs1(vector<int>& nums, int cur){
    if(cur == 0) return;
    dfs1(nums, zuo[cur]);
    if(ci[cur] != 0) nums.push_back(cur);
    dfs1(nums, you[cur]);
}

int dfs2(vector<int>& nums, int l, int r){
    if(l > r) return 0;
    int mid = l + (r - l) / 2;
    int x = nums[mid];
    zuo[x] = dfs2(nums, l, mid - 1);
    you[x] = dfs2(nums, mid + 1, r);
    up(x);
    return x;
}

int rebuild(int topp){
    vector<int> nums;
    nums.reserve(diffv[topp]);
    dfs1(nums, topp);
    return dfs2(nums, 0, (int)nums.size() - 1);
}

int add(int i, int x, int f, int sign){
    if(i == 0){
        ++cnt;
        zuo[cnt] = you[cnt] = 0;
        val[cnt] = x;
        ci[cnt]  = 1;
        sz[cnt]  = 1;
        diffv[cnt] = 1;
        return cnt;
    }else{
        if(val[i] == x){
            ++ci[i];
        }else if(val[i] < x){
            you[i] = add(you[i], x, i, 2);
        }else{
            zuo[i] = add(zuo[i], x, i, 1);
        }
    }
    up(i);
    if(!blance(i)){
        father = f;
        topv   = i;
        si     = sign; // 1 左，2 右，0 根
    }
    return i;
}

void remove_node(int cur, int x, int fa, int sign){
    if(cur == 0) return; // ★ 必须判空
    if(val[cur] == x){
        --ci[cur];
    }else if(val[cur] > x){
        remove_node(zuo[cur], x, cur, 1);
    }else{
        remove_node(you[cur], x, cur, 2);
    }
    up(cur);
    if(!blance(cur)){
        topv   = cur;
        father = fa;
        si     = sign;
    }
}

// < x 的个数
int mnnums(int cur, int x){
    if(cur == 0) return 0;
    if(val[cur] >= x){
        return mnnums(zuo[cur], x);
    }
    return sz[zuo[cur]] + ci[cur] + mnnums(you[cur], x);
}

// 第 k 小（k 从 1 开始）
int kth_index(int cur, int k){
    int left_sz = sz[zuo[cur]];
    if(k <= left_sz) return kth_index(zuo[cur], k);
    if(k > left_sz + ci[cur]) return kth_index(you[cur], k - left_sz - ci[cur]);
    return val[cur];
}

// 前驱：< x 最大
void xiaoda(int cur, int x, int& ans){
    if(cur == 0) return;
    if(val[cur] >= x){
        xiaoda(zuo[cur], x, ans);
    }else{
        ans = max(ans, val[cur]);
        xiaoda(you[cur], x, ans);
    }
}

// 后继：> x 最小
void daxiao(int cur, int x, int& ans){
    if(cur == 0) return;
    if(val[cur] <= x){
        daxiao(you[cur], x, ans);
    }else{
        ans = min(ans, val[cur]);
        daxiao(zuo[cur], x, ans);
    }
}

int main(){
    build();

    int n, m;
    if(scanf("%d %d", &n, &m) != 2) return 0;

    // 插入初始 n 个数
    for(int i = 0; i < n; ++i){
        int a; scanf("%d", &a);
        topv = father = si = 0;
        head = add(head, a, 0, 0);
        if(topv != 0){
            if(topv == head) head = rebuild(topv);
            else if(si == 1)  zuo[father] = rebuild(topv);
            else              you[father] = rebuild(topv);
        }
    }

    int last = 0; // 强制在线异或
    int sum  = 0; // 需要输出的异或和

    for(int i = 0; i < m; ++i){
        int op, xprime;
        scanf("%d %d", &op, &xprime);
        int x = xprime ^ last;

        if(op == 1){
            topv = father = si = 0;
            head = add(head, x, 0, 0);
            if(topv != 0){
                if(topv == head) head = rebuild(topv);
                else if(si == 1)  zuo[father] = rebuild(topv);
                else              you[father] = rebuild(topv);
            }
        }else if(op == 2){
            topv = father = si = 0;
            // ★ 注意参数顺序：root 在前，key 在后
            remove_node(head, x, 0, 0);
            if(topv != 0){
                if(topv == head) head = rebuild(topv);
                else if(si == 1)  zuo[father] = rebuild(topv);
                else              you[father] = rebuild(topv);
            }
        }else if(op == 3){
            int ans = mnnums(head, x) + 1;
            last = ans;
            sum ^= ans;
        }else if(op == 4){
            int ans = kth_index(head, x);
            last = ans;
            sum ^= ans;
        }else if(op == 5){
            int ans = INT_MIN;
            xiaoda(head, x, ans);
            last = ans;
            sum ^= ans;
        }else{ // op == 6
            int ans = INT_MAX;
            daxiao(head, x, ans);
            last = ans;
            sum ^= ans;
        }
    }

    printf("%d\n", sum);
    return 0;
}
