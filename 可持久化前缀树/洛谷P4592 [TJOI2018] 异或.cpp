#include<bits/stdc++.h>
using namespace std;

const int mxn=1e5+5;
const int mxt=60*mxn;   // 6e6，双trie内存略大但可过
const int bit=30;       // 值 < 2^30

int tree1[mxt][2], pass1[mxt];
int tree2[mxt][2], pass2[mxt];
int dfn[mxn], st[mxn][bit], depth[mxn], sz[mxn];
int cnt1, cnt2, h;
int root1[mxn], root2[mxn];
int nums[mxn];
vector<vector<int>> graph;

// 持久化二进制trie插入（根到点前缀用）
int insert1(int i,int val){
    int now = ++cnt1;
    tree1[now][0] = tree1[i][0];
    tree1[now][1] = tree1[i][1];
    pass1[now] = pass1[i] + 1;
    for(int j=bit-1;j>=0;j--){
        int b = (val>>j)&1;
        int prev_child = tree1[i][b];
        int nxt = ++cnt1;
        // 复制旧儿子指针
        tree1[nxt][0] = tree1[prev_child][0];
        tree1[nxt][1] = tree1[prev_child][1];
        pass1[nxt] = pass1[prev_child] + 1;
        // 挂到新根
        tree1[now][b] = nxt;
        // 下潜
        i = prev_child;
        now = nxt;
    }
    return (cnt1 - (bit)); // 返回最顶层新根（也就是第一次创建的 now）
    // 上面写法依赖我们每层新建1个节点，共建bit层；更稳妥：单独保存第一层的 root 索引：
}

// 按更稳妥写法（推荐）——保存第一层根
int insert1_stable(int i,int val){
    int newroot = ++cnt1;
    tree1[newroot][0] = tree1[i][0];
    tree1[newroot][1] = tree1[i][1];
    pass1[newroot] = pass1[i] + 1;

    int now = newroot, cur = i;
    for(int j=bit-1;j>=0;j--){
        int b = (val>>j)&1;
        int prev_child = tree1[cur][b];
        int nxt = ++cnt1;
        tree1[nxt][0] = tree1[prev_child][0];
        tree1[nxt][1] = tree1[prev_child][1];
        pass1[nxt] = pass1[prev_child] + 1;
        tree1[now][b] = nxt;
        cur = prev_child;
        now = nxt;
    }
    return newroot;
}

// dfn前缀trie插入（用于子树查询）
int insert2(int i,int val){
    int newroot = ++cnt2;
    tree2[newroot][0] = tree2[i][0];
    tree2[newroot][1] = tree2[i][1];
    pass2[newroot] = pass2[i] + 1;

    int now = newroot, cur = i;
    for(int j=bit-1;j>=0;j--){
        int b = (val>>j)&1;
        int prev_child = tree2[cur][b];
        int nxt = ++cnt2;
        tree2[nxt][0] = tree2[prev_child][0];
        tree2[nxt][1] = tree2[prev_child][1];
        pass2[nxt] = pass2[prev_child] + 1;
        tree2[now][b] = nxt;
        cur = prev_child;
        now = nxt;
    }
    return newroot;
}

void dfs(int u,int fa){
    dfn[u]=++h;
    sz[u]=1;
    depth[u]=depth[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<bit;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    // 根到点前缀trie
    root1[u]=insert1_stable(root1[fa], nums[u]);
    // dfn前缀trie
    root2[h]=insert2(root2[h-1], nums[u]);

    for(int v:graph[u]){
        if(v==fa) continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

// 子树查询：在 tree2（dfn前缀trie）上做区间 [L..R] 的差分
int query_subtree(int lroot,int rroot,int k){
    int res=0;
    for(int i=bit-1;i>=0;i--){
        int b = (k>>i)&1;
        int want = b^1;
        int cnt = pass2[ tree2[rroot][want] ] - pass2[ tree2[lroot][want] ];
        if(cnt>0){
            res |= (1<<i);
            lroot = tree2[lroot][want];
            rroot = tree2[rroot][want];
        }else{
            lroot = tree2[lroot][b];
            rroot = tree2[rroot][b];
        }
    }
    return res;
}

// 路径查询：在 tree1（根到点前缀trie）上做 C(x)+C(y)-C(lca)-C(parent(lca))
int query_path(int ax,int bx,int cx,int dx,int k){
    int res=0;
    for(int i=bit-1;i>=0;i--){
        int b = (k>>i)&1;
        int want = b^1;
        int cnt = pass1[ tree1[ax][want] ] + pass1[ tree1[bx][want] ]
                - pass1[ tree1[cx][want] ] - pass1[ tree1[dx][want] ];
        if(cnt>0){
            res |= (1<<i);
            ax = tree1[ax][want];
            bx = tree1[bx][want];
            cx = tree1[cx][want];
            dx = tree1[dx][want];
        }else{
            ax = tree1[ax][b];
            bx = tree1[bx][b];
            cx = tree1[cx][b];
            dx = tree1[dx][b];
        }
    }
    return res;
}

int lca(int u,int v){
    if(depth[u]<depth[v]) swap(u,v);
    for(int i=bit-1;i>=0;i--){
        if(depth[ st[u][i] ] >= depth[v]) u = st[u][i];
    }
    if(u==v) return u;
    for(int i=bit-1;i>=0;i--){
        if(st[u][i]!=st[v][i]){
            u=st[u][i];
            v=st[v][i];
        }
    }
    return st[u][0];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,q;
    cin>>n>>q;

    graph.assign(n+1, {});
    for(int i=1;i<=n;i++) cin>>nums[i];

    for(int i=1;i<=n-1;i++){ // 别多读
        int u,v; cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cnt1 = cnt2 = h = 0;
    // root1[0]=root2[0]=0, pass数组默认0

    dfs(1,0);

    while(q--){
        int op; cin>>op;
        if(op==1){
            int x,k; cin>>x>>k;
            int L = dfn[x]-1;
            int R = dfn[x]+sz[x]-1;
            cout<<query_subtree(root2[L], root2[R], k)<<"\n";
        }else{
            int x,y,k; cin>>x>>y>>k;
            int g = lca(x,y);
            int pg = st[g][0]; // parent(lca) 可能为0，root1[0]=0无事
            cout<<query_path(root1[x], root1[y], root1[g], root1[pg], k)<<"\n";
        }
    }
    return 0;
}
