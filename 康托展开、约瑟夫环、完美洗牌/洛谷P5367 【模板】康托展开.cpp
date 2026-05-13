#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

int lowbit(int x){ return x & -x; }

void add(int i, int v, int n, vector<int>& tree){
    for(; i <= n; i += lowbit(i)) tree[i] += v;
}

int query(int i, vector<int>& tree){
    int ans = 0;
    for(; i > 0; i -= lowbit(i)) ans += tree[i];
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;

    vector<long long> fac(n, 1);
    for(int i = 2; i < n; i++){
        fac[i] = (fac[i-1] * 1LL * i) % mod;   // 防溢出
    }

    vector<int> tree(n+1, 0);
    for(int i = 1; i <= n; i++) add(i, 1, n, tree);

    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        // 如果输入是 0..n-1，请取消下一行注释：
        // ++arr[i];
    }

    long long ans = 0;
    for(int i = 0; i < n; i++){
        int x = query(arr[i]-1, tree);                       // 小于当前值的未用元素个数
        ans = (ans + (1LL * x % mod) * fac[n-1-i]) % mod;    // 防溢出
        add(arr[i], -1, n, tree);
    }
    cout << (ans+1) % mod << '\n';
    return 0;
}