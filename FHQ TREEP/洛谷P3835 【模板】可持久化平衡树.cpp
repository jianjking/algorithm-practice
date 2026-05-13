#include <bits/stdc++.h>
using namespace std;

const int mxc = 5*1e5 + 5;
const int mx  = mxc*50;

int head[mxc];
int zuo[mx], you[mx], val[mx], prior[mx], sz[mx];
int cnt = 0;
int cnth = 0;
unsigned int xi = 12345632;

int rdm(){
    xi^=xi>>5;
    xi^=xi<<3;
    xi^=xi>>2;
    return (int)xi;
}

int copy_node(int i){
    int k = ++cnt;
    val[k]=val[i];
    zuo[k]=zuo[i];
    you[k]=you[i];
    prior[k]=prior[i];
    sz[k]=sz[i];
    return k;
}

inline void up(int i){
    if(!i) return;
    sz[i]=sz[zuo[i]]+sz[you[i]]+1;
}

// 信箱法：you[l] 接 <=x 的根；zuo[r] 接 >x 的根
void split(int l,int r,int cur,int x){
    if(cur==0){
        you[l]=0;
        zuo[r]=0;
        return;
    }
    if(val[cur]<=x){
        int t = you[l] = copy_node(cur);
        split(you[l], r, you[cur], x);
        up(t);
    }else{
        int t = zuo[r] = copy_node(cur);
        split(l, zuo[r], zuo[cur], x);
        up(t);
    }
}

int merge(int L,int R){
    if(L==0 || R==0) return L+R;
    if(prior[L]>=prior[R]){
        int t = L = copy_node(L);
        you[L]=merge(you[L],R);
        up(t);
        return L;
    }else{
        int t = R = copy_node(R);
        zuo[R]=merge(L,zuo[R]);
        up(t);
        return R;
    }
}

int add(int h,int x){
    split(0,0,h,x);                 // you[0] <=x, zuo[0] >x
    int nd = ++cnt;
    val[nd]=x;
    zuo[nd]=you[nd]=0;
    sz[nd]=1;
    prior[nd]=rdm();
    int L = you[0], R = zuo[0];
    you[0]=zuo[0]=0;
    return merge(merge(L,nd),R);
}

int deletion(int h,int x){
    split(0,0,h,x);                 // A=you[0] (<=x), C=zuo[0] (>x)
    int A = you[0], C = zuo[0];
    you[0]=zuo[0]=0;

    split(0,0,A,x-1);               // L=you[0] (<=x-1), B=zuo[0] (==x)
    int L = you[0], B = zuo[0];
    you[0]=zuo[0]=0;

    if(B){
        int B2 = merge(zuo[B], you[B]); // 删掉一个（根）
        return merge(merge(L,B2),C);
    }else{
        return merge(merge(L,B),C);     // 没有 x，忽略删除
    }
}

int queryrank(int cur,int x){
    if(cur==0) return 0;
    if(val[cur]<x){
        return sz[zuo[cur]]+1+queryrank(you[cur],x);
    }else{
        return queryrank(zuo[cur],x);
    }
}

int querypai(int cur,int rank){
    if(cur==0) return 0; // 调用者保证合法；防御返回0
    int lsz = sz[zuo[cur]];
    if(rank<=lsz) return querypai(zuo[cur],rank);
    if(rank==lsz+1) return val[cur];
    return querypai(you[cur],rank-lsz-1);
}

void querypre_dfs(int cur,int x,int&ans){
    if(cur==0) return;
    if(val[cur]<x){
        ans=max(ans,val[cur]);
        querypre_dfs(you[cur],x,ans);
    }else{
        querypre_dfs(zuo[cur],x,ans);
    }
}

void queryback_dfs(int cur,int x,int&ans){
    if(cur==0) return;
    if(val[cur]>x){
        ans=min(ans,val[cur]);
        queryback_dfs(zuo[cur],x,ans);
    }else{
        queryback_dfs(you[cur],x,ans);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin>>n)) return 0;

    head[0]=0; cnth=0;

    for(int i=1;i<=n;i++){
        int v,op,x;
        cin>>v>>op>>x;
        if(op==1){
            head[++cnth]=add(head[v],x);
        }else if(op==2){
            head[++cnth]=deletion(head[v],x);
        }else if(op==3){
            head[++cnth]=head[v];
            cout<<queryrank(head[v],x)+1<<'\n';
        }else if(op==4){
            head[++cnth]=head[v];
            cout<<querypai(head[v],x)<<'\n';
        }else if(op==5){
            head[++cnth]=head[v];
            int ans=INT_MIN+1;
            querypre_dfs(head[v],x,ans);
            cout<<ans<<'\n';
        }else{ // op==6
            head[++cnth]=head[v];
            int ans=INT_MAX-1;
            queryback_dfs(head[v],x,ans);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
