#include <bits/stdc++.h>
using namespace std;

const int mx = 1e6 + 5;

int zuo[mx], you[mx], prior[mx], val[mx];
bool vis[mx];
int sz[mx];
int head, cnt;

inline void up(int i){
    if(!i) return;
    sz[i] = sz[zuo[i]] + sz[you[i]] + 1;
}

inline void down(int i){
    if(!i || !vis[i]) return;
    swap(zuo[i], you[i]);
    vis[i] = false;
    if(zuo[i]) vis[zuo[i]] ^= 1;   // 别把懒翻到 0 号
    if(you[i]) vis[you[i]] ^= 1;
}

unsigned int tmp = 122477434;
inline int rmd(){
    tmp ^= (tmp >> 2);
    tmp ^= (tmp << 5);
    tmp ^= (tmp >> 3);
    return (int)tmp;
}

// 经典信箱法 split：
// 把 cur 按 rank 拆成 [前rank个 | 剩下]，
// 左树根写到 you[l]，右树根写到 zuo[r]
void split(int l, int r, int cur, int rank){
    if(cur == 0){
        you[l] = 0;
        zuo[r] = 0;
        return;
    }
    down(cur);
    if(sz[zuo[cur]] + 1 <= rank){
        // 当前根归左边
        you[l] = cur;                          // 左结果根写到 you[l] 信箱
        split(you[l], r, you[cur], rank - sz[zuo[cur]] - 1);
        up(cur);
    }else{
        // 当前根归右边
        zuo[r] = cur;                          // 右结果根写到 zuo[r] 信箱
        split(l, zuo[r], zuo[cur], rank);
        up(cur);
    }
}

int merge(int L, int R){
    if(L == 0 || R == 0) return L + R;
    if(prior[L] >= prior[R]){
        down(L);
        you[L] = merge(you[L], R);
        up(L);
        return L;
    }else{
        down(R);
        zuo[R] = merge(L, zuo[R]);
        up(R);
        return R;
    }
}

void reverse_seg(int L, int R){
    // 第一次：head -> A(you[0]) + Rest(zuo[0])
    split(0, 0, head, L - 1);
    int A = you[0];          // 左段根
    int Rest = zuo[0];       // 剩余根

    // 第二次：Rest -> B(you[0]) + C(zuo[0])
    split(0, 0, Rest, R - (L - 1));
    int B = you[0];          // 反转段根
    int C = zuo[0];          // 右段根

    if(B) vis[B] ^= 1;       // 标记翻转（注意 B 可能为 0）

    head = merge(merge(A, B), C);
}

void dfs(int cur){
    if(!cur) return;
    down(cur);
    dfs(zuo[cur]);
    cout << val[cur] << " ";
    dfs(you[cur]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    head = 0; cnt = 0;
    // 可选：清零一次（若在线评测多组数据要注意）
    // memset(zuo,0,sizeof(zuo));
    // memset(you,0,sizeof(you));
    // memset(prior,0,sizeof(prior));
    // memset(val,0,sizeof(val));
    // memset(vis,0,sizeof(vis));
    // memset(sz,0,sizeof(sz));

    for(int i = 1; i <= n; ++i){
        ++cnt;
        val[cnt] = i;
        sz[cnt] = 1;
        prior[cnt] = rmd();
        head = merge(head, cnt);
    }

    while(m--){
        int L, R;
        cin >> L >> R;
        reverse_seg(L, R);
    }

    dfs(head);
    cout << "\n";
    return 0;
}
