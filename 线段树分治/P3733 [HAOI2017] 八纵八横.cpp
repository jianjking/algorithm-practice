#include<bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXQ = 1005;
const int MAXLEN = 1005;

int n, m, q;

int father[MAXN];
bitset<MAXLEN> val[MAXN];

int lastt[MAXQ];
int X[MAXQ];
int Y[MAXQ];
bitset<MAXLEN> V[MAXQ];

struct str{
    int x;
    int y;
    bitset<MAXLEN> v;
};

vector<str> tree[MAXQ * 4];

bitset<MAXLEN> xian[MAXLEN];
int rollback[MAXLEN + 5];
int cur = 0;

bitset<MAXLEN> readbit(string s){
    bitset<MAXLEN> tmp;
    for(int i = 0; i < (int)s.size(); i++){
        tmp[i] = s[s.size() - 1 - i] - '0';
    }
    return tmp;
}

bool insert(bitset<MAXLEN> tmp){
    for(int i = MAXLEN - 1; i >= 0; i--){
        if(!tmp[i]) continue;

        if(xian[i].none()){
            xian[i] = tmp;
            rollback[cur++] = i;
            return true;
        }

        tmp ^= xian[i];
    }

    return false;
}

bitset<MAXLEN> getans(){
    bitset<MAXLEN> ans;

    for(int i = MAXLEN - 1; i >= 0; i--){
        if(xian[i].none()) continue;

        if(!ans[i]){
            ans ^= xian[i];
        }
    }

    return ans;
}

void print(bitset<MAXLEN> ans){
    int j = MAXLEN - 1;

    while(j > 0 && ans[j] == 0) j--;

    for(int i = j; i >= 0; i--){
        cout << ans[i];
    }

    cout << '\n';
}

int root(int f){
    if(f != father[f]){
        int tmp = father[f];
        father[f] = root(tmp);
        val[f] ^= val[tmp];
    }

    return father[f];
}

void unio_init(int u, int v, bitset<MAXLEN> tmp){
    int fu = root(u);
    int fv = root(v);

    if(fu == fv){
        insert(tmp ^ val[u] ^ val[v]);
    }
    else{
        father[fu] = fv;
        val[fu] = val[u] ^ val[v] ^ tmp;
    }
}

void addedge(int lt, int rt, str tmp, int l, int r, int nums){
    if(lt > rt) return;

    if(lt <= l && r <= rt){
        tree[nums].push_back(tmp);
        return;
    }

    int mid = (l + r) / 2;

    if(lt <= mid){
        addedge(lt, rt, tmp, l, mid, nums * 2);
    }

    if(rt > mid){
        addedge(lt, rt, tmp, mid + 1, r, nums * 2 + 1);
    }
}

void dfs(int l, int r, int nums){
    int oldcur = cur;

    for(auto &p : tree[nums]){
        bitset<MAXLEN> tmp = p.v ^ val[p.x] ^ val[p.y];
        insert(tmp);
    }

    if(l == r){
        print(getans());
    }
    else{
        int mid = (l + r) / 2;
        dfs(l, mid, nums * 2);
        dfs(mid + 1, r, nums * 2 + 1);
    }

    while(cur > oldcur){
        int pos = rollback[--cur];
        xian[pos].reset();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;

    for(int i = 1; i <= n; i++){
        father[i] = i;
        val[i].reset();
    }

    for(int i = 1; i <= m; i++){
        int u, v;
        string s;
        cin >> u >> v >> s;

        bitset<MAXLEN> tmp = readbit(s);

        unio_init(u, v, tmp);
    }

    for(int i = 1; i <= n; i++){
        root(i);
    }

    print(getans());

    int cnt = 0;

    for(int i = 1; i <= q; i++){
        string op;
        cin >> op;

        if(op == "Add"){
            int u, v;
            string s;
            cin >> u >> v >> s;

            ++cnt;

            X[cnt] = u;
            Y[cnt] = v;
            V[cnt] = readbit(s);
            lastt[cnt] = i;
        }
        else if(op == "Cancel"){
            int k;
            cin >> k;

            str tmp;
            tmp.x = X[k];
            tmp.y = Y[k];
            tmp.v = V[k];

            addedge(lastt[k], i - 1, tmp, 1, q, 1);

            lastt[k] = 0;
        }
        else if(op == "Change"){
            int k;
            string s;
            cin >> k >> s;

            str tmp;
            tmp.x = X[k];
            tmp.y = Y[k];
            tmp.v = V[k];

            addedge(lastt[k], i - 1, tmp, 1, q, 1);

            V[k] = readbit(s);
            lastt[k] = i;
        }
    }

    for(int i = 1; i <= cnt; i++){
        if(lastt[i] != 0){
            str tmp;
            tmp.x = X[i];
            tmp.y = Y[i];
            tmp.v = V[i];

            addedge(lastt[i], q, tmp, 1, q, 1);
        }
    }

    if(q > 0){
        dfs(1, q, 1);
    }

    return 0;
}