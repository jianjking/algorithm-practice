#include<bits/stdc++.h>
using namespace std;
struct node{
  int x;
  int y;
  int v;
  int op;
};
int lowbit(int i){
    return i&(-i);
}
void add(int i,vector<long long>&tree,int v){
    int n=tree.size()-1;
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
    }
}
long long query(int i ,vector<long long>&tree){
    long long ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
    }
    return ans;
}
void cdq(int l,int r,vector<node>&q,vector<long long>&ans,vector<long long>&tree){
    if(l>=r)return;
    int mid=(l+r)/2;
    cdq(l,mid,q,ans,tree);
    cdq(mid+1,r,q,ans,tree);
    int i,j;
    for(i=l,j=mid+1;j<=r;j++){
        while(i<=mid&&q[j].x>=q[i].x){
            if(q[i].op==0){
                add(q[i].y,tree,q[i].v);
            }
            i++;
        }
        if(q[j].op>0){
           ans[q[j].op]+=q[j].v*(query(q[j].y,tree));
        }
    }
    for(int z=l;z<i;z++){
        if(q[z].op==0){
            add(q[z].y,tree,-q[z].v);
        }
    }
    sort(q.begin()+l,q.begin()+r+1,[](node a,node b){
        return a.x<b.x;
    });
}
int main(){
    int tmp,w;
    cin>>tmp>>w;
    w++;
    int cnt=1;
    vector<node>q;
    while(true){
        int op;
        cin>>op;
        if(op==3)break;
        if(op==1){
           int x,y,a;
           cin>>x>>y>>a;
           x++;
           y++;
           q.push_back({x,y,a,0});
        }
        else{
            int x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            x1++;
            y1++;
            x2++;
            y2++;
            q.push_back({x2,y2,1,cnt});
            q.push_back({x1-1,y2,-1,cnt});
            q.push_back({x2,y1-1,-1,cnt});
            q.push_back({x1-1,y1-1,1,cnt});
            cnt++;
        }
    }
    vector<long long>ans(cnt,0);
    vector<long long>tree(w+1,0);
    cdq(0,q.size()-1,q,ans,tree);
    for(int i=1;i<cnt;i++){
        cout<<ans[i]<<'\n';
    }
}