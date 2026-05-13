#include<bits/stdc++.h>
using namespace std;
struct node{
     node*left;
     node*right;
     int sz;
     int h;
     pair<int,int>val;
};
int size(node*cur){
    return cur==NULL?0:cur->sz;
}
int high(node*cur){
    return cur==NULL?0:cur->h;
}
void up(node*cur){
    cur->h=max(high(cur->left),high(cur->right))+1;
    cur->sz=size(cur->left)+size(cur->right)+1;
}
node* lxu(node*cur){
       node*r=cur->right;
       cur->right=r->left;
       r->left=cur;
       up(cur);
       up(r);
       return r;
}
node* rxu(node*cur){
    node*l=cur->left;
    cur->left=l->right;
    l->right=cur;
    up(cur);
    up(l);
    return l;
}
node* balance(node*cur){
    int h1=high(cur->left);
    int h2=high(cur->right);
    if(h1-h2>1){
        int h3=high(cur->left->left);
        int h4=high(cur->left->right);
        if(h3>=h4){
            return rxu(cur);
        }
        else{
            cur->left=lxu(cur->left);
             return rxu(cur);
        }
    }
    else if(h2-h1>1){
        int h3=high(cur->right->left);
        int h4=high(cur->right->right);
        if(h4>=h3){
            return lxu(cur);
        }
        else{
            cur->right=rxu(cur->right);
            return lxu(cur);
        }
    }
    up(cur);
    return cur;
}
node*add(pair<int,int>target,node*cur,int n){
        if(cur==NULL){
            cur=new node;
            cur->left=NULL;
            cur->right=NULL;
            cur->sz=1;
            cur->h=1;
            cur->val=target;
            return cur;
        }
        else{
            int cnt=size(cur->left);
            if(n<=cnt){
                cur->left=add(target,cur->left,n);
            }
            else{
                cur->right=add(target,cur->right,n-cnt-1);
            }
        }
        up(cur);
        return balance(cur);
}
void dfs(vector<vector<int>>&ans,node*cur){
    if(cur==NULL)return;
    dfs(ans,cur->left);
    ans.push_back({cur->val.first,cur->val.second});
    dfs(ans,cur->right);
}
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),[](vector<int>&a,vector<int>&b){
            if(a[0]!=b[0])return a[0]>b[0];
            return a[1]<b[1]; 
        });
        int n=people.size();
        node*head=NULL;
        for(int i=0;i<n;i++){
            head=add({people[i][0],people[i][1]},head,people[i][1]);
        }
        vector<vector<int>>ans;
        dfs(ans,head);
        return ans;
    }
};
