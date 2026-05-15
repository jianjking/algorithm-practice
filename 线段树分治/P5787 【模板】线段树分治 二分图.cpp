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
         vector<pair<int,int>>&s, vector<vector<pair<int,int>>>&tree,
         int&cur, int n){

    int tmp = 0;

    for(auto &p : tree[nums]){
        int u = p.first;
        int v = p.second;

        if(root(u, father) == root(v, father)){
            for(int i = l; i <= r; i++){
                cout << "No" << '\n';
            }

            for(int i = 0; i < tmp; i++){
                undo(father, sz, s, cur);
            }

            return;
        }

        if(unio(u, v + n, father, sz, s, cur)) tmp++;
        if(unio(v, u + n, father, sz, s, cur)) tmp++;
    }

    if(l == r){
        cout << "Yes" << '\n';

        for(int i = 0; i < tmp; i++){
            undo(father, sz, s, cur);
        }

        return;
    }

    int mid = l + (r - l) / 2;

    dfs(l, mid, 2 * nums, father, sz, s, tree, cur, n);
    dfs(mid + 1, r, 2 * nums + 1, father, sz, s, tree, cur, n);

    for(int i = 0; i < tmp; i++){
        undo(father, sz, s, cur);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int>father(2 * n + 1);
    vector<int>sz(2 * n + 1);

    for(int i = 1; i <= 2 * n; i++){
        father[i] = i;
        sz[i] = 1;
    }

    vector<pair<int,int>>s(2 * m + 10);
    int cur = 0;

    vector<vector<pair<int,int>>>tree(4 * k + 5);

    for(int i = 0; i < m; i++){
        int x, y, l, r;
        cin >> x >> y >> l >> r;

        addedge(x, y, l + 1, r, 1, k, 1, tree);
    }

    dfs(1, k, 1, father, sz, s, tree, cur, n);

    return 0;
}