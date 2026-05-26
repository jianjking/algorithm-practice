#include<bits/stdc++.h>
using namespace std;

struct node{
   int v;
   int mnv;
   int mxv;
   int ans;
   int nums;
};

int lowbit(int i){
    return i & (-i);
}

void add(int i, vector<int>&tree, int v){
     int n = tree.size() - 1;
     while(i <= n){
        tree[i] = max(tree[i], v);
        i += lowbit(i);
     }
}

int query(int i, vector<int>&tree){
    int ans = 0;
    while(i > 0){
        ans = max(ans, tree[i]);
        i -= lowbit(i);
    }
    return ans;
}

void clear(int i, vector<int>&tree){
     int n = tree.size() - 1;
     while(i <= n){
        tree[i] = 0;
        i += lowbit(i);
     }
}

void cdq(int l, int r, vector<node>&arr, vector<int>&tree){
    if(l >= r) return;

    int mid = (l + r) / 2;

    cdq(l, mid, arr, tree);

    vector<node> larr(arr.begin() + l, arr.begin() + mid + 1);
    vector<node> rarr(arr.begin() + mid + 1, arr.begin() + r + 1);

    sort(larr.begin(), larr.end(), [](node a, node b){
        if(a.mxv != b.mxv) return a.mxv < b.mxv;
        return a.v < b.v;
    });

    sort(rarr.begin(), rarr.end(), [](node a, node b){
        return a.v < b.v;
    });

    int i = 0;

    for(int j = 0; j < (int)rarr.size(); j++){
        while(i < (int)larr.size() && larr[i].mxv <= rarr[j].v){
            add(larr[i].v, tree, larr[i].ans);
            i++;
        }

        int best = query(rarr[j].mnv, tree);

        if(best > 0){
            arr[rarr[j].nums].ans = max(arr[rarr[j].nums].ans, best + 1);
        }
    }

    for(int z = 0; z < i; z++){
        clear(larr[z].v, tree);
    }

    cdq(mid + 1, r, arr, tree);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<node> arr(n + 1);

    for(int i = 1; i <= n; i++){
        cin >> arr[i].v;
        arr[i].mnv = arr[i].v;
        arr[i].mxv = arr[i].v;
        arr[i].ans = 1;
        arr[i].nums = i;
    }

    for(int i = 0; i < m; i++){
        int pos, v;
        cin >> pos >> v;
        arr[pos].mnv = min(arr[pos].mnv, v);
        arr[pos].mxv = max(arr[pos].mxv, v);
    }

    vector<int> tree(100000 + 5, 0);

    cdq(1, n, arr, tree);

    int ans = 0;

    for(int i = 1; i <= n; i++){
        ans = max(ans, arr[i].ans);
    }

    cout << ans << '\n';

    return 0;
}