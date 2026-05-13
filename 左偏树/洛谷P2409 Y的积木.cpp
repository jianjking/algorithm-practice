#include<bits/stdc++.h>
using namespace std;

const int mx = 1000000;          // 左偏树最大节点数
const int INF = 10000001;

int zuo[mx], you[mx], topv[mx];  // top -> 改名本地变量时避免与std::top冲突，这里数组仍叫 topv
int pre[mx], idx[mx], jdx[mx], distv[mx], cost[mx];
int cnt;

// —— 持久化左偏树：新建一个动作节点 ——
// 语义：在数组 i 的位置 j 上，准备把 j -> j+1（若 j+1 不存在则 cost=INF）
int init_node(int i, int j, const vector<vector<int>>& nums) {
    ++cnt;
    idx[cnt] = i;
    jdx[cnt] = j;  // **修正**：你的草稿填的是 j+1，这里应记录“当前位置 j”
    if (j + 1 < (int)nums[i].size()) cost[cnt] = nums[i][j + 1] - nums[i][j];
    else cost[cnt] = INF;
    zuo[cnt] = you[cnt] = 0;
    distv[cnt] = 0;
    topv[cnt] = cnt;
    return cnt;
}

// —— 持久化克隆 —— 
int copy(int x) {
    if (x == 0) return 0;
    ++cnt;
    idx[cnt]   = idx[x];
    jdx[cnt]   = jdx[x];
    cost[cnt]  = cost[x];
    zuo[cnt]   = zuo[x];
    you[cnt]   = you[x];
    distv[cnt] = distv[x];
    topv[cnt]  = topv[x];
    return cnt;
}

// —— 左偏树合并（小根堆，按 cost 升序，持久化） ——
int merge_heap(int a, int b) {
    if (a == 0 || b == 0) return a + b;
    if (cost[a] > cost[b] || (cost[a] == cost[b] && a > b)) swap(a, b);
    int h = copy(a);
    you[h] = merge_heap(you[h], b);
    if (distv[zuo[h]] < distv[you[h]]) swap(zuo[h], you[h]);
    distv[h] = distv[you[h]] + 1;
    return h;
}

// —— 弹出堆顶：返回删除根后的新树头（持久化） ——
int pop_head(int h) {
    if (h == 0) return 0;
    if (zuo[h] == 0 && you[h] == 0) return 0;
    if (zuo[h] == 0 || you[h] == 0) return copy(zuo[h] + you[h]);
    return merge_heap(zuo[h], you[h]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<vector<int>> nums(n);
    cnt = 0;
    distv[0] = -1;

    // 读入 + 排序 + 计算第一组最小和
    int first_sum = 0;
    for (int i = 0; i < n; ++i) {
        int m; cin >> m;
        nums[i].resize(m);
        for (int j = 0; j < m; ++j) cin >> nums[i][j];   // **修正**：不要 push_back
        sort(nums[i].begin(), nums[i].end());            // **修正**：排每个数组
        first_sum += nums[i][0];
    }

    // 初始左偏树头：把每个数组在 j=0 的“前进一步”动作放进去
    int head = 0;
    for (int i = 0; i < n; ++i) {
        head = merge_heap(head, init_node(i, 0, nums));
    }
    pre[head] = first_sum;

    // 第一个答案就是各数组最小值之和
    vector<int> ans(k + 1, 0);
    ans[1] = first_sum;

    // 用最小堆在不同“版本头”之间择最优（键 = pre[h] + cost[h]）
    struct Item {
        int h;
        long long key;
        bool operator<(const Item& o) const { return key > o.key; } // 小根
    };
    priority_queue<Item> pq;
    if (head) pq.push({head, (long long)pre[head] + cost[head]});

    // 生成第 2..k 小
    for (int rank = 2; rank <= k; ++rank) {
        if (pq.empty()) {            // 理论上不会空；防御下
            ans[rank] = ans[rank - 1];
            continue;
        }
        int cur = pq.top().h;
        pq.pop();

        ans[rank] = pre[cur] + cost[cur];

        // ① 不推进当前数组：弹出根节点，继承同一个 pre
        int h1 = pop_head(cur);
        if (h1) {
            pre[h1] = pre[cur];
            pq.push({h1, (long long)pre[h1] + cost[h1]});
        }

        // ② 推进当前数组 idx[cur] 的位置 j -> j+1 后，再把“下一步”动作（从 j+1 往 j+2）放回去
        int i = idx[cur], j = jdx[cur];
        if (j + 1 < (int)nums[i].size()) {                          // j+1 存在即可；其 cost 若无 j+2 会是 INF
            int h2 = merge_heap(h1, init_node(i, j + 1, nums));     // 新版本的 pre 是最新的总和
            pre[h2] = ans[rank];
            pq.push({h2, (long long)pre[h2] + cost[h2]});
        }
    }

    for (int i = 1; i <= k; ++i) {
        cout << ans[i] << (i == k ? '\n' : ' ');
    }
    return 0;
}
