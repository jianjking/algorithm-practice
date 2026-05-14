#include<bits/stdc++.h>
using namespace std;

struct Edge{
    int u,v,w;
};

struct Query{
    int u,v,w,id;
};

int root(int x, vector<int>& father){
    while(x!=father[x]){
        x=father[x];
    }
    return x;
}

void unio(int fx,int fy,vector<int>&father,vector<int>&sz,vector<pair<int,int>>&sta){
    if(sz[fx]<sz[fy]){
        swap(fx,fy);
    }
    father[fy]=fx;
    sz[fx]+=sz[fy];
    sta.push_back({fx,fy});
}

void undo(vector<int>&father,vector<int>&sz,vector<pair<int,int>>&sta){
    int fx=sta.back().first;
    int fy=sta.back().second;
    sta.pop_back();

    father[fy]=fy;
    sz[fx]-=sz[fy];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m;

    vector<Edge> edges(m+1);
    vector<Edge> old(m+1);

    for(int i=1;i<=m;i++){
        cin>>old[i].u>>old[i].v>>old[i].w;
        edges[i]=old[i];
    }

    int q;
    cin>>q;

    vector<Query> quest;
    quest.reserve(500000);

    for(int i=1;i<=q;i++){
        int k;
        cin>>k;
        for(int j=0;j<k;j++){
            int num;
            cin>>num;
            quest.push_back({old[num].u,old[num].v,old[num].w,i});
        }
    }

    sort(edges.begin()+1,edges.end(),[](const Edge&a,const Edge&b){
        return a.w<b.w;
    });

    sort(quest.begin(),quest.end(),[](const Query&a,const Query&b){
        if(a.w!=b.w) return a.w<b.w;
        return a.id<b.id;
    });

    vector<int> father(n+1);
    vector<int> sz(n+1,1);

    for(int i=1;i<=n;i++){
        father[i]=i;
    }

    vector<pair<int,int>> sta;
    sta.reserve(n+quest.size()+5);

    vector<int> ans(q+1,true);

    int ei=1;
    int l=0;
    int lim=quest.size();

    while(l<lim){
        int r=l;

        while(r<lim&&quest[r].w==quest[l].w&&quest[r].id==quest[l].id){
            r++;
        }

        while(ei<=m&&edges[ei].w<quest[l].w){
            int fx=root(edges[ei].u,father);
            int fy=root(edges[ei].v,father);

            if(fx!=fy){
                unio(fx,fy,father,sz,sta);
            }

            ei++;
        }

        int id=quest[l].id;

        if(!ans[id]){
            l=r;
            continue;
        }

        int before=sta.size();

        for(int i=l;i<r;i++){
            int fx=root(quest[i].u,father);
            int fy=root(quest[i].v,father);

            if(fx==fy){
                ans[id]=false;
                break;
            }

            unio(fx,fy,father,sz,sta);
        }

        while((int)sta.size()>before){
            undo(father,sz,sta);
        }

        l=r;
    }

    for(int i=1;i<=q;i++){
        if(ans[i]){
            cout<<"YES"<<'\n';
        }
        else{
            cout<<"NO"<<'\n';
        }
    }

    return 0;
}