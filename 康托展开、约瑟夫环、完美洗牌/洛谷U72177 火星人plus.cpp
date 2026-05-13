#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void build(int l,int r,int v,int nums,vector<int>&sum){
    if(l==r){ sum[nums]=v; return; }
    int mid=l+(r-l)/2;
    build(l,mid,v,2*nums,sum);
    build(mid+1,r,v,2*nums+1,sum);
    sum[nums]=sum[2*nums]+sum[2*nums+1];
}
int query(int l,int r,int x,int y,int nums,vector<int>&sum){
    if(l<=x && r>=y) return sum[nums];
    int mid = x + (y-x)/2;
    int ans = 0;
    if(l<=mid)   ans += query(l, r, x,     mid, 2*nums,   sum);
    if(r>=mid+1) ans += query(l, r, mid+1, y,   2*nums+1, sum);
    return ans;
}
void update(int target,int l,int r,int nums,vector<int>&sum){
    if(l==r){ sum[nums]=0; return; }
    int mid=l+(r-l)/2;
    if(target<=mid) update(target,l,mid,2*nums,sum);
    else            update(target,mid+1,r,2*nums+1,sum);
    sum[nums]=sum[2*nums]+sum[2*nums+1];
}

// target 是 0-based：选当前可用集合中的第 target 个
void pick(ll target,int i,int l,int r,int nums,vector<int>&sum,vector<int>&arr){
    if(l==r){
        arr[i]=l;
        sum[nums]=0; // 取走
        return;
    }
    int mid=l+(r-l)/2;
    int leftCnt = sum[2*nums];
    if(target < leftCnt){
        pick(target, i, l, mid, 2*nums, sum, arr);
    }else{
        pick(target - leftCnt, i, mid+1, r, 2*nums+1, sum, arr);
    }
    sum[nums]=sum[2*nums]+sum[2*nums+1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll m;                         // M 必须用 long long
    cin >> n >> m;

    vector<int> sum(4*n+4, 0);
    build(1, n, 1, 1, sum);

    vector<int> arr(n);
    for(int i=0;i<n;i++) cin >> arr[i];

    // 1) 计算 Lehmer 数位 d[i]（用 long long 保存，避免后续 +m 溢出）
    vector<ll> d(n, 0);
    for(int i=0;i<n;i++){
        int v = arr[i];
        if(v==1) d[i]=0;
        else     d[i]=query(1, v-1, 1, n, 1, sum);
        update(v, 1, n, 1, sum);  // 把 v 从剩余集合移除
    }

    // 2) 阶乘进位制加 m，从末位开始向高位进位，避免 i-1 越界
    d[n-1] += m;
    for(int i=n-1;i>=1;i--){
        ll base = (ll)(n - i);    // 第 i 位的进制是 n-i
        d[i-1] += d[i] / base;
        d[i]   %= base;
    }
    d[0] %= n; // 题目保证不越界，这里做个保护

    // 3) 用“第 d[i] 个未取走的数”重建排列 —— 注意要从左到右！
    build(1, n, 1, 1, sum);
    for(int i=0;i<n;i++){
        pick(d[i], i, 1, n, 1, sum, arr);
    }

    for(int i=0;i<n;i++){
        if(i) cout << ' ';
        cout << arr[i];
    }
    cout << '\n';
    return 0;
}
