#include<bits/stdc++.h>
using namespace std;

const int mx = 6 * 1000000; // 节点池，n=2e5 时够用
int zuo[mx], you[mx], head[mx], lastzuo[mx], nums[mx];
int cnt, h;

// 建树：区间 [0..n]，把左右儿子连好，并维护 lastzuo 为子区间的最小值
int build(int l, int r){
    int num = cnt++;
    if(l == r){
        // 初值为0：表示“这个值从未出现过”，对 mex 判定是友好的（0 < 任意 l>=1）
        lastzuo[num] = 0;
        zuo[num] = you[num] = 0;
        return num;
    }
    int mid = (l + r) >> 1;
    zuo[num] = build(l, mid);
    you[num] = build(mid + 1, r);
    lastzuo[num] = min(lastzuo[zuo[num]], lastzuo[you[num]]);
    return num;
}

// 版本插入：把值 pos 的“最后出现位置”改成 last（=当前下标）
// 注意：递归时要用 cur 的子指针 zuo[cur]/you[cur]，不是 lastzuo[cur]！！
int insert(int l, int r, int pos, int last, int cur){
    int num = cnt++;
    zuo[num] = zuo[cur];
    you[num] = you[cur];
    lastzuo[num] = lastzuo[cur];
    if(l == r){
        lastzuo[num] = last;
        return num;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid){
        zuo[num] = insert(l, mid, pos, last, zuo[cur]);
    }else{
        you[num] = insert(mid + 1, r, pos, last, you[cur]);
    }
    lastzuo[num] = min(lastzuo[zuo[num]], lastzuo[you[num]]);
    return num;
}

// 查询 mex：在版本 head[r] 上，找最小的 x 使得 lastpos[x] < l（说明 x 没出现在 [l..r]）
// 到叶子时：若没出现（< limit）返回该值；否则返回下一个值（可能是 n+1）
int query_mex(int l, int r, int cur, int limit){
    if(l == r){
        return (lastzuo[cur] < limit) ? l : (l + 1);
    }
    int mid = (l + r) >> 1;
    if(lastzuo[zuo[cur]] < limit){
        return query_mex(l, mid, zuo[cur], limit);
    }else{
        return query_mex(mid + 1, r, you[cur], limit);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    cnt = 0; h = 0;
    head[h++] = build(0, n); // 只需要一次 build

    for(int i = 1; i <= n; ++i){
        cin >> nums[i];
        if(nums[i] > n){
            // >n 的数对 mex 无贡献，版本不变
            head[h++] = head[h - 1];
        }else{
            head[h++] = insert(0, n, nums[i], i, head[h - 1]);
        }
    }

    while(m--){
        int l, r;
        cin >> l >> r;
        // 用前缀 r 的版本，在 [0..n] 上找 mex（limit = l）
        cout << query_mex(0, n, head[r], l) << '\n';
    }
    return 0;
}
