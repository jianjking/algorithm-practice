#include<bits/stdc++.h>
using namespace std;

const int mx=1e5+5;

int zuo[mx], you[mx], dist_[mx], sz[mx];
int parent_[mx], cost[mx], ability[mx];
int rt[mx];                 // 每个节点作为管理者时的堆根
long long sum_[mx];         // 当前堆的总薪水
vector<int> child[mx];

inline int heapsz(int x){ return x ? sz[x] : 0; }
// 大顶堆：cost 高者为堆顶；相等时编号小者优先保留
inline bool worse(int a,int b){
    if(cost[a]!=cost[b]) return cost[a]<cost[b];
    return a>b;
}
int merge_(int a,int b){
    if(!a||!b) return a?a:b;
    if(worse(a,b)) swap(a,b);
    you[a]=merge_(you[a],b);
    if(dist_[zuo[a]]<dist_[you[a]]) swap(zuo[a],you[a]);
    dist_[a]=dist_[you[a]]+1;
    sz[a]=sz[zuo[a]]+sz[you[a]]+1;
    return a;
}
int pop_(int x){ // 删除堆顶 x
    int a=zuo[x], b=you[x];
    zuo[x]=you[x]=0;
    return merge_(a,b);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; long long M;
    if(!(cin>>n>>M)) return 0;
    for(int i=1;i<=n;i++){
        cin>>parent_[i]>>cost[i]>>ability[i];
        if(parent_[i]>=1) child[parent_[i]].push_back(i);
    }

    dist_[0]=-1; sz[0]=0;
    long long ans=0;

    // 倒序：先处理孩子再处理父亲
    for(int i=n;i>=1;i--){
        // 初始化把 i 自己放入堆
        zuo[i]=you[i]=0;
        dist_[i]=0;
        sz[i]=1;
        rt[i]=i;
        sum_[i]=cost[i];

        // 合并所有孩子的堆
        for(int v:child[i]){
            rt[i]=merge_(rt[i], rt[v]);
            sum_[i]+=sum_[v];
        }

        // 超预算：不停弹出最大薪水
        while(sum_[i]>M && rt[i]){
            int top=rt[i];
            sum_[i]-=cost[top];
            rt[i]=pop_(rt[i]);
        }

        // 更新答案：领导力 * 选中人数
        ans=max(ans, 1LL*ability[i]*heapsz(rt[i]));
    }

    cout<<ans<<"\n";
    return 0;
}