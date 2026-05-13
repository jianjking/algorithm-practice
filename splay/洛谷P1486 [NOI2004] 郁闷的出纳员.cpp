#include <bits/stdc++.h>
using namespace std;

const int mx = 3 * 100000 + 5;

int zuo[mx], you[mx], father[mx], sz[mx], val[mx];
int cnt, head, change_;

int lr(int i){ // 是否为其父亲的右儿子
    return you[father[i]] == i ? 1 : 0;
}

void up(int i){
    if(!i) return;
    sz[i] = sz[zuo[i]] + sz[you[i]] + 1; // 必须+1
}

void rotato(int i){
    int f = father[i];
    int g = father[f];
    int son1 = lr(i);   // i 是 f 的右儿子?
    int son2 = lr(f);   // f 是 g 的右儿子?

    if(son1 == 1){ // 右旋祖父视角：i 上位，f 成为其左
        you[f] = zuo[i];
        if(zuo[i]) father[zuo[i]] = f;
        zuo[i] = f;
    }else{         // 左旋
        zuo[f] = you[i];
        if(you[i]) father[you[i]] = f;
        you[i] = f;
    }
    father[f] = i;
    father[i] = g;

    if(g){
        if(son2) you[g] = i;
        else     zuo[g] = i;
    }else{
        head = i;
    }
    up(f);
    up(i);
}

void splay(int i, int target){
    if(!i) return;
    while(father[i] != target){
        int f = father[i];
        int g = father[f];
        if(g != target){
            if(lr(i) == lr(f)) rotato(f); // zig-zig
            else               rotato(i); // zig-zag
        }
        rotato(i);
        // 这里不要写 g=father[g] 之类的鬼话；循环顶部现读即可
    }
    if(target == 0) head = i;
}

// 插入：cur 必须用引用，否则接不上
void add(int &cur, int f, int nums){
    if(cur == 0){
        cur = ++cnt;
        val[cur] = nums;
        father[cur] = f;
        zuo[cur] = you[cur] = 0;
        sz[cur] = 1;
        return;
    }
    if(nums < val[cur]) add(zuo[cur], cur, nums);
    else                add(you[cur], cur, nums);
    up(cur);
}

// lower_bound：返回第一个 val >= x 的结点下标；不存在返回 0
int lower_bound_idx(int cur, int x){
    int ans = 0;
    while(cur){
        if(val[cur] >= x){
            ans = cur;
            cur = zuo[cur];
        }else{
            cur = you[cur];
        }
    }
    return ans;
}

// 查询第 k 多（k-th largest），不存在返回 -1
int kth_largest(int k){
    if(k <= 0 || k > sz[head]) return -1;
    int cur = head;
    while(cur){
        int rsz = sz[you[cur]];
        if(k <= rsz){
            cur = you[cur];
        }else if(k == rsz + 1){
            return val[cur] + change_;
        }else{
            k -= rsz + 1;
            cur = zuo[cur];
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if(!(cin >> n >> m)) return 0;

    change_ = 0;
    head = 0;
    cnt = 0;
    int kicked = 0;

    for(int i = 0; i < n; i++){
        char ch; int k;
        cin >> ch >> k;
        if(ch == 'I'){
            if(k < m) continue;              // 初始低于下界直接忽略，不计入踢出人数
            k -= change_;
            add(head, 0, k);
            splay(cnt, 0);                   // 把新插入结点旋到根，保持树势头
        }else if(ch == 'A'){
            change_ += k;
        }else if(ch == 'S'){
            change_ -= k;
            int thr = m - change_;           // 要删除所有 val < thr 的结点
            if(!head) continue;

            int pos = lower_bound_idx(head, thr); // 第一个 >= thr
            if(pos == 0){
                // 全部都 < thr，整棵树清空
                kicked += sz[head];
                head = 0;
            }else{
                splay(pos, 0);               // pos 到根，根左子树全是 < thr
                kicked += sz[zuo[head]];
                if(zuo[head]){
                    // 断开并“丢弃”左子树
                    zuo[head] = 0;
                    up(head);
                }
            }
        }else if(ch == 'F'){
            int ans = kth_largest(k);
            cout << ans << '\n';
        }
    }
    cout << kicked << '\n';
    return 0;
}
