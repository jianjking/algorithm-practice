#include<bits/stdc++.h>
using namespace std;
const int mx=5*1e6;
int zuo[mx];
int you[mx];
int head[mx];
int pre[mx];
int suf[mx];
int sum[mx];
int cnt;
int h;
vector<pair<int,int>>nums;

inline void up(int num){
    // 标准合并式（你原式多写了冗余项，不影响正确性，但这里给成标准更稳）
    pre[num]=max(pre[zuo[num]], sum[zuo[num]] + pre[you[num]]);
    suf[num]=max(suf[you[num]], sum[you[num]] + suf[zuo[num]]);
    sum[num]=sum[zuo[num]]+sum[you[num]];
}

int build(int l,int r){
    int num=++cnt;
    if(l==r){
        sum[num]=pre[num]=suf[num]=1;
        return num;
    }
    int mid=l+(r-l)/2;
    zuo[num]=build(l,mid);
    you[num]=build(mid+1,r);
    up(num);
    return num;
}

int update(int l,int r,int p,int cur){
    int num=++cnt;
    // FIX: 先拷贝旧孩子，再在对应方向递归
    zuo[num]=zuo[cur];
    you[num]=you[cur];
    if(l==r){
        sum[num]=pre[num]=suf[num]=-1;
        return num;
    }
    int mid=l+(r-l)/2;
    if(p<=mid){
        zuo[num]=update(l,mid,p,zuo[cur]); // FIX: 用zuo[cur]作为旧子树
    }else{
        you[num]=update(mid+1,r,p,you[cur]); // FIX: 用you[cur]作为旧子树
    }
    up(num);
    return num;
}

vector<int> query(int l,int r,int ql,int qr,int cur){
    if(ql<=l&&r<=qr){
        return {pre[cur],suf[cur],sum[cur]};
    }
    int mid=l+(r-l)/2;
    if(qr<=mid){
        return query(l,mid,ql,qr,zuo[cur]);
    }else if(ql>mid){
        return query(mid+1,r,ql,qr,you[cur]);
    }else{
        vector<int> left=query(l,mid,ql,qr,zuo[cur]);
        vector<int> right=query(mid+1,r,ql,qr,you[cur]);
        vector<int> res(3);
        // 标准合并
        res[0]=max(left[0], left[2]+right[0]);
        res[1]=max(right[1], right[2]+left[1]);
        res[2]=left[2]+right[2];
        return res;
    }
}

int result(int a,int b,int c,int d,int n){
    int l=0, r=n-1;
    while(l<=r){
        int mid=l+(r-l)/2;
        int sum=0;
        // FIX: 中间段必须是 [b+1, c-1]，避免与右前缀的c重叠
        if(b+1 < c){
            vector<int> tmp=query(0,n-1,b+1,c-1,head[mid]);
            sum = tmp[2];
        }
        // 左区间取最大后缀
        {
            vector<int> tmp=query(0,n-1,a,b,head[mid]);
            sum += tmp[1];
        }
        // 右区间取最大前缀
        {
            vector<int> tmp=query(0,n-1,c,d,head[mid]);
            sum += tmp[0];
        }
        // FIX: 判定应为 > 0（中位数 >= K 等价于“+1/-1 和”严格大于0）
        if(sum >= 0){
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    // FIX: 返回r（最后一个满足条件的位置）
    return nums[r].first;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    cnt=0;
    h=0;
    nums.assign(n,{0,0});
    for(int i=0;i<n;i++){
        cin>>nums[i].first;
        nums[i].second=i;
    }
    sort(nums.begin(),nums.end(),[&](pair<int,int>a,pair<int,int>b){
        return a.first<b.first;
    });
    head[h++]=build(0,n-1);
    for(int i=1;i<n;i++){
        int p=nums[i-1].second;
        head[i]=update(0,n-1,p,head[i-1]);
    }
    int q;
    cin>>q;
    int lastans=0;
    for(int i=0;i<q;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        vector<int> tmp;
        tmp.push_back((a+lastans)%n);
        tmp.push_back((b+lastans)%n);
        tmp.push_back((c+lastans)%n);
        tmp.push_back((d+lastans)%n);
        sort(tmp.begin(),tmp.end());
        a=tmp[0]; b=tmp[1]; c=tmp[2]; d=tmp[3];
        lastans=result(a,b,c,d,n);
        cout<<lastans<<"\n";
    }
    return 0;
}