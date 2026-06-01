#include<bits/stdc++.h>
using namespace std;
int  main(){
    long long ans=0;
    long long a,b,c,d;
    cin>>a>>b>>c>>d;
    for(int z=c;z<=d;z++){
        int x=(z+1)-b;
        if(x<=a){
            ans+=(long long)(c-b+1)*(b-a+1);
        }
        else if(x<=b){
          int y=(z+1)-a;
          if(y>=c){
            int x2=(z+1)-c;
            ans+=(long long)(b-x2+1+b-x+1)*(x-x2+1)/2;
          }
          else{
            ans+=(long long)(b-x+1+b-a+1)*(y-b+1)/2+(c-y)*(b-a+1);
          }
        }
        else{
             int x1=(z+1)-c;
             if(x1>b){
                continue;
             }
             else if(x1>=a){
                ans+=(long long)(1+b-x1+1)*(b-x1+1)/2;
             }
             else{
                ans+=(long long)(1+b-a+1)*(b-a+1)/2;
                ans+=(long long)(a-x1)*(b-a+1);
             }
        }
      
    }
    cout<<ans<<'\n';
}