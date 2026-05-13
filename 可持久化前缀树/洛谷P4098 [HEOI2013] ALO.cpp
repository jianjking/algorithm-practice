#include <bits/stdc++.h>
using namespace std;

// 按题面上限来就够：n <= 5e4
const int mxn = 5e4 + 5;
const int bit = 30;
// 每次插入新值会新建 1（新根） + (bit+1) 个节点，预留 (bit+2)*n 即可
const int mxt = (bit + 2) * mxn;

int tree[mxt][2];
int pass[mxt];          // 通过计数
int root[mxn];          // 各前缀版本根
int pre[mxn], last[mxn];

int cnt;                // 已用节点数
int h;                  // 保留你的变量名（未使用）
vector<pair<int,int>> nums;

// 正确的持久化插入：只在“新链”上改指针，不动旧节点
int insert(int prev, int val){
    int num = ++cnt;                              // 新根
    tree[num][0] = tree[prev][0];
    tree[num][1] = tree[prev][1];
    pass[num]     = pass[prev] + 1;

    int p = num;
    for(int i = bit; i >= 0; --i){
        int b   = (val >> i) & 1;
        int old = tree[p][b];                     // 旧儿子（来自 prev 的对应位置）
        int cur = ++cnt;                          // 新儿子
        tree[p][b] = cur;                         // 只在新链节点 p 上改指针

        // 拷贝旧儿子的结构并 +1 通过计数
        tree[cur][0] = tree[old][0];
        tree[cur][1] = tree[old][1];
        pass[cur]    = pass[old] + 1;

        p = cur;                                  // 继续往下
    }
    return num;
}

// 在区间 [l..r] 内求 val 的最大异或值：用前缀版本根 ur=root[r], vr=root[l-1]
int query(int ur, int vr, int val){
    int u = ur, v = vr, res = 0;
    for(int i = bit; i >= 0; --i){
        int second = (val >> i) & 1;              // 想走的相反位
        int first  = second ^ 1;
        int uc = tree[u][first], vc = tree[v][first];
        if(pass[uc] - pass[vc] > 0){              // 这个分支里区间元素数量 > 0
            res |= (1 << i);
            u = uc; v = vc;
        }else{
            u = tree[u][second];
            v = tree[v][second];
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;

    // 双向“邻域”链 + 前缀根初始化
    pre[0] = 0;       last[0] = 1;
    pre[n+1] = n;     last[n+1] = n+1;
    cnt = 0; root[0] = 0; h = 0;

    nums.reserve(n);
    for(int i = 1; i <= n; ++i){
        int x; cin >> x;
        nums.push_back({x, i});
        pre[i] = i - 1;
        last[i] = i + 1;
        root[i] = insert(root[i - 1], x);        // 建前缀版本
    }

    // 从小到大处理“次大值候选”
    sort(nums.begin(), nums.end(), [&](pair<int,int>& a, pair<int,int>& b){
        return a.first < b.first;
    });

    int ans = 0;
    for(auto &kv : nums){
        int val = kv.first, idx = kv.second;
        int prev = pre[idx], pprev = pre[prev];
        int next = last[idx], nnext = last[next];

        // 左侧作为唯一最大：区间 [pprev+1 .. next-1]
        if(prev >= 1){
            ans = max(ans, query(root[next - 1], root[pprev], val)); // 传“根”，不是下标
        }
        // 右侧作为唯一最大：区间 [prev+1 .. nnext-1]
        if(next <= n){
            ans = max(ans, query(root[nnext - 1], root[prev], val)); // 同上
        }

        // 从“活跃集合”里删除 idx
        last[prev] = next;
        pre[next]  = prev;
    }

    cout << ans << '\n';
    return 0;
}
