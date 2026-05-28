#include<bits/stdc++.h>
using namespace std;
struct kuai{
   vector<string>depart;
};
bool isdigit(char c){
   return c<='9'&&c>='0';
}
int digit(char c){
    return c-'0';
}
int main(){
    int n;
    cin>>n;
    cin.get(); // 修改：原文每行可能有空格，下面要 getline，所以先吃掉换行

    vector<string>ori(n+1);
    vector<string>out; // 修改：out(n+1) 会先放 n+1 个空行，输出必错

    for(int i=1;i<=n;i++){
        getline(cin,ori[i]); // 修改：原文件行可能包含空格，不能用 cin>>
    }

   string s;
   vector<kuai>total;
while(getline(cin,s)){
    if(s.size()>0&&s[0]=='#'){ // 修改：先判断 size，避免空行 s[0] 越界
        continue;
    }
   if(s.size()>0&&s[0]=='@'){ // 修改：先判断 size
      kuai tmp;
      tmp.depart.push_back(s);
      total.push_back(tmp);
   }
   else{
      if(total.size()>0){ // 修改：第一个 @ 前面的 dummy 要忽略，不能访问 total[-1]
        total[total.size()-1].depart.push_back(s);
      }
   }
}

if(total.size()==0){ // 修改：没有任何块，补丁损坏
    cout<<"Patch is damaged."<<'\n';
    return 0;
}

int prenn=1;
int premm=0;
int can=0;
for(int i=0;i<total.size();i++){
    vector<string>diff=total[i].depart;
    string s=diff[0];
    int NN=0;
    int MM=0;
    int nn=0;
    int mm=0;
    if(s.size()<4||s[0]!='@'||s[1]!='@'){ // 修改：防越界
        cout<<"Patch is damaged."<<'\n';
        return 0;
    }
    if(s[2]!=' '||s[3]!='-'){
         cout<<"Patch is damaged."<<'\n';
         return 0;
    }
    int cur=4;

    if(cur>=s.size()||s[cur]<'1'||s[cur]>'9'){ // 修改：NN 必须是正整数，且防越界
        cout<<"Patch is damaged."<<'\n';
        return 0;
    }
    while(cur<s.size()&&isdigit(s[cur])){
        NN=NN*10+digit(s[cur]);
        cur++;
    }
    if(cur>=s.size()||s[cur]!=','){ // 修改：防越界
         cout<<"Patch is damaged."<<'\n';
         return 0;
    }
    cur++;

    if(cur>=s.size()||s[cur]<'1'||s[cur]>'9'){ // 修改：MM 必须是正整数，且防越界
        cout<<"Patch is damaged."<<'\n';
        return 0;
    }
    while(cur<s.size()&&isdigit(s[cur])){
      MM=MM*10+digit(s[cur]);
      cur++;
    }
    if(cur+1>=s.size()||s[cur]!=' '||s[cur+1]!='+'){ // 修改：防越界
       cout<<"Patch is damaged."<<'\n';
         return 0;
    }
   cur+=2;

   if(cur>=s.size()||s[cur]<'1'||s[cur]>'9'){ // 修改：nn 必须是正整数，且防越界
      cout<<"Patch is damaged."<<'\n';
      return 0;
   }
   while(cur<s.size()&&isdigit(s[cur])){
      nn=nn*10+digit(s[cur]);
      cur++;
   }
   if(cur>=s.size()||s[cur]!=','){ // 修改：防越界
     cout<<"Patch is damaged."<<'\n';
         return 0;
   }
   cur++;

   if(cur>=s.size()||s[cur]<'1'||s[cur]>'9'){ // 修改：mm 必须是正整数，且防越界
       cout<<"Patch is damaged."<<'\n';
       return 0;
   }
   while(cur<s.size()&&isdigit(s[cur])){
       mm=mm*10+digit(s[cur]);
       cur++;
   }
   if(cur+2>=s.size()||s[cur]!=' '||s[cur+1]!='@'||s[cur+2]!='@'||cur+3!=s.size()){ // 修改：防越界
     cout<<"Patch is damaged."<<'\n';
         return 0;
   }
   NN+=can;
   vector<string>tmp1;
   vector<string>tmp2;
   for(int i=1;i<diff.size();i++){
      if(diff[i].size()==0){ // 修改：空行没有前缀，访问 diff[i][0] 会越界
         cout<<"Patch is damaged."<<'\n';
         return 0;
      }
      if(diff[i][0]=='+'){
        tmp2.push_back(diff[i].substr(1)); // 修改：真实内容要去掉 + 前缀
      }
      else if(diff[i][0]=='-'){
        tmp1.push_back(diff[i].substr(1)); // 修改：真实内容要去掉 - 前缀
      }
      else if(diff[i][0]==' '){
        tmp1.push_back(diff[i].substr(1)); // 修改：真实内容要去掉空格前缀
        tmp2.push_back(diff[i].substr(1)); // 修改：真实内容要去掉空格前缀
      }
      else{
         cout<<"Patch is damaged."<<'\n';
         return 0;
      }
   }
   if(tmp1.size()!=MM||tmp2.size()!=mm){
     cout<<"Patch is damaged."<<'\n';
         return 0;
   }
   int ans=-MM;
   for(int i=MM-1;i>=0;i--){
    if(NN+i>=prenn+premm&&NN+i+MM<=ori.size()){ // 修改：边界允许刚好匹配到最后一行
         bool an=true;
      for(int j=NN+i;j<NN+i+MM;j++){
        if(tmp1[j-(NN+i)]!=ori[j]){ // 修改：tmp1 下标应为 j-起点
            an=false;
            break;
        } 
      }
      if(an)ans=i;
   }
   if(NN-i>=prenn+premm&&NN-i>0&&NN-i+MM<=ori.size()){ // 修改：负偏移时起点是 NN-i
         bool an=true;
      for(int j=NN-i;j<NN-i+MM;j++){ // 修改：这里原来仍用了 NN+i，负偏移必错
        if(tmp1[j-(NN-i)]!=ori[j]){ // 修改：tmp1 下标应为 j-起点
            an=false;
            break;
        } 
      }
      if(an)ans=-i;
   }
}
  if(ans==-MM){
    cout<<"Patch is damaged."<<'\n';
         return 0;
  }
   for(int i=prenn+premm;i<NN+ans;i++){ // 修改：上一块对应的原文已被替换，不能从 prenn 开始补
    out.push_back(ori[i]);
   }
   for(int i=0;i<mm;i++){
    out.push_back(tmp2[i]);
   }
   NN+=ans;
   can+=ans;
   prenn=NN;
   premm=MM;
}
 for(int i=prenn+premm;i<ori.size();i++){ // 修改：最后一个块后面的原文要补上
    out.push_back(ori[i]);
 }
 for(auto&p:out){
    cout<<p<<'\n';
 }
}