#include<bits/stdc++.h>
using namespace std;

struct node{
    int h;
    int v;
    int dpend;
    long double cntend;
    int dpstart;
    long double cntstart;
    int num;
};

void up(int i,vector<int>&tree,vector<long double>&cnt){
    if(tree[2*i]>tree[2*i+1]){
        tree[i]=tree[2*i];
        cnt[i]=cnt[2*i];
    }
    else if(tree[2*i]==tree[2*i+1]){
        tree[i]=tree[2*i];
        cnt[i]=cnt[2*i]+cnt[2*i+1];
    }
    else{
        tree[i]=tree[2*i+1];
        cnt[i]=cnt[2*i+1];
    }
}

void insert(int pos,int v1,long double v2,int l,int r,int nums,vector<int>&tree,vector<long double>&cnt){
    if(l==r){
        if(tree[nums]<v1){
            tree[nums]=v1;
            cnt[nums]=v2;
        }
        else if(tree[nums]==v1){
            cnt[nums]+=v2;
        }
        return;
    }

    int mid=(l+r)/2;

    if(pos<=mid){
        insert(pos,v1,v2,l,mid,2*nums,tree,cnt);
    }
    else{
        insert(pos,v1,v2,mid+1,r,2*nums+1,tree,cnt);
    }

    up(nums,tree,cnt);
}

pair<int,long double> query(int lt,int rt,int l,int r,int nums,vector<int>&tree,vector<long double>&cnt){
    if(lt>rt){
        return {0,0};
    }

    if(lt<=l&&rt>=r){
        return {tree[nums],cnt[nums]};
    }

    int mid=(l+r)/2;

    if(rt<=mid){
        return query(lt,rt,l,mid,2*nums,tree,cnt);
    }

    if(lt>mid){
        return query(lt,rt,mid+1,r,2*nums+1,tree,cnt);
    }

    pair<int,long double> lans=query(lt,rt,l,mid,2*nums,tree,cnt);
    pair<int,long double> rans=query(lt,rt,mid+1,r,2*nums+1,tree,cnt);

    if(lans.first<rans.first){
        return rans;
    }

    if(lans.first>rans.first){
        return lans;
    }

    return {lans.first,lans.second+rans.second};
}

void clear(int pos,int l,int r,int nums,vector<int>&tree,vector<long double>&cnt){
    if(l==r){
        tree[nums]=0;
        cnt[nums]=0;
        return;
    }

    int mid=(l+r)/2;

    if(pos<=mid){
        clear(pos,l,mid,2*nums,tree,cnt);
    }
    else{
        clear(pos,mid+1,r,2*nums+1,tree,cnt);
    }

    up(nums,tree,cnt);
}

void cdq1(int l,int r,vector<int>&tree,vector<long double>&cnt,vector<node>&nums,int n){
    if(l>=r){
        return;
    }

    int mid=(l+r)/2;

    cdq1(l,mid,tree,cnt,nums,n);

    vector<int>left;
    vector<int>right;

    for(int i=l;i<=mid;i++){
        left.push_back(i);
    }

    for(int i=mid+1;i<=r;i++){
        right.push_back(i);
    }

    sort(left.begin(),left.end(),[&](int a,int b){
        return nums[a].h>nums[b].h;
    });

    sort(right.begin(),right.end(),[&](int a,int b){
        return nums[a].h>nums[b].h;
    });

    vector<int>used;

    int i=0;

    for(int j=0;j<(int)right.size();j++){
        int id=right[j];

        while(i<(int)left.size()&&nums[left[i]].h>=nums[id].h){
            int x=left[i];

            insert(nums[x].v,nums[x].dpend,nums[x].cntend,1,n,1,tree,cnt);

            used.push_back(nums[x].v);
            i++;
        }

        pair<int,long double>tmp=query(nums[id].v,n,1,n,1,tree,cnt);

        if(nums[id].dpend<tmp.first+1){
            nums[id].dpend=tmp.first+1;
            nums[id].cntend=tmp.second;
        }
        else if(nums[id].dpend==tmp.first+1){
            nums[id].cntend+=tmp.second;
        }
    }

    for(int x:used){
        clear(x,1,n,1,tree,cnt);
    }

    cdq1(mid+1,r,tree,cnt,nums,n);
}

void cdq2(int l,int r,vector<int>&tree,vector<long double>&cnt,vector<node>&nums,int n){
    if(l>=r){
        return;
    }

    int mid=(l+r)/2;

    cdq2(l,mid,tree,cnt,nums,n);

    vector<int>left;
    vector<int>right;

    for(int i=l;i<=mid;i++){
        left.push_back(i);
    }

    for(int i=mid+1;i<=r;i++){
        right.push_back(i);
    }

    sort(left.begin(),left.end(),[&](int a,int b){
        return nums[a].h<nums[b].h;
    });

    sort(right.begin(),right.end(),[&](int a,int b){
        return nums[a].h<nums[b].h;
    });

    vector<int>used;

    int i=0;

    for(int j=0;j<(int)right.size();j++){
        int id=right[j];

        while(i<(int)left.size()&&nums[left[i]].h<=nums[id].h){
            int x=left[i];

            insert(nums[x].v,nums[x].dpstart,nums[x].cntstart,1,n,1,tree,cnt);

            used.push_back(nums[x].v);
            i++;
        }

        pair<int,long double>tmp=query(1,nums[id].v,1,n,1,tree,cnt);

        if(nums[id].dpstart<tmp.first+1){
            nums[id].dpstart=tmp.first+1;
            nums[id].cntstart=tmp.second;
        }
        else if(nums[id].dpstart==tmp.first+1){
            nums[id].cntstart+=tmp.second;
        }
    }

    for(int x:used){
        clear(x,1,n,1,tree,cnt);
    }

    cdq2(mid+1,r,tree,cnt,nums,n);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    vector<node>nums(n+1);
    vector<int>arr;

    for(int i=1;i<=n;i++){
        cin>>nums[i].h>>nums[i].v;

        arr.push_back(nums[i].v);

        nums[i].dpend=1;
        nums[i].cntend=1;
        nums[i].dpstart=1;
        nums[i].cntstart=1;
        nums[i].num=i;
    }

    sort(arr.begin(),arr.end());
    arr.erase(unique(arr.begin(),arr.end()),arr.end());

    for(int i=1;i<=n;i++){
        nums[i].v=lower_bound(arr.begin(),arr.end(),nums[i].v)-arr.begin()+1;
    }

    int m=arr.size();

    vector<int>tree(4*m+9,0);
    vector<long double>cnt(4*m+9,0);

    cdq1(1,n,tree,cnt,nums,m);

    fill(tree.begin(),tree.end(),0);
    fill(cnt.begin(),cnt.end(),0);

    int l=1;
    int r=n;

    while(l<r){
        swap(nums[l],nums[r]);
        l++;
        r--;
    }

    cdq2(1,n,tree,cnt,nums,m);

    sort(nums.begin()+1,nums.end(),[](node a,node b){
        return a.num<b.num;
    });

    int mxlen=1;
    long double mxcnt=0;

    for(int i=1;i<=n;i++){
        mxlen=max(mxlen,nums[i].dpend);
    }

    for(int i=1;i<=n;i++){
        if(nums[i].dpend==mxlen){
            mxcnt+=nums[i].cntend;
        }
    }

    cout<<mxlen<<'\n';

    cout<<fixed<<setprecision(10);

    for(int i=1;i<=n;i++){
        long double ans=0;

        if(nums[i].dpend+nums[i].dpstart-1==mxlen){
            ans=nums[i].cntend*nums[i].cntstart/mxcnt;
        }

        cout<<(double)ans;

        if(i==n){
            cout<<'\n';
        }
        else{
            cout<<" ";
        }
    }

    return 0;
}