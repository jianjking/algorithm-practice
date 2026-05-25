#include<bits/stdc++.h>
using namespace std;

struct str{
    int nums;
    int a;
    int b;
    int c;
};

int lowbit(int i){
    return i&(-i);
}

void add(int i,vector<int>&tree,int v){
    int n=tree.size()-1;
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
    }
}

int query(int i,vector<int>&tree){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
    }
    return ans;
}

void merge(int l,int r, vector<str>&s, vector<int>&f,vector<int>&tree){
    if(l>=r){
        return;
    }

    int mid=(l+r)/2;

    merge(l,mid,s,f,tree);
    merge(mid+1,r,s,f,tree);

    int i,j;

    for(i=mid+1,j=l;i<=r;i++){
        while(j<=mid&&s[j].b<=s[i].b){
            add(s[j].c,tree,1);
            j++;
        }

        f[s[i].nums]+=query(s[i].c,tree);
    }

    for(int z=l;z<j;z++){
        add(s[z].c,tree,-1);
    }

    sort(s.begin()+l,s.begin()+r+1,[](str a,str b){
        return a.b<b.b;
    });
}

int main(){
    int n,k;
    cin>>n>>k;

    vector<str>s(n);

    for(int i=0;i<n;i++){
        cin>>s[i].a>>s[i].b>>s[i].c;
        s[i].nums=i;
    }

    vector<int>f(n,0);

    sort(s.begin(),s.end(),[](str a,str b){
        if(a.a!=b.a)return a.a<b.a;
        if(a.b!=b.b)return a.b<b.b;
        if(a.c!=b.c)return a.c<b.c;
        return a.nums<b.nums;
    });

    int l=0;

    while(l<n){
        int r=l;

        while(r+1<n&&s[r+1].a==s[l].a&&s[r+1].b==s[l].b&&s[r+1].c==s[l].c){
            r++;
        }

        for(int i=l;i<=r;i++){
            f[s[i].nums]=r-i;
        }

        l=r+1;
    }

    vector<int>tree(k+1,0);

    merge(0,n-1,s,f,tree);

    vector<int>ans(n,0);

    for(int i=0;i<n;i++){
        ans[f[i]]++;
    }

    for(int i=0;i<n;i++){
        cout<<ans[i]<<'\n';
    }

    return 0;
}