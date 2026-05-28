#include<bits/stdc++.h>
using namespace std;
struct kuai{
  bool X;
  int time;
  int nums;
};
struct compare{
  bool operator()(const kuai& a,const kuai& b)const{
          if(a.time!=b.time)return a.time<b.time;
          if(a.nums!=b.nums)return a.nums<b.nums;
          return a.X<b.X;
  }
};
struct cache{
   int n;
   set<kuai,compare>s;
   unordered_map<int,int>alive;
};
int main(){
    int n,N,q;
    cin>>n>>N>>q;
    vector<cache>arr(N,{n,{},{}});
    for(int i=1;i<=q;i++){
        int o,a;
        cin>>o>>a;
        int pos=(a/n)%N;
        if(arr[pos].alive.count(a)){
            auto p=arr[pos].s.lower_bound({0,arr[pos].alive[a],a});
            kuai tmp=*p;
            if(o==1)tmp.X=1;
            arr[pos].alive[a]=i;
            tmp.time=i;
            arr[pos].s.erase(p);
            arr[pos].s.insert(tmp);
        }
        else{
            if(arr[pos].alive.size()<n){
                arr[pos].alive[a]=i;
                if(o==0)arr[pos].s.insert({0,arr[pos].alive[a],a});
                else arr[pos].s.insert({1,arr[pos].alive[a],a});
            }
            else{
                kuai tmp=*arr[pos].s.begin();
                arr[pos].s.erase(arr[pos].s.begin());
                arr[pos].alive.erase(arr[pos].alive.find(tmp.nums));
                arr[pos].alive[a]=i;
                   if(o==0)arr[pos].s.insert({0,arr[pos].alive[a],a});
                else arr[pos].s.insert({1,arr[pos].alive[a],a});
                if(tmp.X){
                    cout<<1<<" "<<tmp.nums<<'\n';
                }
            }
               cout<<0<<" "<<a<<'\n';
        }
    }

}