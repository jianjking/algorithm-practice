#include<bits/stdc++.h>
using namespace std;

struct node{
    int u;
    int uteam;
    int v;
    int vteam;
};

int root(int f, vector<int>& fa){
    while(fa[f] != f) f = fa[f];
    return f;
}

bool unio(int u, int v, vector<int>& fa, vector<int>& sz, vector<pair<int,int>>& s, int& now){
    int fu = root(u, fa);
    int fv = root(v, fa);

    if(fu == fv) return false;

    if(sz[fu] > sz[fv]){
        fa[fv] = fu;
        sz[fu] += sz[fv];
        s[now++] = {fu, fv};
    }
    else{
        fa[fu] = fv;
        sz[fv] += sz[fu];
        s[now++] = {fv, fu};
    }

    return true;
}

void undo(vector<int>& fa, vector<int>& sz, vector<pair<int,int>>& s, int& now){
    now--;
    int f = s[now].first;
    int son = s[now].second;

    fa[son] = son;
    sz[f] -= sz[son];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    int allk = k;

    vector<int> team(n + 1, 0);
    for(int i = 1; i <= n; i++){
        cin >> team[i];
    }

    vector<int> father(2 * n + 1, 0);
    vector<int> sz(2 * n + 1, 1);

    for(int i = 1; i <= 2 * n; i++){
        father[i] = i;
    }

    vector<node> crossedge(m);
    vector<int> inside(allk + 1, false);

    vector<pair<int,int>> s(2 * m + 5);

    int now = 0;
    int cur = 0;

    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;

        if(team[u] < team[v]){
            crossedge[cur++] = {u, team[u], v, team[v]};
        }
        else if(team[v] < team[u]){
            crossedge[cur++] = {v, team[v], u, team[u]};
        }
        else{
            int g = team[u];

            if(inside[g]) continue;

            if(root(u, father) == root(v, father)){
                k--;
                inside[g] = true;
                continue;
            }

            unio(u, v + n, father, sz, s, now);
            unio(v, u + n, father, sz, s, now);
        }
    }

    long long ans = 1LL * k * (k - 1) / 2;

    sort(crossedge.begin(), crossedge.begin() + cur, [](const node& a, const node& b){
        if(a.uteam != b.uteam) return a.uteam < b.uteam;
        return a.vteam < b.vteam;
    });

    int l = 0;

    while(l < cur){
        int r = l;

        while(r < cur &&
              crossedge[r].uteam == crossedge[l].uteam &&
              crossedge[r].vteam == crossedge[l].vteam){
            r++;
        }

        if(inside[crossedge[l].uteam] || inside[crossedge[l].vteam]){
            l = r;
            continue;
        }

        int checkpoint = now;
        bool ok = true;

        for(int tmp = l; tmp < r; tmp++){
            int u = crossedge[tmp].u;
            int v = crossedge[tmp].v;

            if(root(u, father) == root(v, father)){
                ok = false;
                break;
            }

            unio(u, v + n, father, sz, s, now);
            unio(v, u + n, father, sz, s, now);
        }

        if(!ok){
            ans--;
        }

        while(now > checkpoint){
            undo(father, sz, s, now);
        }

        l = r;
    }

    cout << ans << '\n';

    return 0;
}