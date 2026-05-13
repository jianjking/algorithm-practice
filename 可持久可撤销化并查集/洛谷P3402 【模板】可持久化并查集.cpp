#include<bits/stdc++.h>
using namespace std;

const int MAXM = 200001;
const int MAXN = 10000000;

int rootfa[MAXM];
int rootsz[MAXM];

int lr[MAXN];
int rr[MAXN];
int val[MAXN];

int cnt = 0;
int n, m;

int buildfa(int l, int r){
    int now = ++cnt;
    if(l == r){
        val[now] = l;
        return now;
    }
    int mid = (l + r) >> 1;
    lr[now] = buildfa(l, mid);
    rr[now] = buildfa(mid + 1, r);
    return now;
}

int buildsz(int l, int r){
    int now = ++cnt;
    if(l == r){
        val[now] = 1;
        return now;
    }
    int mid = (l + r) >> 1;
    lr[now] = buildsz(l, mid);
    rr[now] = buildsz(mid + 1, r);
    return now;
}

int update(int node, int v, int l, int r, int pos){
    int now = ++cnt;

    lr[now] = lr[pos];
    rr[now] = rr[pos];
    val[now] = val[pos];

    if(l == r){
        val[now] = v;
        return now;
    }

    int mid = (l + r) >> 1;
    if(node <= mid){
        lr[now] = update(node, v, l, mid, lr[pos]);
    }
    else{
        rr[now] = update(node, v, mid + 1, r, rr[pos]);
    }

    return now;
}

int query(int node, int l, int r, int pos){
    if(l == r){
        return val[pos];
    }

    int mid = (l + r) >> 1;
    if(node <= mid){
        return query(node, l, mid, lr[pos]);
    }
    else{
        return query(node, mid + 1, r, rr[pos]);
    }
}

int findroot(int x, int ver){
    int fa = query(x, 1, n, rootfa[ver]);
    while(x != fa){
        x = fa;
        fa = query(x, 1, n, rootfa[ver]);
    }
    return x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    rootfa[0] = buildfa(1, n);
    rootsz[0] = buildsz(1, n);

    for(int ver = 1; ver <= m; ver++){
        int op, x, y;
        cin >> op;

        rootfa[ver] = rootfa[ver - 1];
        rootsz[ver] = rootsz[ver - 1];

        if(op == 1){
            cin >> x >> y;

            int fx = findroot(x, ver);
            int fy = findroot(y, ver);

            if(fx == fy){
                continue;
            }

            int sizex = query(fx, 1, n, rootsz[ver]);
            int sizey = query(fy, 1, n, rootsz[ver]);

            if(sizex >= sizey){
                rootfa[ver] = update(fy, fx, 1, n, rootfa[ver]);
                rootsz[ver] = update(fx, sizex + sizey, 1, n, rootsz[ver]);
            }
            else{
                rootfa[ver] = update(fx, fy, 1, n, rootfa[ver]);
                rootsz[ver] = update(fy, sizex + sizey, 1, n, rootsz[ver]);
            }
        }
        else if(op == 2){
            cin >> x;

            rootfa[ver] = rootfa[x];
            rootsz[ver] = rootsz[x];
        }
        else{
            cin >> x >> y;

            int fx = findroot(x, ver);
            int fy = findroot(y, ver);

            if(fx == fy){
                cout << 1 << '\n';
            }
            else{
                cout << 0 << '\n';
            }
        }
    }

    return 0;
}