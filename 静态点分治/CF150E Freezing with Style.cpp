#include<bits/stdc++.h>
using namespace std;

const int MAXN=100000+5;
const int NEG=-1000000000;

int n,limitl,limitr;
vector<vector<pair<int,int>>>graph;

int sz[MAXN];
bool vis[MAXN];

int predep[MAXN];
int curdep[MAXN];
int prenode[MAXN];
int curnode[MAXN];

int ansl,ansr;
int curLen;
deque<int>q;

void getsz(int u,int fa){
    sz[u]=1;
    for(auto&[p,w]:graph[u]){
        if(p==fa||vis[p])continue;
        getsz(p,u);
        sz[u]+=sz[p];
    }
}

int getrt(int u,int fa){
    getsz(u,fa);
    int half=sz[u]/2;

    while(true){
        bool flag=true;
        for(auto&[p,w]:graph[u]){
            if(p==fa||vis[p])continue;
            if(sz[p]>half){
                flag=false;
                fa=u;
                u=p;
                break;
            }
        }
        if(flag)return u;
    }
}

void dfs(int u,int fa,int sum,int dep,int mid){
    curLen=max(curLen,dep);

    if(sum>curdep[dep]){
        curdep[dep]=sum;
        curnode[dep]=u;
    }

    for(auto&[p,w]:graph[u]){
        if(p==fa||vis[p])continue;
        dfs(p,u,sum+(w>=mid?1:-1),dep+1,mid);
    }
}

void addque(int x){
    while(!q.empty()&&predep[x]>=predep[q.back()]){
        q.pop_back();
    }
    q.push_back(x);
}

bool calu(int rt,int mid){
    getsz(rt,0);

    sort(graph[rt].begin(),graph[rt].end(),[](pair<int,int>a,pair<int,int>b){
        return sz[a.first]<sz[b.first];
    });

    int prelen=0;
    predep[0]=0;
    prenode[0]=rt;

    for(auto&[p,w]:graph[rt]){
        if(vis[p])continue;

        for(int i=1;i<=sz[p];i++){
            curdep[i]=NEG;
            curnode[i]=0;
        }

        curLen=0;
        dfs(p,rt,w>=mid?1:-1,1,mid);

        q.clear();

        for(int i=min(prelen,limitr);i>=limitl;i--){
            addque(i);
        }

        int right=limitr;
        int left=limitl;

        for(int i=1;i<=curLen;i++){
            left--;

            if(left>=0&&left<=prelen){
                addque(left);
            }

            if(!q.empty()&&q.front()==right){
                q.pop_front();
            }

            right--;

            if(!q.empty()&&curdep[i]+predep[q.front()]>=0){
                ansl=curnode[i];
                ansr=prenode[q.front()];
                return true;
            }
        }

        for(int i=1;i<=curLen;i++){
            if(i>prelen||curdep[i]>predep[i]){
                predep[i]=curdep[i];
                prenode[i]=curnode[i];
            }
        }

        prelen=max(prelen,curLen);
    }

    return false;
}

bool solve(int rt,int mid){
    vis[rt]=true;

    if(calu(rt,mid))return true;

    for(auto&[p,w]:graph[rt]){
        if(vis[p])continue;
        if(solve(getrt(p,rt),mid))return true;
    }

    return false;
}

bool check(int mid){
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }

    int rt=getrt(1,0);
    return solve(rt,mid);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>limitl>>limitr;

    graph.assign(n+1,vector<pair<int,int>>());

    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }

    int l=0;
    int r=1000000000;
    int ans=0;

    while(l<=r){
        int mid=(l+r)/2;

        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }

    cout<<ansl<<" "<<ansr<<"\n";

    return 0;
}