
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
struct during{
  ll l;
  ll r;
};
struct compare{
    bool operator()(const during&a,const during&b)const{
        if(a.r-a.l+1!=b.r-b.l+1)return a.r-a.l+1<b.r-b.l+1;
        return a.l<b.l;
    }
};
struct q{
  ll l;
  ll r;
  ll cur;
}; 
struct process{
   vector<q>arr;
};
int main(){
    int n,time;
    cin>>n>>time;
    set<during,compare>s;
    s.insert({0,LLONG_MAX});
    vector<process>arr(n);
    for(int i=0;i<time;i++){
        string tmp;
        cin>>tmp;
        if(tmp=="new"){
            int p,l;
            cin>>p>>l;
            p--;
            auto u=s.lower_bound({0,l-1});
            during d=*u;
            s.erase(u);
            arr[p].arr.push_back({d.l,d.l+l-1,d.l});
            cout<<d.l<<'\n';
            s.insert({d.l+l,d.r});
        }
        else if(tmp=="send"){
            int p;
            cin>>p;
            p--;
            ll sum=0;
            for(auto&t:arr[p].arr){
                  sum+=t.cur;
                  if(t.cur==t.r){
                    t.cur=t.l;
                  }
                  else{
                    t.cur++;
                  }
            }
            cout<<sum<<'\n';
        }
        else{
            int p,i;
            cin>>p>>i;
            p--;
            i--;
            q aaa=arr[p].arr[i];
            for(int z=i;z<arr[p].arr.size()-1;z++){
                 arr[p].arr[z]=arr[p].arr[z+1];
            }
            arr[p].arr.pop_back();
            vector<during>abc;
            for(auto&g:s){
                abc.push_back(g);
            }
            abc.push_back({aaa.l,aaa.r});
            s.clear();
            sort(abc.begin(),abc.end(),[](auto a,auto b){
               if(a.l!=b.l) return a.l<b.l;
                 return a.r<b.r;
            });
            int l=0;
            int r=0;
            while(l<abc.size()){
                ll dl=abc[l].l;
                ll dr=abc[l].r;
                while(r+1<abc.size()&&abc[r+1].l==dr+1){
                    dr=abc[r+1].r;
                    r++;
                }
                s.insert({dl,dr});
               l=r+1;
               r=l;
            }
        }
    }
}
