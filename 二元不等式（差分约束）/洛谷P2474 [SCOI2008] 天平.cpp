#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,a,b;
    cin>>n>>a>>b;
    vector<vector<int>>mn(n+1,vector<int>(n+1,INT_MIN));
    vector<vector<int>>mx(n+1,vector<int>(n+1,INT_MAX));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char ch;
            cin>>ch;
            if(ch=='-'){
                mn[i][j]=-2;
                mx[i][j]=-1;
                mn[j][i]=1;
                mx[j][i]=2;
            }
            else if(ch=='+'){
                mx[i][j]=2;
                mn[i][j]=1;
                mx[j][i]=-1;
                mn[j][i]=-2;
            }
            else if(ch=='='){
                mx[i][j]=0;
                mn[i][j]=0;
                mx[j][i]=0;
                mn[j][i]=0;
            }
            else{
                mn[i][j]=-2;
                mx[i][j]=2;
                mn[j][i]=-2;
                mx[j][i]=2;
            }
        }
    }
     for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mn[i][k]!=INT_MIN&&mn[k][j]!=INT_MIN)
                mn[i][j]=max(mn[i][j],mn[i][k]+mn[k][j]);
                if(mx[i][k]!=INT_MAX&&mx[k][j]!=INT_MAX)
                mx[i][j]=min(mx[i][j],mx[i][k]+mx[k][j]);
            }
        }
}
long long ans1=0;
long long ans2=0;
long long ans3=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(i==a||i==b||j==a||j==b)continue;
            if( mn[a][i]>mx[j][b]||mn[a][j]>mx[i][b]||mn[b][i]>mx[j][a]||mn[b][j]>mx[i][a]){
                ans1++;
            }
            else if( (mn[a][i]==mx[a][i] && mn[j][b]==mx[j][b] && mn[a][i]==mx[j][b]) ||
                     (mn[a][j]==mx[a][j] && mn[i][b]==mx[i][b] && mn[a][j]==mx[i][b]) ||
                     (mn[b][i]==mx[b][i] && mn[j][a]==mx[j][a] && mn[b][i]==mx[j][a]) ||
                     (mn[b][j]==mx[b][j] && mn[i][a]==mx[i][a] && mn[b][j]==mx[i][a]) ){
                ans2++;
            }
            else if(mx[a][i]<mn[j][b]||mx[a][j]<mn[i][b]||mx[b][i]<mn[j][a]||mx[b][j]<mn[i][a]){
                ans3++;
            }
        }
    }
    cout<<ans1<<" "<<ans2<<" "<<ans3<<"\n";
}