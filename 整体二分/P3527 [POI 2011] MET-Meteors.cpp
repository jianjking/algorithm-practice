#include<bits/stdc++.h>
using namespace std;

struct str{
   int u;
   int v;
   long long a;
};

int lowbit(int i){
    return i&(-i);
}

void addnum(int num,vector<long long>&tree,long long add){
    int n=tree.size()-1;
    while(num<=n){
        tree[num]+=add;
        num+=lowbit(num);
    }
}

long long querysum(int x,vector<long long>&tree){
    long long ans=0;
    while(x>0){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void dfs(int ql,int qr,int l,int r,
         vector<pair<long long,int>>&wanted,
         vector<str>&yunshi,
         vector<long long>&tree,
         vector<int>&ans,
         vector<vector<int>>&space,
         int m){

    if(ql>qr)return;

    if(l==r){
        for(int i=ql;i<=qr;i++){
            ans[wanted[i].second]=l;
        }
        return;
    }

    int mid=l+(r-l)/2;

    for(int i=l;i<=mid;i++){
        addnum(yunshi[i].u,tree,yunshi[i].a);
        addnum(yunshi[i].v+1,tree,-yunshi[i].a);
    }

    vector<pair<long long,int>> qql;
    vector<pair<long long,int>> qqr;

    for(int i=ql;i<=qr;i++){
        int country=wanted[i].second;
        long long cnt=0;

        for(auto &p:space[country]){
            cnt+=querysum(p,tree);
            cnt+=querysum(p+m,tree);
            if(cnt>=wanted[i].first)break;
        }

        if(cnt>=wanted[i].first){
            qql.push_back(wanted[i]);
        }
        else{
            wanted[i].first-=cnt;
            qqr.push_back(wanted[i]);
        }
    }

    int cur=ql;

    for(int i=0;i<(int)qql.size();i++){
        wanted[cur++]=qql[i];
    }

    for(int i=0;i<(int)qqr.size();i++){
        wanted[cur++]=qqr[i];
    }

    for(int i=l;i<=mid;i++){
        addnum(yunshi[i].u,tree,-yunshi[i].a);
        addnum(yunshi[i].v+1,tree,yunshi[i].a);
    }

    int leftcnt=qql.size();

    dfs(ql,ql+leftcnt-1,l,mid,wanted,yunshi,tree,ans,space,m);
    dfs(ql+leftcnt,qr,mid+1,r,wanted,yunshi,tree,ans,space,m);
}

int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<int>>space(n+1);

    for(int i=1;i<=m;i++){
        int o;
        cin>>o;
        space[o].push_back(i);
    }

    vector<pair<long long,int>>wanted(n+1);

    for(int i=1;i<=n;i++){
        cin>>wanted[i].first;
        wanted[i].second=i;
    }

    int k;
    cin>>k;

    vector<str>yunshi(k+2);

    for(int i=1;i<=k;i++){
        int l,r;
        long long a;
        cin>>l>>r>>a;

        if(r<l){
            r+=m;
        }

        yunshi[i].u=l;
        yunshi[i].v=r;
        yunshi[i].a=a;
    }

    vector<int>ans(n+1,0);
    vector<long long>tree(2*m+2,0);

    dfs(1,n,1,k+1,wanted,yunshi,tree,ans,space,m);

    for(int i=1;i<=n;i++){
        if(ans[i]==k+1)cout<<"NIE"<<'\n';
        else cout<<ans[i]<<'\n';
    }

    return 0;
}