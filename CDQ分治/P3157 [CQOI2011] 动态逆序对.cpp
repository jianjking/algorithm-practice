#include<bits/stdc++.h>
using namespace std;

struct str{
    int pos;
    int nums;
    int v;
    int time;
};

int n,m;

int lowbit(int i){
    return i&(-i);
}

void add(int i,vector<int>&tree,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
    }
}

int query(int i,vector<int>&tree){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
    }
    return ans;
}

void cdq(int l,int r,vector<str>&op,vector<long long>&del,vector<int>&tree,vector<str>&tmp){
    if(l>=r)return;

    int mid=(l+r)/2;

    cdq(l,mid,op,del,tree,tmp);
    cdq(mid+1,r,op,del,tree,tmp);

    // 统计：左边位置 < 当前删除位置，值 > 当前删除值
    int j=l;
    for(int i=mid+1;i<=r;i++){
        while(j<=mid && op[j].pos < op[i].pos){
            add(op[j].nums,tree,op[j].v);
            j++;
        }

        if(op[i].v==-1){
            del[op[i].time]+=query(n,tree)-query(op[i].nums,tree);
        }
    }

    for(int z=l;z<j;z++){
        add(op[z].nums,tree,-op[z].v);
    }

    // 统计：左边位置 > 当前删除位置，值 < 当前删除值
    j=mid;
    for(int i=r;i>mid;i--){
        while(j>=l && op[j].pos > op[i].pos){
            add(op[j].nums,tree,op[j].v);
            j--;
        }

        if(op[i].v==-1){
            del[op[i].time]+=query(op[i].nums-1,tree);
        }
    }

    for(int z=mid;z>j;z--){
        add(op[z].nums,tree,-op[z].v);
    }

    // 按 pos 归并排序，保证上一层 CDQ 可以双指针扫描
    int p=l,q=mid+1,k=l;

    while(p<=mid && q<=r){
        if(op[p].pos<=op[q].pos){
            tmp[k++]=op[p++];
        }
        else{
            tmp[k++]=op[q++];
        }
    }

    while(p<=mid){
        tmp[k++]=op[p++];
    }

    while(q<=r){
        tmp[k++]=op[q++];
    }

    for(int i=l;i<=r;i++){
        op[i]=tmp[i];
    }
}

int main(){
    cin>>n>>m;

    vector<int>a(n+1);
    vector<int>pos(n+1);
    vector<str>op(n+m);

    vector<int>tree(n+1,0);

    long long inv=0;

    for(int i=1;i<=n;i++){
        cin>>a[i];

        pos[a[i]]=i;

        // 计算初始逆序对数量
        inv+=i-1-query(a[i],tree);
        add(a[i],tree,1);

        op[i-1].pos=i;
        op[i-1].nums=a[i];
        op[i-1].v=1;
        op[i-1].time=0;
    }

    fill(tree.begin(),tree.end(),0);

    for(int i=1;i<=m;i++){
        int x;
        cin>>x;

        op[n+i-1].nums=x;
        op[n+i-1].pos=pos[x];
        op[n+i-1].v=-1;
        op[n+i-1].time=i;
    }

    vector<long long>del(m+1,0);
    vector<str>tmp(n+m);

    cdq(0,n+m-1,op,del,tree,tmp);

    long long cur=inv;

    for(int i=1;i<=m;i++){
        cout<<cur<<'\n';
        cur-=del[i];
    }

    return 0;
}