#include<bits/stdc++.h>
using namespace std;
long long power(int a,int b,int p){
   long long ans=1;
   while(b){
    if(b&1){
        ans=(ans*a)%p;
    }
    a=(a*a)%p;
    b>>=1;
   }
   return ans;
}
int main(){
    int n,p;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>p;
    vector<int>oula(2*n+1,0);
    vector<int>cnt(2*n+1,0);
    for(int i=2;i<=n;i++){
        cnt[i]=-1;
    }
    for(int i=n+2;i<=2*n;i++){
        cnt[i]=1; 
    }
    for(int i=2;i<=2*n;i++){
        if(oula[i]!=0)continue;
        for(int j=i*2;j<=2*n;j+=i){
            if(oula[j]==0)oula[j]=i;
        }
    }
    for(int i=2*n;i>=2;i--){
        if(cnt[i]!=0&&oula[i]!=0){
            int num=i/oula[i];
            cnt[oula[i]]+=cnt[i];
            cnt[num]+=cnt[i];
            cnt[i]=0;
        }
    }
    long long ans=1;
    for(int i=2;i<=2*n;i++){
        if(cnt[i]!=0){
            ans=(ans*power(i,cnt[i],p))%p;
        }
    }
    cout<<ans<<'\n';
}