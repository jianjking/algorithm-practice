#include<bits/stdc++.h>
using namespace std;
long long x,y;
long long multiply(long long a,long long b,long long mod){
    a=(a%mod+mod)%mod;
    b=(b%mod+mod)%mod;
    return (unsigned __int128)a*b%mod;
}
long long exgcd(long long a,long long b){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    long long g=exgcd(b,a%b);
    long long tmpx=x;
    long long tmpy=y;
    x=tmpy;
    y=tmpx-a/b*tmpy;
    return g;
}
int main(){
    int n;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    long long lcm,tail;
    lcm=1;
    tail=0;
    for(int i=0;i<n;i++){
        long long a,b;
        cin>>a>>b;
        long long g=exgcd(lcm,a);
        if((b-tail)%g!=0){
            cout<<-1<<'\n';
            return 0;
        }
        x=multiply((b-tail)/g,x,a/g);
        if(x<0)x+=a/g;
        long long tmp=lcm*a/g;
        tail=(tail+multiply(lcm,x,tmp))%tmp;
        lcm=tmp;
        }
       cout<<(tail%lcm+lcm)%lcm<<'\n';
       return 0;
}