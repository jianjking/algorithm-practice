#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
string root(string i, unordered_map<string,string>&fa,unordered_map<string,double>&dist){
    if(i==fa[i])return i;
    string f=root(fa[i],fa,dist);
    dist[i]*=dist[fa[i]];
    fa[i]=f;
    return f;
}
void merge(string l,string r,double v,unordered_map<string,string>&fa, unordered_map<string,double>&dist){
        string lf=root(l,fa,dist);
        string rf=root(r,fa,dist);
        if(lf==rf)return;
        dist[lf]=dist[r]*v/dist[l];
        fa[lf]=rf;
}
void query(string l,string r,vector<double>&ans,unordered_map<string,string>&fa, unordered_map<string,double>&dist){
    if(!fa.count(l)||!fa.count(r)){ans.push_back(-1);return;}
     string lf=root(l,fa,dist);
        string rf=root(r,fa,dist);
        if(lf!=rf){
            ans.push_back(-1);return;
        }
    ans.push_back(dist[l]/dist[r]);
}
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string,string>fa;
        unordered_map<string,double>dist;
        int n=equations.size();
        for(int i=0;i<n;i++){
            string l=equations[i][0];
            string r=equations[i][1];
            double v=values[i];
            if(!fa.count(l)){
                fa[l]=l;
                dist[l]=1.0;
            }
            if(!fa.count(r)){
                fa[r]=r;
                dist[r]=1.0;
            }
            merge(l,r,v,fa,dist);
        }
        int m=queries.size();
        vector<double>ans;
        for(int i=0;i<m;i++){
          string l=queries[i][0];
          string r=queries[i][1];
          query(l,r,ans,fa,dist);
        }
        return ans;
    }
};