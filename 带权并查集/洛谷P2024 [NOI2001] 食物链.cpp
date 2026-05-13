#include <bits/stdc++.h>
using namespace std;

int nums(int i){ return (i + 3) % 3; } // 规避负数取模

int root(int i, vector<int>& fa, vector<int>& dist){
    if (fa[i] == i) return i;
    int p = fa[i];
    int f = root(p, fa, dist);
    dist[i] = nums(dist[i] + dist[p]);  // 累加到根的关系
    fa[i] = f;
    return f;
}

void merge1(int x, int y, int op, int &cnt, vector<int>& fa, vector<int>& dist){
    int xf = root(x, fa, dist);
    int yf = root(y, fa, dist);
    if (xf == yf){
        if (nums(dist[x] - dist[y]) != op) cnt++;  // 冲突=>假话
        return;
    }
    // 令 fa[xf] = yf，保持 type[x] - type[y] == op
    dist[xf] = nums(dist[y] + op - dist[x]);
    fa[xf] = yf;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;                 // ☆ 修正：双箭头读取
    vector<int> fa(n + 1), dist(n + 1, 0);

    // ☆ 初始化并查集
    for (int i = 1; i <= n; ++i) fa[i] = i;

    int cnt = 0;
    for (int i = 0; i < k; ++i){
        int op, x, y;
        cin >> op >> x >> y;

        // ☆ 边界假话：越界
        if (x < 1 || x > n || y < 1 || y > n){
            cnt++;
            continue;
        }
        // ☆ 边界假话：吃自己
        if (op == 2 && x == y){
            cnt++;
            continue;
        }

        if (op == 1){
            // 同类 => type[x] - type[y] == 0
            merge1(x, y, 0, cnt, fa, dist);
        }else{ // op == 2
            // x 吃 y => type[x] - type[y] == 1
            merge1(x, y, 1, cnt, fa, dist);
        }
    }
    cout << cnt << '\n';
    return 0;
}
