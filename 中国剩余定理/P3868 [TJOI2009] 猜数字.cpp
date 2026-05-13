#include<bits/stdc++.h>
using namespace std;
long long x,y;
long long multiply(long long a,long long b,long long mod){
    a=(a%mod+mod)%mod;
    b=(b%mod+mod)%mod;
    return (unsigned __int128)a*b%mod;
}
void exgcd(long long a,long long b){
    if(b==0){
        x=1;
        y=0;
        return ;
    }
    exgcd(b,a%b);
    long long tmpx=x;
    long long tmpy=y;
    x=tmpy;
    y=tmpx-a/b*tmpy;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k;
    cin>>k;
    long long lcm=1;
    vector<long long>a(k);
    vector<long long>b(k);
     for(int i=0;i<k;i++){
        cin>>b[i];
       
    }
    for(int i=0;i<k;i++){
        cin>>a[i];
        lcm=lcm*a[i];
    }
 for(int i=0;i<k;i++){
       
         b[i] %= a[i];
        if(b[i]<0) b[i]+=a[i];
    }
    long long ans=0;
    for(int i=0;i<k;i++){
        long long x1=lcm/a[i];
        exgcd(x1,a[i]);
        ans=(ans+multiply(multiply(b[i],x1,lcm),x,lcm))%lcm;
    }
    cout<<(ans%lcm+lcm)%lcm<<'\n';
}