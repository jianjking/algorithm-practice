#include <bits/stdc++.h>
using namespace std;

const int mx = 100000 + 5;
int zuo[mx], you[mx], nums[mx], dist[mx], father[mx];

int root(int x){ return father[x]==x ? x : father[x]=root(father[x]); }

// 左偏树合并：按 (值, 编号) 作为优先级，小的当根
int merge_heap(int a, int b){
    if(a==0 || b==0) return a + b;
    if(nums[a] > nums[b] || (nums[a]==nums[b] && a>b)) swap(a, b);
    you[a] = merge_heap(you[a], b);
    if(dist[zuo[a]] < dist[you[a]]) swap(zuo[a], you[a]);
    dist[a] = dist[you[a]] + 1;
    return a;
}

// 弹出堆顶 x（x 必为当前堆根），返回新根
int pop_root(int x){
    int t = merge_heap(zuo[x], you[x]);
    father[x] = t;
    if(t) father[t] = t;
    // 清掉旧节点结构信息（稳妥做法）
    zuo[x] = you[x] = 0;
    dist[x] = 0;
    return t;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if(!(cin >> n >> m)) return 0;
    for(int i=1;i<=n;i++) cin >> nums[i];

    dist[0] = -1;                  // 空节点 NPL = -1
    for(int i=1;i<=n;i++) father[i] = i;  // 初态每点自成一堆

    while(m--){
        int op; 
        cin >> op;
        if(op == 1){
            int x, y; 
            cin >> x >> y;
            // 题意：如果 x 或 y 对应的那个“点”已被删除，则忽略
            if(nums[x]==-1 || nums[y]==-1) continue;
            int rx = root(x), ry = root(y);
            if(rx == ry) continue;
            int r = merge_heap(rx, ry);
            father[rx] = father[ry] = r;
            father[r]  = r;
        }else{
            int x; 
            cin >> x;
            // 如果编号 x 这个点已经被删，直接输出 -1
            if(nums[x]==-1){
                cout << -1 << '\n';
                continue;
            }
            int r = root(x);          // 找到 x 所在堆的当前根
            cout << nums[r] << '\n';  // 输出堆顶值
            pop_root(r);              // 弹出堆顶并合并左右子堆
            nums[r] = -1;             // 标记“被弹出的那个原编号点”已删除
        }
    }
    return 0;
}
