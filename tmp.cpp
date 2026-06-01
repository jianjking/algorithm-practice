#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long dfs(string s, unordered_map<string,long long>&sort1, unordered_map<string,long long>&sort2,vector<vector<string>>&f){
     if(s[0]!='$'){
        return s.size();
     }
     string tmp=s.substr(1);
         long long ans=0;
     if(sort1.count(tmp)){
        return sort1[tmp];
     }
     else{
               long long pos=sort2[tmp];
               for(auto&p:f[pos]){
         ans=(ans+dfs(p,sort1,sort2,f))%mod;
             }
     }
     return ans;
}
int main(){
    unordered_map<string,long long>sort1;
    vector<vector<string>>f;
    unordered_map<string,long long>sort2;
    int n;
    cin>>n;
    cin.get();
    string s;
    for(int i=0;i<n;i++){
        getline(cin,s);
        int cnt=0;
        string target;
        long long ans=0;
        if(s[0]=='1'){
            int j=1;
            while(j<s.size()){
                if(s[j]==' '){
                    j++;
                    continue;
                }
                string tmp;
                while(j<s.size()&&s[j]!=' '){
                    tmp+=s[j];
                    j++;
                }
                if(cnt==0){
                    target=tmp;
                    cnt++;
                    continue;
                }
                if(tmp[0]!='$'){
                    ans=(ans+tmp.size())%mod;
                }
                else{
                    string search=tmp.substr(1);
                    if(sort1.count(search)){
                         ans=(ans+sort1[search])%mod;
                    }
                    else{
                        long long pos=sort2[search];
                        for(auto&p:f[pos]){
                            ans=(ans+dfs(p,sort1,sort2,f))%mod;
                        }
                    }
                }
            }
           sort1[target]=ans;
        }
        else if(s[0]=='2'){
             int j=1;
             f.push_back({});
            while(j<s.size()){
                if(s[j]==' '){
                    j++;
                    continue;
                }
                string tmp;
                while(j<s.size()&&s[j]!=' '){
                    tmp+=s[j];
                    j++;
                }
                if(cnt==0){
                    target=tmp;
                    cnt++;
                    continue;
                }
             f[f.size()-1].push_back(tmp);
        }
        sort2[target]=f.size()-1;
    }
    else{
        int j=1;
          while(j<s.size()){
                if(s[j]==' '){
                    j++;
                    continue;
                }
                string tmp;
                while(j<s.size()&&s[j]!=' '){
                    tmp+=s[j];
                    j++;
                }
                if(cnt==0){
                    target=tmp;
                    cnt++;
                    continue;
                }
       }
       if(sort1.count(target)){
        cout<<sort1[target]<<'\n';
       }
       else{
         long long pos=sort2[target];
                        for(auto&p:f[pos]){
                            ans=(ans+dfs(p,sort1,sort2,f))%mod;
                        }
                        cout<<ans<<'\n';
       }
    }
}}