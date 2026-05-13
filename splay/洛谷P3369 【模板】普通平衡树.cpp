#include<bits/stdc++.h>
using namespace std;

const int mx=1e5+5;
int zuo[mx];
int you[mx];
int key[mx];
int father[mx];
int sz[mx];
int head;
int cnt;

int lr(int i){
    return you[father[i]]==i?1:0;
}

void up(int i){
    // FIX: 用子树规模而不是儿子下标相加
    sz[i] = 1;
    if(zuo[i]) sz[i] += sz[zuo[i]];
    if(you[i]) sz[i] += sz[you[i]];
}

void rotato(int i){
    // 单旋：i 绕着父亲 f 旋转
    int f = father[i];
    int g = father[f];
    int son1 = lr(i);     // i 是 f 的右儿子(1)还是左儿子(0)
    int son2 = (g ? lr(f) : -1); // f 相对 g 的方向（若 g 存在）

    // 1) 让 i 接到 g 底下
    if(g){
        if(son2==1) you[g]=i; else zuo[g]=i;
    }else{
        head = i; // i 成为新根
    }
    father[i]=g;

    // 2) 在 (i,f) 之间移动中间子树 B，并把 f 接到 i 上
    if(son1==0){
        // i 是 f 的左儿子：右旋 f
        zuo[f] = you[i];
        if(you[i]) father[you[i]] = f;
        you[i] = f;
        father[f] = i;
    }else{
        // i 是 f 的右儿子：左旋 f
        you[f] = zuo[i];
        if(zuo[i]) father[zuo[i]] = f;
        zuo[i] = f;
        father[f] = i;
    }

    // 3) 回收信息
    up(f);
    up(i);
}

void splay(int i,int target){
    // 把 i 旋到 target 的儿子；target=0 则旋到根
    while(father[i] != target){
        int f = father[i];
        int g = father[f];
        if(g != target){
            // zig-zig：同向，先转父
            if(lr(i) == lr(f)) rotato(f);
            else               rotato(i); // zig-zag：异向，先转自己
        }
        rotato(i);
    }
    if(target==0){
        head = i;
        father[head]=0;
    }
}

void add(int cur_ignored,int f_ignored,int x){
    // FIX: 不改签名；真正用 head 全局插
    if(head==0){
        key[++cnt]=x;
        sz[cnt]=1;
        father[cnt]=0;
        zuo[cnt]=you[cnt]=0;
        head=cnt;
        return;
    }
    int p=0, cur=head;
    while(cur){
        p=cur;
        if(x < key[cur]) cur=zuo[cur];
        else             cur=you[cur];
    }
    key[++cnt]=x;
    sz[cnt]=1;
    father[cnt]=p;
    zuo[cnt]=you[cnt]=0;
    if(x < key[p]) zuo[p]=cnt; else you[p]=cnt;
    splay(cnt,0);
}

// 返回严格小于 nums 的数量
int rankd(int cur_ignored,int nums){
    int ans=0, cur=head;
    while(cur){
        if(nums <= key[cur]){
            cur=zuo[cur];
        }else{
            ans += (zuo[cur]?sz[zuo[cur]]:0) + 1;
            cur=you[cur];
        }
    }
    return ans;
}

// 找到第 rank 小（1-index），返回节点编号，找不到返回 0
int finding(int cur_ignored,int rank){
    if(head==0) return 0;
    if(rank<=0 || rank>sz[head]) return 0;
    int cur=head;
    while(cur){
        int ls = zuo[cur]?sz[zuo[cur]]:0;
        if(rank<=ls) cur=zuo[cur];
        else if(rank==ls+1) return cur;
        else { rank-=ls+1; cur=you[cur]; }
    }
    return 0;
}

void deletion(int nums){
    if(head==0) return;
    // 用 rank 找到等于 nums 的第一个位置
    int k = rankd(head, nums) + 1;
    int i = finding(head, k);
    if(!i || key[i]!=nums) return; // 不存在
    splay(i,0); // 要删的点到根

    int L = zuo[i], R = you[i];
    if(!L && !R){ head=0; return; }
    if(!L){ father[R]=0; head=R; return; }
    if(!R){ father[L]=0; head=L; return; }

    // 两边都有：把 L 的最大点旋到根，再把 R 接到根的右侧
    father[L]=0; head=L;
    int t=head;
    while(you[t]) t=you[t];
    splay(t,0);           // t 没有右儿子
    you[t]=R; father[R]=t;
    up(t);
}

void rankmx(int cur,int nums,int&ans){
    // 前驱：严格小于 nums 的最大值
    int res = INT_MIN, pos = 0;
    int c = head;
    while(c){
        if(key[c] < nums){ res=key[c]; pos=c; c=you[c]; }
        else c=zuo[c];
    }
    if(pos) splay(pos,0);
    ans = res;
}

void rankmn(int cur,int nums,int&ans){
    // 后继：严格大于 nums 的最小值
    int res = INT_MAX, pos = 0;
    int c=head;
    while(c){
        if(key[c] > nums){ res=key[c]; pos=c; c=zuo[c]; }
        else c=you[c];
    }
    if(pos) splay(pos,0);
    ans = res;
}

int main(){
    head=0;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cnt=0;

    int n;
    if(!(cin>>n)) return 0;
    for(int i=0;i<n;i++){
        int op,x;
        cin>>op>>x;
        if(op==1){
            add(head,0,x);                 // 保持你的接口
        }
        else if(op==2){
            deletion(x);
        }
        else if(op==3){
            int ans = rankd(head,x) + 1;   // rank：严格小于数量+1
            cout<<ans<<'\n';
            //（可选）把等于 x 的节点旋到根，存在就转
            int k = rankd(head,x)+1;
            int id = finding(head,k);
            if(id && key[id]==x) splay(id,0);
        }
        else if(op==4){
            int id = finding(head,x);      // 第 x 小的“值”
            cout<<(id?key[id]:0)<<'\n';
            if(id) splay(id,0);
        }
        else if(op==5){
            int ans=INT_MIN;
            rankmx(head,x,ans);
            cout<<ans<<'\n';
        }
        else{
            int ans=INT_MAX;
            rankmn(head,x,ans);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
