#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 998244353;
const ll INF_NEG = -(1LL << 60);

struct node{
    ll a,b,c,d,v;
    bool belongl;
    int num;
    ll dp,cnt;
};

ll lowbit(ll x){
    return x & -x;
}

void add(ll pos,ll val,ll ways,vector<ll>&tree,vector<ll>&cnt){
    int n = tree.size() - 1;
    while(pos <= n){
        if(tree[pos] < val){
            tree[pos] = val;
            cnt[pos] = ways;
        }
        else if(tree[pos] == val){
            cnt[pos] = (cnt[pos] + ways) % mod;
        }
        pos += lowbit(pos);
    }
}

pair<ll,ll> query(ll pos,vector<ll>&tree,vector<ll>&cnt){
    ll best = 0;
    ll ways = 0;

    while(pos > 0){
        if(tree[pos] > best){
            best = tree[pos];
            ways = cnt[pos];
        }
        else if(tree[pos] == best){
            ways = (ways + cnt[pos]) % mod;
        }
        pos -= lowbit(pos);
    }

    return {best,ways};
}

void clear(ll pos,vector<ll>&tree,vector<ll>&cnt){
    int n = tree.size() - 1;
    while(pos <= n){
        tree[pos] = INF_NEG;
        cnt[pos] = 0;
        pos += lowbit(pos);
    }
}

void cdq2(int l,int r,vector<node>&tmp,vector<ll>&tree,vector<ll>&cnt){
    if(l >= r) return;

    int mid = (l + r) / 2;

    cdq2(l,mid,tmp,tree,cnt);
    cdq2(mid+1,r,tmp,tree,cnt);

    int i = l;

    for(int j = mid + 1;j <= r;j++){
        while(i <= mid && tmp[i].c <= tmp[j].c){
            if(tmp[i].belongl){
                add(tmp[i].d,tmp[i].dp,tmp[i].cnt,tree,cnt);
            }
            i++;
        }

        if(!tmp[j].belongl){
            pair<ll,ll> t = query(tmp[j].d,tree,cnt);

            if(t.first + tmp[j].v > tmp[j].dp){
                tmp[j].dp = t.first + tmp[j].v;
                tmp[j].cnt = t.second % mod;
            }
            else if(t.first + tmp[j].v == tmp[j].dp){
                tmp[j].cnt = (tmp[j].cnt + t.second) % mod;
            }
        }
    }

    for(int z = l;z < i;z++){
        if(tmp[z].belongl){
            clear(tmp[z].d,tree,cnt);
        }
    }

    sort(tmp.begin()+l,tmp.begin()+r+1,[](const node&x,const node&y){
        if(x.c != y.c) return x.c < y.c;
        if(x.d != y.d) return x.d < y.d;
        if(x.belongl != y.belongl) return x.belongl > y.belongl;
        return x.num < y.num;
    });
}

void cdq1(int l,int r,vector<node>&nums,vector<ll>&tree,vector<ll>&cnt){
    if(l >= r) return;

    int mid = (l + r) / 2;

    cdq1(l,mid,nums,tree,cnt);

    vector<node>tmp;

    for(int i = l;i <= r;i++){
        nums[i].belongl = (i <= mid);
        tmp.push_back(nums[i]);
    }

    sort(tmp.begin(),tmp.end(),[](const node&x,const node&y){
        if(x.b != y.b) return x.b < y.b;
        if(x.belongl != y.belongl) return x.belongl > y.belongl;
        if(x.c != y.c) return x.c < y.c;
        if(x.d != y.d) return x.d < y.d;
        return x.num < y.num;
    });

    cdq2(0,tmp.size()-1,tmp,tree,cnt);

    for(auto &x:tmp){
        if(!x.belongl){
            nums[x.num].dp = x.dp;
            nums[x.num].cnt = x.cnt;
        }
    }

    cdq1(mid+1,r,nums,tree,cnt);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n,m;
    cin >> n >> m;

    vector<node>raw(n);

    for(int i = 0;i < n;i++){
        cin >> raw[i].a >> raw[i].b >> raw[i].c >> raw[i].d >> raw[i].v;
    }

    sort(raw.begin(),raw.end(),[](const node&x,const node&y){
        if(x.a != y.a) return x.a < y.a;
        if(x.b != y.b) return x.b < y.b;
        if(x.c != y.c) return x.c < y.c;
        if(x.d != y.d) return x.d < y.d;
        return false;
    });

    vector<node>nums(1);
    vector<ll>arr;

    for(auto x:raw){
        if(nums.size() > 1 &&
           nums.back().a == x.a &&
           nums.back().b == x.b &&
           nums.back().c == x.c &&
           nums.back().d == x.d){

            nums.back().v += x.v;
            nums.back().dp = nums.back().v;
        }
        else{
            x.dp = x.v;
            x.cnt = 1;
            nums.push_back(x);
            arr.push_back(x.d);
        }
    }

    sort(arr.begin(),arr.end());
    arr.erase(unique(arr.begin(),arr.end()),arr.end());

    int N = nums.size() - 1;

    for(int i = 1;i <= N;i++){
        nums[i].d = lower_bound(arr.begin(),arr.end(),nums[i].d) - arr.begin() + 1;
        nums[i].num = i;
    }

    vector<ll>tree(arr.size()+1,INF_NEG);
    vector<ll>cnt(arr.size()+1,0);

    cdq1(1,N,nums,tree,cnt);

    ll mx = 0;
    ll ans = 0;

    for(int i = 1;i <= N;i++){
        mx = max(mx,nums[i].dp);
    }

    for(int i = 1;i <= N;i++){
        if(nums[i].dp == mx){
            ans = (ans + nums[i].cnt) % mod;
        }
    }

    cout << mx << '\n' << ans << '\n';

    return 0;
}