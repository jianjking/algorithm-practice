#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
struct node{
  int l;
  int r;
  int gcd;
};
int main(){
   vector<node>pre;
   int n;
   cin>>n;
   long long ans=0;
   vector<int>nums(n+1);
   for(int i=1;i<=n;i++){
      cin>>nums[i];
   }
   for(int r=1;r<=n;r++){
     for(auto&p:pre){
            p.gcd=gcd(p.gcd,nums[r]);
     }
     int i=0;
     int j=0;
     pre.push_back({r,r,nums[r]});
      vector<node>cur;
     while(i<pre.size()){
        int lt=pre[i].l;
        int lr=pre[i].r;
        while(j+1<pre.size()&&pre[j+1].gcd==pre[i].gcd){
            lr=pre[j+1].r;
            j++;
        }
        cur.push_back({lt,lr,pre[i].gcd});
        i=j+1;
        j=i;
     }
     pre=cur;
    for(int i=0;i<pre.size();i++){
    long long A=pre[i].l+pre[i].r; // 修改：先拆开算，避免一整坨乘法爆 long long
    long long B=pre[i].r-pre[i].l+1; // 修改：左端点个数

    if(A%2==0)A/=2; // 修改：先把 /2 消掉，再取模乘法
    else B/=2;      // 修改：因为 A*B 一定是偶数

    long long add=A%mod; // 修改：每乘一步都取模
    add=add*(B%mod)%mod;
    add=add*(pre[i].gcd%mod)%mod;
    add=add*(r%mod)%mod;

    ans=(ans+add)%mod; // 修改：加入答案
}
   }
   cout<<ans<<'\n';
}