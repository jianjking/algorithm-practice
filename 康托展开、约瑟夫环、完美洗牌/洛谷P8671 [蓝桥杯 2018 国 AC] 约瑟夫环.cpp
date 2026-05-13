#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k;
    cin>>n>>k;
    int ans=0;
    for(int i=2;i<=n;i++){
        ans=(ans+k+1)%i;
    }
    cout<<ans<<'\n';
}