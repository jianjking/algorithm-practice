#include<bits/stdc++.h>
using namespace std;
//动态规划方法，枚举谁和谁握手
long long f1(int n){
    if(n==1)return 0;
    if(n==2)return 1;
    long long prepre=0;
     long long pre=1;
    for(int i=3;i<=n;i++){
        long long cur=i*(prepre+pre);
        prepre=pre;
        pre=cur;
    }
    return pre;
}
//二项式反演
//g(x)=总方法数 x！
//g(x)=sum(有零个人握自己手+有一个人握自己手+有两个人握自己手+.....有x个人握自己手)
//f(x)=有x个人握自己的手
long long f2(int n){
    long long facn=1;
    for(int i=2;i<=n;i++){
        facn*=i;
    }
    long long faci=1;
    long long sum=0;
    for(int i=0;i<=n;i++){
        if(i!=0)faci*=i;
       int sign=(i%2==0?1:-1);
      sum+=sign*(facn/faci);
    }
    return sum;

}
int main(){
    int n;
    cin>>n;
    cout<<f2(n)<<'\n';
}
