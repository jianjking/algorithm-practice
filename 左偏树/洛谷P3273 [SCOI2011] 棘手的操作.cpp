#include <bits/stdc++.h>
using namespace std;

const int mx = 300000 + 5;

int zuo[mx], you[mx], up[mx];     // 左儿子、右儿子、堆父亲（只用于堆）
int father[mx], sz[mx];           // 并查集父亲、并查集大小
int rt[mx];                       // 每个并查集代表元对应堆的根
int dist[mx];                     // 左偏堆的 NPL（空儿子 dist = -1）
long long nums[mx];               // 节点“基值”（只含 A1 的改动 & 合并时注入的 tag）
long long tag[mx];                // 堆的子树 lazy（仅用于左偏堆）
long long addv[mx];               // 连通块增量（A2）
long long sumv = 0;               // 全局增量（A3）

multiset<long long> headMax;      // 维护所有连通块的“块内最大值”（不含 sumv）

int Find(int x){ return father[x]==x ? x : father[x]=Find(father[x]); }

inline void push(int x){
    if(!x || tag[x]==0) return;
    if(zuo[x]) tag[zuo[x]] += tag[x];
    if(you[x]) tag[you[x]] += tag[x];
    nums[x] += tag[x];
    tag[x] = 0;
}

int mergeHeap(int a, int b){
    if(!a) return b;
    if(!b) return a;
    push(a); push(b);
    if(nums[a] < nums[b]) swap(a, b);         // 大根堆
    you[a] = mergeHeap(you[a], b);
    if(you[a]) up[you[a]] = a;
    if(dist[zuo[a]] < dist[you[a]]) swap(zuo[a], you[a]);
    dist[a] = dist[you[a]] + 1;
    return a;
}

// 从 x 一直向上把懒标记下推，保证 x 处数值最新
void pushPathToRoot(int x){
    static int stk[mx];
    int top = 0, u = x;
    while(u){ stk[top++] = u; u = up[u]; }
    while(top) push(stk[--top]);
}

// 从堆中删除“任意节点 x”，并返回新堆根
int eraseNode(int x){
    pushPathToRoot(x);                 // 确保 x、其父链信息新鲜
    int L = zuo[x], R = you[x];
    if(L) up[L] = 0;
    if(R) up[R] = 0;
    int s = mergeHeap(L, R);           // 先把 x 的两个子树合起来
    int p = up[x];
    // 断开 x 与父亲
    zuo[x] = you[x] = 0; dist[x] = 0; up[x] = 0;

    int cur = x;
    while(p){
        int g = up[p];
        push(p);
        if(zuo[p] == cur) zuo[p] = 0;
        else if(you[p] == cur) you[p] = 0;
        up[p] = 0;
        s = mergeHeap(s, p);           // 把剩余部分与父结点重新 meld
        cur = p;
        p = g;
    }
    if(s) up[s] = 0;
    return s;                          // 新堆根
}

// 当前连通块 rep 的堆根“有效值”（不含全局 sumv）
inline long long peekRootVal(int rep){
    int h = rt[rep];
    if(!h) return (long long)LLONG_MIN/4;
    return nums[h] + tag[h] + addv[rep];
}

inline void eraseHead(int rep){
    if(rt[rep]){
        auto it = headMax.find(peekRootVal(rep));
        if(it != headMax.end()) headMax.erase(it);
    }
}
inline void insertHead(int rep){
    if(rt[rep]) headMax.insert(peekRootVal(rep));
}

void unite(int x, int y){
    int rx = Find(x), ry = Find(y);
    if(rx == ry) return;
    if(sz[rx] < sz[ry]) swap(rx, ry);               // rx 吸收 ry

    eraseHead(rx);
    eraseHead(ry);

    long long delta = addv[ry] - addv[rx];          // 统一块增量：把差值打到 ry 堆根的 tag 上
    if(rt[ry]) tag[rt[ry]] += delta;

    rt[rx] = mergeHeap(rt[rx], rt[ry]);
    if(rt[rx]) up[rt[rx]] = 0;

    father[ry] = rx;
    sz[rx] += sz[ry];
    rt[ry] = 0; // 清理被吸收方

    insertHead(rx);
}

inline long long valueOfNode(int x){                 // F1
    long long acc = 0;
    int u = x;
    while(u){ acc += tag[u]; u = up[u]; }           // 累加路径上所有 lazy
    int r = Find(x);
    return nums[x] + acc + addv[r] + sumv;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    if(!(cin >> n)) return 0;

    for(int i=1;i<=n;i++){
        long long a; cin >> a;
        nums[i] = a;
    }

    // 初始化
    dist[0] = -1;
    for(int i=1;i<=n;i++){
        zuo[i]=you[i]=up[i]=0;
        dist[i]=0; tag[i]=0;
        father[i]=i; sz[i]=1;
        addv[i]=0; rt[i]=i;
    }
    sumv = 0;
    headMax.clear();
    for(int i=1;i<=n;i++) insertHead(i);

    int Q; cin >> Q;
    while(Q--){
        string s; cin >> s;
        if(s=="U"){
            int x,y; cin >> x >> y;
            unite(x,y);
        }else if(s=="A1"){
            int x; long long v; cin >> x >> v;
            int r = Find(x);
            eraseHead(r);
            rt[r] = eraseNode(x);                   // 脱堆
            // x 已经把路径 lazy 吃干净了（在 eraseNode 里 pushPathToRoot 过）
            nums[x] += v;
            // 重置 x 再插回
            zuo[x]=you[x]=0; dist[x]=0; up[x]=0; tag[x]=0;
            rt[r] = mergeHeap(rt[r], x);
            if(rt[r]) up[rt[r]] = 0;
            insertHead(r);
        }else if(s=="A2"){
            int x; long long v; cin >> x >> v;
            int r = Find(x);
            eraseHead(r);
            addv[r] += v;
            insertHead(r);
        }else if(s=="A3"){
            long long v; cin >> v;
            sumv += v;
        }else if(s=="F1"){
            int x; cin >> x;
            cout << valueOfNode(x) << '\n';
        }else if(s=="F2"){
            int x; cin >> x;
            int r = Find(x);
            long long ans = peekRootVal(r) + sumv;
            cout << ans << '\n';
        }else if(s=="F3"){
            long long ans = *headMax.rbegin() + sumv;   // 取全局最大
            cout << ans << '\n';
        }
    }
    return 0;
}
