#include<iostream>
#include<vector>
using namespace std;

long long multiply(long long a,long long b,long long mod){
    a%=mod; if(a<0) a+=mod;
    b%=mod; if(b<0) b+=mod;
    __int128 aa=a, bb=b, mm=mod;
    return (long long)((aa*bb)%mm);
}

long long x,y;
void exgcd(long long a,long long b){
    if(b==0){ x=1; y=0; return; }
    exgcd(b,a%b);
    long long tx=x, ty=y;
    x=ty;
    y=tx-(a/b)*ty;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    vector<long long>a(n),b(n);
    long long lcm=1;
    for(int i=0;i<n;i++){
        cin>>a[i]>>b[i];
        b[i]%=a[i];
        if(b[i]<0) b[i]+=a[i];
        lcm*=a[i];
    }
    long long sum=0;
    for(int i=0;i<n;i++){
        long long tmp=lcm/a[i];
        exgcd(tmp,a[i]);
        long long inv=(x%a[i]+a[i])%a[i];
        sum=(sum+multiply(multiply(b[i],tmp,lcm),inv,lcm))%lcm;
    }
    if(sum<0) sum+=lcm;
    cout<<sum<<'\n';
}
