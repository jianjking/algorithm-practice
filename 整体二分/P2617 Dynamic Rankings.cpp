#include<bits/stdc++.h>
using namespace std;

struct str{
    int num;   // 1 修改事件，2 查询事件
    int p;     // 修改：位置；查询：左端点
    int v;     // 修改：值；查询：右端点
    int k;     // 修改：+1/-1；查询：第k小
    int time;  // 查询编号
};

int lowbit(int i){
    return i & (-i);
}

void addnum(int p,int v,vector<int>&tree){
    int n = tree.size() - 1;
    while(p <= n){
        tree[p] += v;
        p += lowbit(p);
    }
}

int query(int i,vector<int>&tree){
    int ans = 0;
    while(i > 0){
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

void dfs(int ql,int qr,int l,int r,vector<str>&op,vector<int>&tree,vector<int>&ans){
    if(ql > qr) return;

    if(l == r){
        for(int i = ql; i <= qr; i++){
            if(op[i].num == 2){
                ans[op[i].time] = l;
            }
        }
        return;
    }

    int mid = l + (r - l) / 2;

    vector<str> qql;
    vector<str> qqr;

    for(int i = ql; i <= qr; i++){
        if(op[i].num == 1){
            if(op[i].v <= mid){
                addnum(op[i].p, op[i].k, tree);
                qql.push_back(op[i]);
            }
            else{
                qqr.push_back(op[i]);
            }
        }
        else{
            int l1 = op[i].p;
            int r1 = op[i].v;
            int need = op[i].k;

            int cnt = query(r1, tree) - query(l1 - 1, tree);

            if(need <= cnt){
                qql.push_back(op[i]);
            }
            else{
                str tmp = op[i];
                tmp.k -= cnt;
                qqr.push_back(tmp);
            }
        }
    }

    int pos = ql;

    for(int i = 0; i < (int)qql.size(); i++){
        op[pos++] = qql[i];
    }

    for(int i = 0; i < (int)qqr.size(); i++){
        op[pos++] = qqr[i];
    }

    // 撤销这一层对树状数组的影响
    for(auto &e : qql){
        if(e.num == 1 && e.v <= mid){
            addnum(e.p, -e.k, tree);
        }
    }

    int lsiz = qql.size();

    dfs(ql, ql + lsiz - 1, l, mid, op, tree, ans);
    dfs(ql + lsiz, qr, mid + 1, r, op, tree, ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin >> n >> m;

    vector<str> op(n + 2 * m + 5);

    int cur = 1;

    vector<int> val(n + 1);
    vector<int> tree(n + 1, 0);

    for(int i = 1; i <= n; i++){
        int v;
        cin >> v;
        op[cur++] = {1, i, v, 1, 0};
        val[i] = v;
    }

    for(int i = 1; i <= m; i++){
        char ch;
        cin >> ch;

        if(ch == 'Q'){
            int l,r,k;
            cin >> l >> r >> k;
            op[cur++] = {2, l, r, k, i};
        }
        else{
            int x,y;
            cin >> x >> y;

            op[cur++] = {1, x, val[x], -1, i};
            op[cur++] = {1, x, y, 1, i};

            val[x] = y;
        }
    }

    vector<int> ans(m + 1, -1);

    int l = 1;
    int r = 1000000000;

    dfs(1, cur - 1, l, r, op, tree, ans);

    for(int i = 1; i <= m; i++){
        if(ans[i] != -1){
            cout << ans[i] << '\n';
        }
    }

    return 0;
}