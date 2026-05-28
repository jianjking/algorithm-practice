#include<bits/stdc++.h>
using namespace std;

struct node{
   long long h;
   long long e;
   long long a;
   long long d;
   long long c;
   bool belongl;
   int num;
   long long dp;
};

long long lowbit(long long i){
    return i&(-i);
}

void add(long long pos,long long v,vector<long long>&tree){
  int n=tree.size()-1;

  while(pos<=n){
    tree[pos]=max(tree[pos],v);
    pos+=lowbit(pos);
  }
}

long long query(long long pos,vector<long long>&tree){
    long long ans=0;

    while(pos>0){
        ans=max(ans,tree[pos]);
        pos-=lowbit(pos);
    }

    return ans;
}

void clear(long long pos,vector<long long>&tree){
   int n=tree.size()-1;

   while(pos<=n){
    tree[pos]=LLONG_MIN/2;
    pos+=lowbit(pos);
   }
}

void cdq2(int l,int r,vector<node>&tmp,vector<long long>&tree){
    if(l>=r)return;

    int mid=(l+r)/2;

    cdq2(l,mid,tmp,tree);
    cdq2(mid+1,r,tmp,tree);

    int i,j;

    for(i=l,j=mid+1;j<=r;j++){
        while(i<=mid&&tmp[i].a<=tmp[j].a){
            if(tmp[i].belongl){
                add(tmp[i].d,tmp[i].dp,tree);
            }
            i++;
        }

        if(!tmp[j].belongl){
            tmp[j].dp=max(tmp[j].dp,query(tmp[j].d,tree)+tmp[j].c);
        }
    }

    for(int z=l;z<i;z++){
        if(tmp[z].belongl){
            clear(tmp[z].d,tree);
        }
    }

    sort(tmp.begin()+l,tmp.begin()+r+1,[](node a,node b){
       if(a.a!=b.a) return a.a<b.a;
       return a.belongl>b.belongl;
    });
}

void cdq1(int l,int r,vector<node>&arr,vector<long long>&tree){
    if(l>=r)return;

    int mid=(l+r)/2;

    cdq1(l,mid,arr,tree);

    for(int i=l;i<=mid;i++){
        arr[i].belongl=true;
    }

    for(int i=mid+1;i<=r;i++){
        arr[i].belongl=false;
    }

    vector<node>tmp;

    for(int i=l;i<=r;i++){
        tmp.push_back(arr[i]);
    }

    sort(tmp.begin(),tmp.end(),[](node a,node b){
        if(a.e!=b.e)return a.e<b.e;
        return a.belongl>b.belongl;
    });

    cdq2(0,tmp.size()-1,tmp,tree);

    for(int i=0;i<(int)tmp.size();i++){
        arr[tmp[i].num]=tmp[i];
    }

    cdq1(mid+1,r,arr,tree);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    vector<node>nums(n);
    vector<long long>aaa;

    for(int i=0;i<n;i++){
        cin>>nums[i].h>>nums[i].e>>nums[i].a>>nums[i].d>>nums[i].c;
        aaa.push_back(nums[i].d);
    }

    sort(aaa.begin(),aaa.end());
    aaa.erase(unique(aaa.begin(),aaa.end()),aaa.end());

    sort(nums.begin(),nums.end(),[](node a,node b){
        if(a.h!=b.h)return a.h<b.h;
        if(a.e!=b.e)return a.e<b.e;
        if(a.a!=b.a)return a.a<b.a;
        if(a.d!=b.d)return a.d<b.d;
        return a.c>b.c;
    });

    vector<node>arr;

    int l=0;
    int r=0;

    while(l<n){
        arr.push_back(nums[l]);

        arr[arr.size()-1].d=lower_bound(aaa.begin(),aaa.end(),nums[l].d)-aaa.begin()+1;
        arr[arr.size()-1].num=arr.size()-1;

        while(r+1<n&&nums[r+1].a==nums[l].a&&nums[l].d==nums[r+1].d&&nums[l].e==nums[r+1].e&&nums[l].h==nums[r+1].h){
            r++;

            if(nums[r].c>0){
                arr[arr.size()-1].c+=nums[r].c;
            }
        }

        arr[arr.size()-1].dp=arr[arr.size()-1].c;

        l=r+1;
        r=l;
    }

    n=arr.size();

    vector<long long>tree(aaa.size()+1,LLONG_MIN/2);

    cdq1(0,n-1,arr,tree);

    long long ans=LLONG_MIN;

    for(int i=0;i<n;i++){
        ans=max(ans,arr[i].dp);
    }

    cout<<ans<<'\n';

    return 0;
}