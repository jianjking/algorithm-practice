#include<bits/stdc++.h>
using namespace std;

int lowbit(int i){
    return i & (-i);
}

void addnums(vector<int>&tree,int i,int val){
    int n = tree.size() - 1;
    while(i <= n){
        tree[i] += val;
        i += lowbit(i);
    }
}

int query(int i,vector<int>&tree){
    int ans = 0;
    while(i > 0){
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

void dfs(int ql,int qr,int nl,int nr,
         vector<int>&q,
         vector<int>&l,
         vector<int>&r,
         vector<int>&k,
         vector<int>&tree,
         vector<int>&ans,
         vector<pair<int,int>>&nums){

    if(ql > qr) return;

    if(nl == nr){
        for(int i = ql; i <= qr; i++){
            ans[q[i]] = nums[nl].first;
        }
        return;
    }

    int mid = (nl + nr) / 2;

    for(int i = nl; i <= mid; i++){
        addnums(tree, nums[i].second, 1);
    }

    vector<int> qql;
    vector<int> qqr;

    for(int i = ql; i <= qr; i++){
        int qq = q[i];
        int cur = query(r[qq], tree) - query(l[qq] - 1, tree);

        if(cur >= k[qq]){
            qql.push_back(qq);
        }
        else{
            k[qq] -= cur;
            qqr.push_back(qq);
        }
    }

    int pos = ql;
    for(auto id : qql){
        q[pos++] = id;
    }
    for(auto id : qqr){
        q[pos++] = id;
    }

    for(int i = nl; i <= mid; i++){
        addnums(tree, nums[i].second, -1);
    }

    int lsiz = qql.size();

    dfs(ql, ql + lsiz - 1, nl, mid, q, l, r, k, tree, ans, nums);
    dfs(ql + lsiz, qr, mid + 1, nr, q, l, r, k, tree, ans, nums);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin >> n >> m;

    vector<pair<int,int>> nums(n + 1);

    for(int i = 1; i <= n; i++){
        cin >> nums[i].first;
        nums[i].second = i;
    }

    vector<int> q(m + 1);
    vector<int> l(m + 1);
    vector<int> r(m + 1);
    vector<int> k(m + 1);

    for(int i = 1; i <= m; i++){
        cin >> l[i] >> r[i] >> k[i];
        q[i] = i;
    }

    sort(nums.begin() + 1, nums.end(), [](pair<int,int> a, pair<int,int> b){
        if(a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });

    vector<int> tree(n + 1, 0);
    vector<int> ans(m + 1, 0);

    dfs(1, m, 1, n, q, l, r, k, tree, ans, nums);

    for(int i = 1; i <= m; i++){
        cout << ans[i] << '\n';
    }

    return 0;
}