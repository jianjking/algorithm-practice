#include<bits/stdc++.h>
using namespace std;

const int maxn=5*1e4;
const int maxt=maxn*60;

int arr[maxn];
int root[maxn*4+5];
int zuo[maxt];
int you[maxt];
int diff[maxt];
int key[maxt];
int ci[maxt];
int sz[maxt];
// FIX: 重建收集数组开到 maxt（存“节点编号”）
int collect[maxt];

int top, fa, sign;
int cnt, h;

const double xi=0.7;
// 题面哨兵
const int NEG_INF = -2147483647;
const int POS_INF =  2147483647;

bool balance(int i){
    return (i==0)||(xi*diff[i] >= max(diff[zuo[i]], diff[you[i]]));
}
void up(int i){
    diff[i]=diff[zuo[i]] + diff[you[i]] + (ci[i]==0?0:1);
    sz[i]=sz[zuo[i]] + sz[you[i]] + ci[i];
}
int init(int num){
    key[++cnt]=num;
    ci[cnt]=1;
    diff[cnt]=1;
    zuo[cnt]=you[cnt]=0;     // FIX: 新节点儿子清零
    sz[cnt]=1;              // FIX: 新节点 size 立刻设为 1（否则父节点读到 0）
    return cnt;
}
int innerinsert(int i,int num,int f,int si){
    if(i==0){
        return init(num);
    }
    if(key[i]==num){
        ci[i]++;
    }else if(key[i]<num){
        you[i]=innerinsert(you[i],num,i,2);
    }else{
        zuo[i]=innerinsert(zuo[i],num,i,1);
    }
    up(i);
    if(!balance(i)){
        top=i; fa=f; sign=si;
    }
    return i;
}
void dfs(int i,int &num){
    if(i==0) return;
    dfs(zuo[i],num);
    if(ci[i]>0) collect[num++]=i; // 只收活节点“编号”
    dfs(you[i],num);
}
int rebuild(int l,int r){
    if(l>r) return 0;
    int midIdx = l + (r - l) / 2;
    int h = collect[midIdx];      // 节点编号
    zuo[h] = rebuild(l, midIdx - 1);
    you[h] = rebuild(midIdx + 1, r);
    up(h);
    return h;
}
void innerins(int i,int nums){
    top=fa=sign=0;
    root[i]=innerinsert(root[i],nums,0,0);
    if(top!=0){
        int num=0;
        dfs(top,num);
        if(fa==0){
            root[i]=rebuild(0,num-1);
        }else{
            if(sign==1) zuo[fa]=rebuild(0,num-1);
            else        you[fa]=rebuild(0,num-1);
        }
    }
}
void innerdelete(int i,int nums,int f,int si){
    if(i==0) return;          // 安全卫
    if(key[i]==nums){
        ci[i]--;              // 逻辑删除
    }else if(key[i]<nums){
        innerdelete(you[i],nums,i,2);
    }else{
        innerdelete(zuo[i],nums,i,1);
    }
    up(i);
    if(!balance(i)){
        top=i; fa=f; sign=si;
    }
}
void deletion(int i,int nums){
    top=fa=sign=0;
    innerdelete(root[i],nums,0,0);
    if(top!=0){
        int num=0;
        dfs(top,num);
        if(fa==0){
            root[i]=rebuild(0,num-1);
        }else{
            if(sign==1) zuo[fa]=rebuild(0,num-1);
            else        you[fa]=rebuild(0,num-1);
        }
    }
}
void add(int l,int r,int q,int v,int cur){
    innerins(cur,v);
    if(l==r) return;          // 叶子停
    int mid=l+(r-l)/2;
    if(q<=mid) add(l,mid,q,v,cur*2);
    else       add(mid+1,r,q,v,cur*2+1);
}
int innerquery(int cur,int num){
    if(cur==0) return 0;      // 空树
    if(key[cur]>=num){
        return innerquery(zuo[cur],num);
    }else{
        return sz[zuo[cur]] + ci[cur] + innerquery(you[cur],num);
    }
}
int query(int l,int r,int ql,int qr,int cur,int num){
    if(ql<=l && r<=qr) return innerquery(root[cur],num);
    int ans=0;
    int mid=l+(r-l)/2;
    if(ql<=mid) ans += query(l,mid,ql,qr,cur*2,num);
    if(qr>mid)  ans += query(mid+1,r,ql,qr,cur*2+1,num);
    return ans;
}
int querykth(int n,int ql,int qr,int k){
    int l=0, r=100000000;
    int ans=0;
    while(l<=r){
        int mid=l+(r-l)/2;
        // small(mid+1) >= k -> 缩右
        if(query(1,n,ql,qr,1,mid+1) >= k){
            ans=mid; r=mid-1;
        }else{
            l=mid+1;
        }
    }
    return ans;
}
void update(int l,int r,int cur,int target,int nums){
    deletion(cur,arr[target]);   // 传线段树结点编号
    innerins(cur,nums);
    if(l==r) return;
    int mid=l+(r-l)/2;
    if(target<=mid) update(l,mid,cur*2,target,nums);
    else            update(mid+1,r,cur*2+1,target,nums);
}
int innerpre(int cur,int nums){
    if(cur==0) return NEG_INF;
    if(key[cur]>=nums){
        return innerpre(zuo[cur],nums);
    }else{
        return max(key[cur],innerpre(you[cur],nums));
    }
}
int querypre(int l,int r,int ql,int qr,int cur,int nums){
    if(ql<=l && r<=qr) return innerpre(root[cur],nums);
    int ans=NEG_INF;
    int mid=l+(r-l)/2;
    if(ql<=mid) ans=max(ans,querypre(l,mid,ql,qr,cur*2,nums));
    if(qr>mid)  ans=max(ans,querypre(mid+1,r,ql,qr,cur*2+1,nums));
    return ans;
}
int innerback(int cur,int nums){
    if(cur==0) return POS_INF;
    if(key[cur]<=nums){
        return innerback(you[cur],nums);
    }else{
        return min(key[cur],innerback(zuo[cur],nums));
    }
}
int queryback(int l,int r,int ql,int qr,int cur,int nums){
    if(ql<=l && r<=qr) return innerback(root[cur],nums);
    int ans=POS_INF;
    int mid=l+(r-l)/2;
    if(ql<=mid) ans=min(ans,queryback(l,mid,ql,qr,cur*2,nums));
    if(qr>mid)  ans=min(ans,queryback(mid+1,r,ql,qr,cur*2+1,nums));
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x; cin>>x;
        arr[i]=x;
        add(1,n,i,x,1);
    }
    for(int i=0;i<m;i++){
        int op; cin>>op;
        if(op==1){
            int l,r,k; cin>>l>>r>>k;
            cout<<query(1,n,l,r,1,k)+1<<"\n";       // 排名=严格小于+1
        }else if(op==2){
            int l,r,k; cin>>l>>r>>k;
            cout<<querykth(n,l,r,k)<<"\n";
        }else if(op==3){
            int pos,k; cin>>pos>>k;
            update(1,n,1,pos,k);
            arr[pos]=k;
        }else if(op==4){
            int l,r,k; cin>>l>>r>>k;
            cout<<querypre(1,n,l,r,1,k)<<"\n";
        }else{
            int l,r,k; cin>>l>>r>>k;
            cout<<queryback(1,n,l,r,1,k)<<"\n";
        }
    }
    return 0;
}
