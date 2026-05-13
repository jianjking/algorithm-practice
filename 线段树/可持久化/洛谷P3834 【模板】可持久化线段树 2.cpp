#include <bits/stdc++.h>
using namespace std;

const int mx = 5e6;
int zuo[mx], you[mx], sz[mx], head[mx];
unordered_map<int,int> ranked; // rank -> value
unordered_map<int,int> anti;   // value -> rank
int cnt, h;

int build(int l,int r){
    int num = cnt++;
    sz[num] = 0; // 明确置零
    if(l==r) return num;
    int mid = l + (r-l)/2;
    zuo[num] = build(l, mid);
    you[num] = build(mid+1, r);
    return num;
}
int update(int l,int r,int target,int cur){
    int num = cnt++;
    zuo[num] = zuo[cur];
    you[num] = you[cur];
    sz[num]  = sz[cur] + 1; // 路径拷贝 +1
    if(l==r) return num;
    int mid = l + (r-l)/2;
    if(target <= mid){
        zuo[num] = update(l, mid, target, zuo[cur]);
    }else{
        you[num] = update(mid+1, r, target, you[cur]);
    }
    return num;
}
void query(int curl,int curr,int l,int r,int k){
    if(l==r){
        // l 是 rank，输出 value：ranked[l]
        cout << ranked[l] << '\n';
        return;
    }
    int leftCnt = sz[zuo[curr]] - sz[zuo[curl]];
    int mid = l + (r-l)/2;
    if(leftCnt >= k){
        query(zuo[curl], zuo[curr], l, mid, k);
    }else{
        query(you[curl], you[curr], mid+1, r, k - leftCnt);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cnt = 0; h = 0;

    int n, m;
    if(!(cin >> n >> m)) return 0;

    // 1) 读原数组到 a；另做一份用于离散化
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    vector<int> vals = a;                 // 拷贝一份做离散化
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int s = (int)vals.size();             // 离散化后的取值个数

    // 2) 建 rank <-> value 映射
    ranked.clear(); anti.clear();
    for(int i=0;i<s;i++){
        ranked[i+1] = vals[i];            // rank -> value
        anti[vals[i]] = i+1;              // value -> rank
    }

    // 3) 建 0 版本（空树），以及前缀版本
    head[h++] = build(1, s);              // head[0]
    for(int i=0;i<n;i++){
        int rk = anti[a[i]];              // 用原数组值映射到 rank
        head[h++] = update(1, s, rk, head[i]); // head[i+1]
    }

    // 4) 处理查询
    for(int i=0;i<m;i++){
        int l, r, k;
        cin >> l >> r >> k;               // 1-indexed
        query(head[l-1], head[r], 1, s, k);
    }
    return 0;
}
