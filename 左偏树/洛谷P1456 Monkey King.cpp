#include<bits/stdc++.h>
using namespace std;
const int mx=1e6+10;
int zuo[mx];
int you[mx];
int nums[mx];
int father[mx];   // 同时作为左偏堆父指针 + 并查集父
int dist[mx];     // 左偏堆 NPL

int root(int i){  // 并查集 find：沿堆父到堆根
   // 迭代+压缩
   int x=i;
   while(father[x]!=x) x=father[x];
   while(father[i]!=i){ int p=father[i]; father[i]=x; i=p; }
   return x;
}

// 左偏堆合并（最大堆；值相等时选编号小的做根稳定）
int merge(int a,int b){
    if(a==0||b==0) return a+b;
    if(nums[a] < nums[b] || (nums[a]==nums[b] && a>b)) swap(a,b);
    you[a]=merge(you[a],b);
    if(dist[zuo[a]] < dist[you[a]]) swap(zuo[a],you[a]);
    dist[a]=dist[you[a]]+1;
    // 把两个孩子的 father 都指回 a（堆父 == DSU父）
    if(zuo[a]) father[zuo[a]]=a;
    if(you[a]) father[you[a]]=a;
    return a;
}

// 弹出堆顶 i，返回“去顶后”的新堆根
int remove(int i){
    // 让左右子堆的父先指回自己（断开 i）
    if(zuo[i]) father[zuo[i]]=zuo[i];
    if(you[i]) father[you[i]]=you[i];
    int s=merge(zuo[i],you[i]);
    // 把 i 的指针清干净
    zuo[i]=you[i]=0;
    dist[i]=0;
    // 新根 s 作为 i 的父（便于把 i 放回去时再 merge）
    father[i]=s ? s : i;
    return s;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    while (cin>>n){
        for(int i=1;i<=n;i++) cin>>nums[i];

        // 初始化
        dist[0] = -1;
        for(int i=1;i<=n;i++){
            zuo[i]=you[i]=0;
            dist[i]=0;
            father[i]=i;  // 每只猴子初始是单节点堆的堆根，也是集合代表
        }

        int m; cin>>m;
        while(m--){
            int x,y; cin>>x>>y;
            int rx=root(x), ry=root(y);
            if(rx==ry){
                cout<<-1<<"\n";
                continue;
            }
            // 各自弹顶
            int sx=remove(rx);
            int sy=remove(ry);
            // 顶点战力减半
            nums[rx] >>= 1;
            nums[ry] >>= 1;
            // 把被弹的顶点放回各自堆
            father[rx]=rx; // 放回前先把自己当根，避免沿旧父链跑飞
            father[ry]=ry;
            int hx = merge(sx, rx);
            father[hx]=hx;
            int hy = merge(sy, ry);
            father[hy]=hy;
            // 两堆合并
            int H = merge(hx, hy);
            father[H]=H;

            cout<<nums[H]<<"\n";
        }
    }
    return 0;
}
