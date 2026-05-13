#include <bits/stdc++.h>
using namespace std;

const int mx = 3*1e5 + 5;

int zuo[mx], you[mx], topv[mx]; // top 改个内部名，避免和函数/宏混淆
int distn[mx];

long long addv[mx], mulv[mx];   // 用 long long
long long defend[mx];
long long nums[mx];
long long v[mx];

int status[mx], dep[mx], parent[mx];
int frs[mx];        // 骑士起始城池 c_i
int cnt[mx];        // 各城阵亡数
int death[mx];      // 骑士死亡城（0 表示打到根还活着）

// 下传懒标记：先把父标记合并到子，再清父
inline void down(int i){
    if(mulv[i]!=1 || addv[i]!=0){
        if(zuo[i]){
            mulv[zuo[i]] = mulv[zuo[i]] * mulv[i];
            addv[zuo[i]] = addv[zuo[i]] * mulv[i] + addv[i];
            nums[zuo[i]] = nums[zuo[i]] * mulv[i] + addv[i];
        }
        if(you[i]){
            mulv[you[i]] = mulv[you[i]] * mulv[i];
            addv[you[i]] = addv[you[i]] * mulv[i] + addv[i];
            nums[you[i]] = nums[you[i]] * mulv[i] + addv[i];
        }
        mulv[i] = 1;
        addv[i] = 0;
    }
}

inline int mergeh(int a,int b){
    if(!a || !b) return a ? a : b;
    if(nums[a] > nums[b] || (nums[a]==nums[b] && a>b)) swap(a,b); // 最小堆
    down(a);
    you[a] = mergeh(you[a], b);
    if(distn[zuo[a]] < distn[you[a]]) swap(zuo[a], you[a]);
    distn[a] = distn[you[a]] + 1;
    return a;
}

// 弹出堆顶，返回新堆顶；被弹出节点的 id 由调用者保存
inline int pop_head(int h){
    down(h);
    int nh = mergeh(zuo[h], you[h]);
    zuo[h] = you[h] = 0;
    distn[h] = 0;
    return nh;
}

// 对整棵堆根打一次 (a==0 ? +c : *c) 的“线性”懒标记
inline void apply_on_root(int a, int typ, long long c){
    if(!a) return;
    if(typ==0){ nums[a] += c; addv[a] += c; }
    else      { nums[a] *= c; mulv[a] *= c; addv[a] *= c; }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 初始化
    for(int i=1;i<mx;i++){ mulv[i]=1; }
    distn[0] = -1;

    int n, m;
    if(!(cin >> n >> m)) return 0;

    for(int i=1;i<=n;i++) cin >> defend[i];

    parent[1]=0; status[1]=0; v[1]=0; // 根无变换
    for(int i=2;i<=n;i++){
        int f,a; long long vv;
        cin >> f >> a >> vv;
        parent[i]=f; status[i]=a; v[i]=vv;
    }

    // 深度：根为 1，dep[0]=0 保持默认
    for(int i=1;i<=n;i++) dep[i] = dep[parent[i]] + 1;

    // 读入骑士，建堆（每个骑士作为一个节点，id=骑士编号）
    for(int i=1;i<=m;i++){
        long long s; int c;
        cin >> s >> c;
        nums[i] = s;
        frs[i] = c;
        // 懒标记初始化
        mulv[i] = 1; addv[i] = 0;
        zuo[i]=you[i]=0; distn[i]=0;

        if(!topv[c]) topv[c]=i;
        else topv[c]=mergeh(topv[c], i);
    }

    // 自底向上处理城市
    for(int i=n;i>=1;i--){
        int &H = topv[i];

        // 先清掉打不过这座城的（最小堆反复弹出 < h_i 的）
        while(H && nums[H] < defend[i]){
            cnt[i]++;
            int dead = H;
            H = pop_head(H);
            death[dead] = i; // 正确记录“被弹出的那个”
        }

        // 活下来的在该城获得一次变换（根节点无变换）
        if(H && i!=1) apply_on_root(H, status[i], v[i]);

        // 合并到父城
        if(parent[i]){
            topv[parent[i]] = mergeh(topv[parent[i]], H);
        }
    }

    // 根堆里剩下的都是“没死”的
    if(topv[1]){
        // 迭代栈遍历，不用递归
        vector<int> st; st.push_back(topv[1]);
        while(!st.empty()){
            int x = st.back(); st.pop_back();
            if(!x) continue;
            death[x] = 0;
            if(zuo[x]) st.push_back(zuo[x]);
            if(you[x]) st.push_back(you[x]);
        }
    }

    // 输出：各城牺牲数
    for(int i=1;i<=n;i++) cout << cnt[i] << '\n';

    // 输出：每个骑士攻占的城池数量 = dep[c_i] - dep[death_i]（death_i==0 表示到根仍存活）
    for(int i=1;i<=m;i++){
        cout << (dep[frs[i]] - dep[death[i]]) << '\n';
    }
    return 0;
}
