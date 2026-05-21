#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXS = MAXN << 2;
const int MAXT = 2000005;
const int MAXE = 3000005;
const int BIT = 16;

struct Product{
    int s;
    int v;
};

int n,m,tday;

int a[MAXN];
int op[MAXN];
int S[MAXN],V[MAXN];
int L[MAXN],R[MAXN],X[MAXN],D[MAXN];
int tim[MAXN];

int root[MAXN];
int tree[MAXT][2];
int pass[MAXT];
int cntt;

int headp[MAXS],nxtp[MAXE],pid[MAXE],cntp;
int headb[MAXS],nxtb[MAXE],bid[MAXE],cntb;

Product pro[MAXN];
int ans[MAXN];

bool cmp(Product a,Product b){
    return a.s<b.s;
}

int insert(int num,int r){
    int rt=++cntt;
    int pre=rt;

    tree[rt][0]=tree[r][0];
    tree[rt][1]=tree[r][1];
    pass[rt]=pass[r]+1;

    for(int i=BIT;i>=0;i--){
        int path=(num>>i)&1;

        r=tree[r][path];

        int cur=++cntt;
        tree[cur][0]=tree[r][0];
        tree[cur][1]=tree[r][1];
        pass[cur]=pass[r]+1;

        tree[pre][path]=cur;
        pre=cur;
    }

    return rt;
}

int query(int num,int u,int v){
    int res=0;

    for(int i=BIT;i>=0;i--){
        int path=(num>>i)&1;
        int best=path^1;

        if(pass[tree[v][best]]>pass[tree[u][best]]){
            res|=(1<<i);
            u=tree[u][best];
            v=tree[v][best];
        }
        else{
            u=tree[u][path];
            v=tree[v][path];
        }
    }

    return res;
}

void addp(int i,int id){
    nxtp[++cntp]=headp[i];
    pid[cntp]=id;
    headp[i]=cntp;
}

void addb(int i,int id){
    nxtb[++cntb]=headb[i];
    bid[cntb]=id;
    headb[i]=cntb;
}

void addProduct(int pos,int id,int l,int r,int i){
    addp(i,id);

    if(l==r)return;

    int mid=(l+r)/2;

    if(pos<=mid){
        addProduct(pos,id,l,mid,i*2);
    }
    else{
        addProduct(pos,id,mid+1,r,i*2+1);
    }
}

void addBuy(int ql,int qr,int id,int l,int r,int i){
    if(ql<=l&&r<=qr){
        addb(i,id);
        return;
    }

    int mid=(l+r)/2;

    if(ql<=mid){
        addBuy(ql,qr,id,l,mid,i*2);
    }

    if(qr>mid){
        addBuy(ql,qr,id,mid+1,r,i*2+1);
    }
}

int lower_pos(int siz,int num){
    int l=1,r=siz;
    int res=siz+1;

    while(l<=r){
        int mid=(l+r)/2;

        if(pro[mid].s>=num){
            res=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }

    return res;
}

int upper_pos(int siz,int num){
    int l=1,r=siz;
    int res=0;

    while(l<=r){
        int mid=(l+r)/2;

        if(pro[mid].s<=num){
            res=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }

    return res;
}

void dfs(int l,int r,int i){
    int cnt=0;

    for(int e=headp[i];e;e=nxtp[e]){
        int id=pid[e];
        pro[++cnt]={S[id],V[id]};
    }

    sort(pro+1,pro+cnt+1,cmp);

    cntt=0;
    root[0]=0;

    for(int j=1;j<=cnt;j++){
        root[j]=insert(pro[j].v,root[j-1]);
    }

    for(int e=headb[i];e;e=nxtb[e]){
        int id=bid[e];

        int pre=lower_pos(cnt,L[id])-1;
        int post=upper_pos(cnt,R[id]);

        if(pre<post){
            ans[id]=max(ans[id],query(X[id],root[pre],root[post]));
        }
    }

    if(l==r)return;

    int mid=(l+r)/2;

    dfs(l,mid,i*2);
    dfs(mid+1,r,i*2+1);
}

void prepare(){
    cntt=0;
    root[0]=0;

    for(int i=1;i<=n;i++){
        root[i]=insert(a[i],root[i-1]);
    }

    for(int i=1;i<=m;i++){
        if(op[i]==0){
            addProduct(tim[i],i,1,tday,1);
        }
        else{
            ans[i]=query(X[i],root[L[i]-1],root[R[i]]);

            int st=max(tim[i]-D[i]+1,1);

            if(st<=tim[i]){
                addBuy(st,tim[i],i,1,tday,1);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;

    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    for(int i=1;i<=m;i++){
        cin>>op[i];

        if(op[i]==0){
            tday++;
            cin>>S[i]>>V[i];
        }
        else{
            cin>>L[i]>>R[i]>>X[i]>>D[i];
        }

        tim[i]=tday;
    }

    prepare();

    if(tday>0){
        dfs(1,tday,1);
    }

    for(int i=1;i<=m;i++){
        if(op[i]==1){
            cout<<ans[i]<<'\n';
        }
    }

    return 0;
}