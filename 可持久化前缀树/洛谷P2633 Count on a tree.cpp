#include<bits/stdc++.h>
using namespace std;

const int mx=5*1000000;
int zuo[mx], you[mx], head[mx], sz[mx], deep[mx];
int cnt, h;
int nums[mx];                     // 点权（按点编号 1..n）
unordered_map<int,int> zheng;     // 值 -> rank (1..s)
unordered_map<int,int> fan;       // rank -> 值
vector<vector<int>> graph;
vector<vector<int>> st;

inline void up(int num){
    sz[num] = sz[zuo[num]] + sz[you[num]];
}

int build(int l,int r){
    int num = ++cnt;
    if(l==r){
        // FIX: 叶子明确置 0（虽然全局区默认 0）
        sz[num] = 0;
        return num;
    }
    int mid = l + (r-l)/2;
    zuo[num] = build(l,mid);
    you[num] = build(mid+1,r);
    up(num);
    return num;
}

int insert(int l,int r,int target,int cur){
    int num = ++cnt;
    zuo[num] = zuo[cur];
    you[num] = you[cur];
    if(l==r){
        // FIX: 叶子 +1
        sz[num] = sz[cur] + 1;
        return num;
    }
    int mid = l + (r-l)/2;
    if(target<=mid){
        zuo[num] = insert(l,mid,target,zuo[cur]);
    }else{
        you[num] = insert(mid+1,r,target,you[cur]);
    }
    up(num);
    return num;
}

void dfs(int u,int f){
    st[u][0] = f;
    deep[u] = deep[f] + 1;
    for(int i=1;i<(int)st[0].size();i++){
        st[u][i] = st[ st[u][i-1] ][i-1];
    }
    // 每个点以父亲版本为基，插入自己的 rank
    head[u] = insert(1,(int)zheng.size(), zheng[nums[u]], head[f]);
    for(int v: graph[u]){
        if(v!=f) dfs(v,u);
    }
}

// 返回 rank（不是原值！）
int query(int l,int r,int hu,int hv,int hlca,int hplca,int k){
    if(l==r){
        // 这里按不变式：能走到叶子必有 k<=count，直接返回 rank
        return l; // FIX
    }
    int mid = l + (r-l)/2;
    int cntLeft = sz[zuo[hu]] + sz[zuo[hv]] - sz[zuo[hlca]] - sz[zuo[hplca]];
    if(cntLeft >= k){
        return query(l,mid,zuo[hu],zuo[hv],zuo[hlca],zuo[hplca],k);
    }else{
        return query(mid+1,r,you[hu],you[hv],you[hlca],you[hplca],k-cntLeft);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m; 
    cin >> n >> m;

    cnt = 0; h = 0;
    graph.assign(n+1, {});
    
    // 读点权
    vector<int> all; 
    all.reserve(n);
    for(int i=1;i<=n;i++){
        cin >> nums[i];
        all.push_back(nums[i]);
    }

    // FIX: 正经离散化：值->连续rank，rank->值
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    for(int i=0;i<(int)all.size();i++){
        zheng[all[i]] = i+1;    // rank 从 1 开始
        fan[i+1] = all[i];
    }
    int s = (int)all.size();

    // 建空树根 head[0]
    head[0] = build(1, s);

    // 读边
    for(int i=1;i<=n-1;i++){
        int a,b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // 预处理 ST 维度
    int tmp=1, cn=0;
    while(tmp<=n){ cn++; tmp<<=1; }
    st.assign(n+1, vector<int>(cn+1, 0));

    // DFS 建每个点对应的版本
    dfs(1,0);

    int lastans = 0;
    while(m--){
        int u,v,k; 
        cin >> u >> v >> k;
        u ^= lastans;           // 题意：仅 u 异或

        // LCA（倍增）
        if(deep[u]<deep[v]) swap(u,v);
        int u0=u, v0=v;
        int diff = deep[u] - deep[v];
        for(int j=0;j<(int)st[0].size();j++) if((diff>>j)&1) u = st[u][j];
        if(u!=v){
            for(int j=(int)st[0].size()-1;j>=0;j--){
                if(st[u][j] != st[v][j]){
                    u = st[u][j];
                    v = st[v][j];
                }
            }
            u = st[u][0]; // now u is lca
        }
        int lca = u;
        int plca = st[lca][0]; // 可能为 0，head[0] 有效

        int rankK = query(1, s, head[u0], head[v0], head[lca], head[plca], k);
        lastans = fan[rankK];   // rank -> 原值
        cout << lastans << '\n';
    }
    return 0;
}
