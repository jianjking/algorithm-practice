#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+5;
const int maxt=maxn*60;     // 约 600 万结点上限，足够
const int bit=20;           // LCA 对 1e5 节点够用

int st[maxn][bit];
int tree[maxt][27];         // 27 路，你也可以改 26
int root[maxn];
int pass[maxt];             // 经过该 trie 结点的串数
int depth[maxn];
int cnt;

vector<vector<pair<int,string>>> graph;

int insert(int i, const string &s){
    // 1) 新根 = 旧根 i 的拷贝 + pass 增 1
    int now = ++cnt;
    for(int j=0;j<27;j++) tree[now][j] = tree[i][j];
    pass[now] = pass[i] + 1;

    int pre = now;   // 新版本当前结点
    int old = i;     // 旧版本对应结点

    // 2) 沿 s 的每个字符做“路径复制”
    for(int z=0; z<(int)s.size(); z++){
        int c = s[z]-'a';
        int old_child = tree[old][c];  // 旧孩子

        int cur = ++cnt;               // 新孩子
        for(int j=0;j<27;j++) tree[cur][j] = tree[old_child][j]; // 从旧孩子拷
        pass[cur] = pass[old_child] + 1;

        tree[pre][c] = cur;            // 接上新孩子
        pre = cur;
        old = old_child;
    }
    return now;
}

void dfs(int u,int f){
    depth[u]=depth[f]+1;
    st[u][0]=f;
    for(int i=1;i<bit;i++) st[u][i]=st[st[u][i-1]][i-1];

    for(auto &[v,s]:graph[u]){
        if(v==f) continue;
        root[v]=insert(root[u],s);     // v 的版本 = u 的版本 + 插入边串
        dfs(v,u);
    }
}

int query(int uroot,int vroot,const string &s){
    int a=uroot, b=vroot;
    for(char ch: s){
        int c = ch - 'a';
        a = tree[a][c];
        b = tree[b][c];
        if(pass[a]-pass[b]==0) return 0;  // 该前缀不存在，提前结束
    }
    return pass[a]-pass[b];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n;
    graph.resize(n+1);

    for(int i=1;i<n;i++){
        int u,v; string s;
        cin>>u>>v>>s;
        graph[u].emplace_back(v,s);
        graph[v].emplace_back(u,s);
    }

    // root[1] 默认是 0 号空版本（全局数组已清零）
    dfs(1,0);

    cin>>m;
    while(m--){
        int u,v; string s;
        cin>>u>>v>>s;

        int u0=u, v0=v;

        // LCA
        if(depth[u]<depth[v]) swap(u,v);
        for(int j=bit-1;j>=0;j--)
            if(depth[st[u][j]]>=depth[v]) u=st[u][j];
        if(u!=v){
            for(int j=bit-1;j>=0;j--)
                if(st[u][j]!=st[v][j]){
                    u=st[u][j];
                    v=st[v][j];
                }
            u=st[u][0];
        }
        int lca=u;

        // 路径(u0,v0) = (root[u0]-root[lca]) + (root[v0]-root[lca])
        int ans = 0;
        ans += query(root[u0], root[lca], s);
        ans += query(root[v0], root[lca], s);
        cout<<ans<<"\n";
    }
    return 0;
}
