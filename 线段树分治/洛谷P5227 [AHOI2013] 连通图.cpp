#include<bits/stdc++.h>
using namespace std;

int root(int f, vector<int>& father){
    while(f != father[f]) f = father[f];
    return f;
}

void unio(int u, int v, vector<int>& father, vector<int>& sz, vector<pair<int,int>>& s, int& cur){
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
}

void undo(vector<int>& father, vector<int>& sz, vector<pair<int,int>>& s, int& cur){
    cur--;
    int f = s[cur].first;
    int son = s[cur].second;
    father[son] = son;
    sz[f] -= sz[son];
}

void addedge(int lt, int rt, int u, int v, int l, int r, int nums, vector<vector<pair<int,int>>>& tree){
    if(lt <= l && r <= rt){
        tree[nums].push_back({u, v});
        return;
    }

    int mid = l + (r - l) / 2;

    if(lt <= mid){
        addedge(lt, rt, u, v, l, mid, nums * 2, tree);
    }

    if(rt > mid){
        addedge(lt, rt, u, v, mid + 1, r, nums * 2 + 1, tree);
    }
}

void dfs(int l, int r, int nums, vector<int>& father, vector<int>& sz,
         vector<vector<pair<int,int>>>& tree, vector<pair<int,int>>& s,
         int& cur, int& part){

    int tmp = 0;

    for(auto &p : tree[nums]){
        int u = p.first;
        int v = p.second;

        int fu = root(u, father);
        int fv = root(v, father);

        if(fu == fv) continue;

        unio(fu, fv, father, sz, s, cur);
        part--;
        tmp++;
    }

    if(l == r){
        if(part == 1){
            cout << "Connected" << '\n';
        }
        else{
            cout << "Disconnected" << '\n';
        }

        for(int i = 0; i < tmp; i++){
            undo(father, sz, s, cur);
            part++;
        }

        return;
    }

    int mid = l + (r - l) / 2;

    dfs(l, mid, nums * 2, father, sz, tree, s, cur, part);
    dfs(mid + 1, r, nums * 2 + 1, father, sz, tree, s, cur, part);

    for(int i = 0; i < tmp; i++){
        undo(father, sz, s, cur);
        part++;
    }
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<pair<int,int>> edge(m + 1);

    for(int i = 1; i <= m; i++){
        cin >> edge[i].first >> edge[i].second;
    }

    int k;
    cin >> k;

    vector<pair<int,int>> add;
    vector<bool> vis(m + 1, false);

    for(int i = 1; i <= k; i++){
        int c;
        cin >> c;

        for(int j = 0; j < c; j++){
            int x;
            cin >> x;

            add.push_back({x, i});
            vis[x] = true;
        }
    }

    sort(add.begin(), add.end(), [](const pair<int,int>& a, const pair<int,int>& b){
        if(a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });

    vector<vector<pair<int,int>>> tree(4 * k + 5);

    int tmp = add.size();
    int l = 0;

    while(l < tmp){
        int r = l;

        while(r + 1 < tmp && add[r + 1].first == add[l].first){
            r++;
        }

        int id = add[l].first;
        int pre = 0;

        for(int i = l; i <= r; i++){
            int now = add[i].second;

            if(pre + 1 <= now - 1){
                addedge(pre + 1, now - 1, edge[id].first, edge[id].second, 1, k, 1, tree);
            }

            pre = now;
        }

        if(pre + 1 <= k){
            addedge(pre + 1, k, edge[id].first, edge[id].second, 1, k, 1, tree);
        }

        l = r + 1;
    }

    for(int i = 1; i <= m; i++){
        if(!vis[i]){
            addedge(1, k, edge[i].first, edge[i].second, 1, k, 1, tree);
        }
    }

    vector<int> father(n + 1);
    vector<int> sz(n + 1, 1);

    for(int i = 1; i <= n; i++){
        father[i] = i;
    }

    vector<pair<int,int>> s(n + 5);

    int cur = 0;
    int part = n;

    dfs(1, k, 1, father, sz, tree, s, cur, part);

    return 0;
}