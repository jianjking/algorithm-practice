#include<bits/stdc++.h>
using namespace std;
vector<int>zuo;
vector<int>you;
vector<int>st;
vector<int>nums;
void build(int n){
    for(int cur=1,top=0,pos=0;cur<=n;cur++){
        pos=top;
        while(pos>0&&nums[st[pos]]>nums[cur]){
            pos--;
        }

        if(pos>0){
          you[st[pos]]=cur;
        }
        if(pos<top){
            zuo[cur]=st[pos+1];
        }
        pos++;
        st[pos]=cur;
        top=pos;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    zuo.assign(n+1,0);
    you.assign(n+1,0);
    st.assign(n+1,0);
    nums.assign(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    build(n);
    long long sum1=0;
    long long sum2=0;
    for(int i=1;i<=n;i++){
        sum1^=(1LL*i*(zuo[i]+1));
        sum2^=(1LL*i*(you[i]+1));
    }
    cout<<sum1<<" "<<sum2<<'\n';
}