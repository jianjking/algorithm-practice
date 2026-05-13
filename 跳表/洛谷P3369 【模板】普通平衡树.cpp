#include<bits/stdc++.h>
using namespace std;

const int MXN = 1e5 + 5;
const int MX  = 21;

int cnt;
int key[MXN];
int ci[MXN];
int len[MXN][MX];
int next_node[MXN][MX];
int high[MXN];

void build(){
    cnt++;                    // 全局初值0，这里++后=1
    key[cnt]  = INT_MIN;      // 头结点
    high[cnt] = MX - 1;       // 满层
}

int ran(){ 
    int ans = 1;
    while ((rand() & 1) && ans < MX - 1) ++ans;
    return ans;
}

// 可选：如果多测需要清空，用这个（把原来的尺寸错误一并修了）
void clear(){
    memset(key,  0, sizeof(key));
    memset(ci,   0, sizeof(ci));
    memset(high, 0, sizeof(high));
    memset(len,  0, sizeof(len));
    memset(next_node, 0, sizeof(next_node));
    cnt = 0;
}

int find(int i,int h,int nums){
    while(next_node[i][h]!=0 && key[next_node[i][h]]<nums){
        i = next_node[i][h];
    }
    if(h==1){
        if(next_node[i][h]!=0 && key[next_node[i][h]]==nums){
            return next_node[i][h];
        }
        return 0;
    }else{
        return find(i,h-1,nums);
    }
}

// 注意：必须递归到底层给 ci++，并让路径上每一层 len++
void addcount(int i,int h,int nums,int /*height_ignored*/){
    while(next_node[i][h]!=0 && key[next_node[i][h]]<nums){
         i = next_node[i][h];
    }
    if(h==1){
        // 右邻即为该键
        if(next_node[i][h]!=0 && key[next_node[i][h]]==nums){
            ci[next_node[i][h]]++;
        }
    }else{
        addcount(i, h-1, nums, 0);
    }
    len[i][h]++;  // 每层路径都 +1
}

int addnode(int i,int h,int j){
    int rlen = 0; // 本层向右累计的（<key[j]）元素数
    while(next_node[i][h]!=0 && key[next_node[i][h]]<key[j]){
         rlen += len[i][h];
         i = next_node[i][h];
    }
    if(h==1){
         int nxt = next_node[i][h];
         next_node[j][h] = nxt;
         next_node[i][h] = j;
         // 第1层：len 即为“指向节点”的重数
         len[i][h] = ci[j];                 // i->j 跨过 j 的重数（此时=1）
         len[j][h] = (nxt ? ci[nxt] : 0);   // j->nxt 跨过 nxt 的重数
         return rlen;                       // 严格小于 key[j] 的元素个数（不开+1）
    }else{
         int down = addnode(i, h-1, j);     // 下层跨过元素数
         if(high[j] < h){
             // 本层没有 j，只是总量 +1
             len[i][h]++;
         }else{
            int old_next = next_node[i][h];
            int old_len  = len[i][h];
            next_node[j][h] = old_next;
            next_node[i][h] = j;
            // 带秤跳表切分（关键！用 down 而不是 rlen）
            len[i][h] = down + ci[j];
            len[j][h] = old_len + 1 - down - ci[j];
         }
         return rlen + down;
    }
}

void add(int nums){
   int j = find(1, MX-1, nums);
   if(j){
        addcount(1, MX-1, nums, high[j]);   // height 参数忽略，保留你的签名
   }else{
        ++cnt;
        high[cnt] = ran();
        key[cnt]  = nums;
        ci[cnt]   = 1;
        addnode(1, MX-1, cnt);
   }
}

void deletecnt(int i,int h,int j){
    // 这里 j 是“节点编号”，不是值
    while(next_node[i][h]!=0 && key[next_node[i][h]]<key[j]){
        i = next_node[i][h];
    }
    if(h==1){
        // 右邻就是 j
        if(next_node[i][h]==j) ci[j]--;
    }else{
        deletecnt(i, h-1, j);
    }
    len[i][h]--;
}

void deletenode(int i,int h,int j){
    while(next_node[i][h]!=0 && key[next_node[i][h]]<key[j]){
        i = next_node[i][h];
    }
    if(h==1){
        // 底层摘链 + 跨度合并
        int nj = next_node[j][h];
        next_node[i][h] = nj;
        len[i][h] += len[j][h] - 1;
        return;
    }else{
        if(high[j] < h){
            // 本层没有 j，只是这条边跨过元素 -1
            len[i][h]--;
        }else{
            int nj = next_node[j][h];
            next_node[i][h] = nj;
            len[i][h] += len[j][h] - 1;
        }
        deletenode(i, h-1, j);
    }
}

void deletion(int nums){
    int j = find(1, MX-1, nums);
    if(!j) return;
    if(ci[j] > 1){
        deletecnt(1, MX-1, j);
    }else{
        deletenode(1, MX-1, j);
        // 不清理数组：逻辑删除即可
    }
}

int small(int i,int h,int nums){
    if(h==0) return 0;
    int sum = 0;
    while(next_node[i][h]!=0 && key[next_node[i][h]]<nums){
        sum += len[i][h];
        i = next_node[i][h];         // 必须右移
    }
    sum += small(i, h-1, nums);
    return sum;
}

int pai(int i,int h,int x){
    int sum = 0;
    while(next_node[i][h]!=0 && sum + len[i][h] < x){
        sum += len[i][h];
        i = next_node[i][h];
    }
    if(h==1){
        int nxt = next_node[i][h];
        return nxt ? key[nxt] : INT_MAX;  // 题目一般不给越界；这里返回 +INF 表示无解
    }else{
        return pai(i, h-1, x - sum);
    }
}

void pre(int i,int h,int nums,int&ans){
    if(h==0) return;
    while(next_node[i][h]!=0 && key[next_node[i][h]]<nums){
        i = next_node[i][h];
    }
    if(h==1){
        ans = (i==1 ? INT_MIN : key[i]); // 严格前驱
        return;
    }
    pre(i, h-1, nums, ans);
}

void back(int i,int h,int nums,int&ans){
    if(h==0) return;
    while(next_node[i][h]!=0 && key[next_node[i][h]]<nums){
        i = next_node[i][h];
    }
    if(h==1){
        int nxt = next_node[i][h];
        if(!nxt){ ans = INT_MAX; return; }
        if(key[nxt] > nums){ ans = key[nxt]; return; }
        // 跳过等于 nums 的那个
        nxt = next_node[nxt][1];
        ans = (nxt ? key[nxt] : INT_MAX);
        return;
    }
    back(i, h-1, nums, ans);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    srand((unsigned)time(nullptr));
    build();

    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int op, nums;
        cin >> op >> nums;
        if(op==1){
            add(nums);
        }else if(op==2){
            deletion(nums);
        }else if(op==3){
            cout << 1 + small(1, MX-1, nums) << '\n';
        }else if(op==4){
            cout << pai(1, MX-1, nums) << '\n';
        }else if(op==5){
            int ans = INT_MIN;
            pre(1, MX-1, nums, ans);
            cout << ans << '\n';
        }else{
            int ans = INT_MAX;
            back(1, MX-1, nums, ans);
            cout << ans << '\n';
        }
    }
    return 0;
}
