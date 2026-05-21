#include<bits/stdc++.h>
using namespace std;

struct str{
   int x;
   int y;
   int d;
};

const int MAXN=200000;
const int MAXQ=200000;
const int BIT=31;

int xian[BIT];

int father[MAXN+1];
int sz[MAXN+1];
int val[MAXN+1];

int rollback1[MAXN+1][2];
int rollback2[BIT+5];

int cur1=0;
int cur2=0;

array<int,4> op[MAXN+MAXQ+5];

bool query[MAXQ+1];
int X[MAXQ+1];
int Y[MAXQ+1];

int root(int f){
    while(f!=father[f]) f=father[f];
    return f;
}

int getxor(int f){
    int x=0;
    while(f!=father[f]){
        x^=val[f];
        f=father[f];
    }
    return x;
}

void insert(int nums,int&pushcnt){
    for(int i=BIT-1;i>=0;i--){
        if(((nums>>i)&1)==0) continue;

        if(xian[i]==0){
            xian[i]=nums;
            pushcnt++;
            rollback2[cur2++]=i;
            return;
        }

        nums^=xian[i];
    }
}

void unio(int u,int v,int d,int&pushcnt,int&uniocnt){
    int fu=root(u);
    int fv=root(v);

    int w=getxor(u)^getxor(v)^d;

    if(fu==fv){
        insert(w,pushcnt);
        return;
    }

    if(sz[fu]<sz[fv]){
        rollback1[cur1][0]=fv;
        rollback1[cur1][1]=fu;
        cur1++;
        uniocnt++;

        father[fu]=fv;
        sz[fv]+=sz[fu];
        val[fu]=w;
    }
    else{
        rollback1[cur1][0]=fu;
        rollback1[cur1][1]=fv;
        cur1++;
        uniocnt++;

        father[fv]=fu;
        sz[fu]+=sz[fv];
        val[fv]=w;
    }
}

void undo1(){
    cur1--;
    int f=rollback1[cur1][0];
    int son=rollback1[cur1][1];

    sz[f]-=sz[son];
    val[son]=0;
    father[son]=son;
}

void undo2(){
    cur2--;
    int pos=rollback2[cur2];
    xian[pos]=0;
}

void dfs(int l,int r,int nums,vector<vector<str>>&tree){
    int uniocnt=0;
    int pushcnt=0;

    for(auto&p:tree[nums]){
        unio(p.x,p.y,p.d,pushcnt,uniocnt);
    }

    if(l==r){
        if(query[l]){
            int x=X[l];
            int y=Y[l];

            int tmp=getxor(x)^getxor(y);

            for(int i=BIT-1;i>=0;i--){
                tmp=min(tmp,tmp^xian[i]);
            }

            cout<<tmp<<'\n';
        }
    }
    else{
        int mid=l+(r-l)/2;
        dfs(l,mid,2*nums,tree);
        dfs(mid+1,r,2*nums+1,tree);
    }

    for(int i=0;i<uniocnt;i++){
        undo1();
    }

    for(int i=0;i<pushcnt;i++){
        undo2();
    }
}

void addedge(str&tmp,int lt,int rt,int l,int r,int nums,vector<vector<str>>&tree){
    if(lt>rt) return;

    if(lt<=l&&r<=rt){
        tree[nums].push_back(tmp);
        return;
    }

    int mid=(l+r)/2;

    if(lt<=mid){
        addedge(tmp,lt,rt,l,mid,2*nums,tree);
    }

    if(rt>mid){
        addedge(tmp,lt,rt,mid+1,r,2*nums+1,tree);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m;

    int cnt=1;

    for(int i=1;i<=m;i++){
        int x,y,d;
        cin>>x>>y>>d;
        op[cnt]={x,y,d,0};
        cnt++;
    }

    int q;
    cin>>q;

    for(int i=1;i<=q;i++){
        int tmp;
        cin>>tmp;

        if(tmp==1){
            int x,y,d;
            cin>>x>>y>>d;
            op[cnt]={x,y,d,i};
            cnt++;
        }
        else if(tmp==2){
            int x,y;
            cin>>x>>y;
            op[cnt]={x,y,0,i};
            cnt++;
        }
        else{
            int x,y;
            cin>>x>>y;
            X[i]=x;
            Y[i]=y;
            query[i]=true;
        }
    }

    sort(op+1,op+cnt,[](const array<int,4>&a,const array<int,4>&b){
        if(a[0]!=b[0]) return a[0]<b[0];
        if(a[1]!=b[1]) return a[1]<b[1];
        return a[3]<b[3];
    });

    vector<vector<str>> tree(4*(q+1)+5);

    int l=1;

    while(l<cnt){
        int r=l;

        while(r+1<cnt&&op[r+1][0]==op[l][0]&&op[r+1][1]==op[l][1]){
            r++;
        }

        for(int i=l;i<=r;i+=2){
            int start=op[i][3];
            int end;

            if(i+1<=r){
                end=op[i+1][3]-1;
            }
            else{
                end=q;
            }

            str tmp={op[i][0],op[i][1],op[i][2]};
            addedge(tmp,start,end,0,q,1,tree);
        }

        l=r+1;
    }

    for(int i=1;i<=n;i++){
        father[i]=i;
        sz[i]=1;
        val[i]=0;
    }

    dfs(0,q,1,tree);

    return 0;
}