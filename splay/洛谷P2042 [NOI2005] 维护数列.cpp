#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int INF = 1000000001;

int head = 0;
int arr[MAXN];
int num[MAXN];
int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int siz[MAXN];
int space[MAXN], si;
int sum[MAXN];
int allv[MAXN];
int pre[MAXN];
int suf[MAXN];
bool updatev[MAXN];
int changev[MAXN];
bool revv[MAXN];

void up(int i){
    int l = ls[i], r = rs[i];
    siz[i] = siz[l] + siz[r] + 1;
    sum[i] = sum[l] + sum[r] + num[i];
    allv[i] = max(max(allv[l], allv[r]), suf[l] + num[i] + pre[r]);
    pre[i] = max(pre[l], sum[l] + num[i] + pre[r]);
    suf[i] = max(suf[r], suf[l] + num[i] + sum[r]);
}

int lr(int i){ return rs[fa[i]] == i ? 1 : 0; }

void rotate(int i){
    int f = fa[i], g = fa[f], soni = lr(i), sonf = lr(f);
    if (soni == 1){
        rs[f] = ls[i];
        if (rs[f]) fa[rs[f]] = f;
        ls[i] = f;
    }else{
        ls[f] = rs[i];
        if (ls[f]) fa[ls[f]] = f;
        rs[i] = f;
    }
    if (g){
        if (sonf == 1) rs[g] = i;
        else ls[g] = i;
    }
    fa[f] = i;
    fa[i] = g;
    up(f);
    up(i);
}

void splay(int i, int goal){
    while (fa[i] != goal){
        int f = fa[i], g = fa[f];
        if (g != goal){
            if (lr(i) == lr(f)) rotate(f);
            else rotate(i);
        }
        rotate(i);
    }
    if (goal == 0) head = i;
}

void setValue(int i, int val){
    if (!i) return;
    updatev[i] = true;
    changev[i] = val;
    num[i] = val;
    sum[i] = siz[i] * val;
    allv[i] = max(sum[i], val);
    pre[i] = max(sum[i], 0);
    suf[i] = max(sum[i], 0);
}

void setReverse(int i){
    if (!i) return;
    swap(pre[i], suf[i]);
    revv[i] ^= 1;
}

void down(int i){
    if (updatev[i]){
        setValue(ls[i], changev[i]);
        setValue(rs[i], changev[i]);
        updatev[i] = false;
    }
    if (revv[i]){
        swap(ls[i], rs[i]);
        setReverse(ls[i]);
        setReverse(rs[i]);
        revv[i] = false;
    }
}

int init(int val){
    int i = space[si--];
    siz[i] = 1;
    num[i] = sum[i] = allv[i] = val;
    pre[i] = suf[i] = max(val, 0);
    fa[i] = ls[i] = rs[i] = 0;
    updatev[i] = revv[i] = false;
    return i;
}

int build(int l, int r){
    int mid = (l + r) >> 1;
    int root = init(arr[mid]);
    if (l < mid){
        ls[root] = build(l, mid - 1);
        fa[ls[root]] = root;
    }
    if (mid < r){
        rs[root] = build(mid + 1, r);
        fa[rs[root]] = root;
    }
    up(root);
    return root;
}

int findk(int rank){
    int i = head;
    while (i){
        down(i);
        if (siz[ls[i]] + 1 == rank) return i;
        if (siz[ls[i]] >= rank) i = ls[i];
        else{
            rank -= siz[ls[i]] + 1;
            i = rs[i];
        }
    }
    return 0;
}

void insertSeg(int rank, int n){
    if (rank == 0){
        head = build(1, n);
    }else{
        int l = findk(rank);
        int r = findk(rank + 1);
        splay(l, 0);
        splay(r, l);
        ls[r] = build(1, n);
        fa[ls[r]] = r;
        up(r);
        up(l);
    }
}

void recycle(int i){
    if (!i) return;
    space[++si] = i;
    recycle(ls[i]);
    recycle(rs[i]);
}

void removeSeg(int rank, int n){
    int l = findk(rank - 1);
    int r = findk(rank + n);
    splay(l, 0);
    splay(r, l);
    recycle(ls[r]);
    ls[r] = 0;
    up(r);
    up(l);
}

void resetSeg(int rank, int n, int val){
    int l = findk(rank - 1);
    int r = findk(rank + n);
    splay(l, 0);
    splay(r, l);
    setValue(ls[r], val);
    up(r);
    up(l);
}

void reverseSeg(int rank, int n){
    int l = findk(rank - 1);
    int r = findk(rank + n);
    splay(l, 0);
    splay(r, l);
    setReverse(ls[r]);
    up(r);
    up(l);
}

int querySum(int rank, int n){
    int l = findk(rank - 1);
    int r = findk(rank + n);
    splay(l, 0);
    splay(r, l);
    return sum[ls[r]];
}

int queryMax(){
    return allv[head];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    si = MAXN - 1;
    for (int i = 1; i <= si; i++) space[i] = i;

    arr[1] = arr[n + 2] = allv[0] = -INF;
    for (int i = 1, j = 2; i <= n; i++, j++) cin >> arr[j];
    insertSeg(0, n + 2);

    string op;
    for (int i = 0; i < m; i++){
        cin >> op;
        if (op == "MAX-SUM"){
            cout << queryMax() << '\n';
        }else{
            int pos, len, c;
            cin >> pos >> len;
            pos++;
            if (op == "INSERT"){
                for (int j = 1; j <= len; j++) cin >> arr[j];
                insertSeg(pos, len);
            }else if (op == "DELETE"){
                removeSeg(pos, len);
            }else if (op == "MAKE-SAME"){
                cin >> c;
                resetSeg(pos, len, c);
            }else if (op == "REVERSE"){
                reverseSeg(pos, len);
            }else if (op == "GET-SUM"){
                cout << querySum(pos, len) << '\n';
            }
        }
    }
    return 0;
}