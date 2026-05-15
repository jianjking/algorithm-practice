#include<bits/stdc++.h>
using namespace std;

int root(int f, vector<int>&father){
    while(f != father[f]) f = father[f];
    return f;
}

bool unio(int u, int v, vector<int>&father, vector<int>&sz, vector<pair<int,int>>&s, int&cur){
    u = root(u, father);
    v = root(v, father);

    if(u == v) return false;

    if(sz[u] > sz[v]){
        father[v] = u;
        sz[u] += sz[v];
        s[cur++] = {u, v};
    }
    else{
        father[u] = v;
        sz[v] += sz[u];
        s[cur++] = {v, u};
    }

    return true;
}

void undo(vector<int>&father, vector<int>&sz, vector<pair<int,int>>&s, int&cur){
    int f = s[cur - 1].first;
    int son = s[cur - 1].second;
    cur--;
    father[son] = son;
    sz[f] -= sz[son];
}

void addedge(int u, int v, int lt, int rt, int l, int r, int nums, vector<vector<pair<int,int>>>&tree){
    if(lt > rt) return;

    if(lt <= l && r <= rt){
        tree[nums].push_back({u, v});
        return;
    }

    int mid = l + (r - l) / 2;

    if(lt <= mid){
        addedge(u, v, lt, rt, l, mid, 2 * nums, tree);
    }

    if(rt > mid){
        addedge(u, v, lt, rt, mid + 1, r, 2 * nums + 1, tree);
    }
}

void dfs(int l, int r, int nums, vector<int>&father, vector<int>&sz,
         vector<vector<pair<int,int>>>&tree, vector<pair<int,int>>&s,
         int&cur, int&part, int&ans){

    int cnt = 0;

    for(auto &p : tree[nums]){
        int u = p.first;
        int v = p.second;

        int fu = root(u, father);
        int fv = root(v, father);

        if(fu == fv) continue;

        unio(fu, fv, father, sz, s, cur);
        part--;
        cnt++;
    }

    if(l == r){
        if(part == 1){
            ans = min(ans, l);
        }

        for(int i = 0; i < cnt; i++){
            undo(father, sz, s, cur);
            part++;
        }

        return;
    }

    int mid = l + (r - l) / 2;

    dfs(l, mid, 2 * nums, father, sz, tree, s, cur, part, ans);
    dfs(mid + 1, r, 2 * nums + 1, father, sz, tree, s, cur, part, ans);

    for(int i = 0; i < cnt; i++){
        undo(father, sz, s, cur);
        part++;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int k = 0;
    vector<vector<int>>edge(m, vector<int>(3));

    for(int i = 0; i < m; i++){
        cin >> edge[i][0] >> edge[i][1] >> edge[i][2];
        k = max(k, edge[i][2]);
    }

    int V = k + 1;

    vector<vector<pair<int,int>>>tree(4 * (V + 1) + 5);

    vector<int>father(n + 1);
    vector<int>sz(n + 1);
    vector<pair<int,int>>s(m + 5);

    int cur = 0;

    for(int i = 1; i <= n; i++){
        father[i] = i;
        sz[i] = 1;
    }

    for(int i = 0; i < m; i++){
        int u = edge[i][0];
        int v = edge[i][1];
        int w = edge[i][2];

        if(w > 0){
            addedge(u, v, 0, w - 1, 0, V, 1, tree);
        }

        addedge(u, v, w + 1, V, 0, V, 1, tree);
    }

    int part = n;
    int ans = INT_MAX;

    dfs(0, V, 1, father, sz, tree, s, cur, part, ans);

    cout << ans << '\n';

    return 0;
}