#include <bits/stdc++.h>
using namespace std;

vector<int> nums;   // nums[key] = 插入位置(时间)
vector<int> zuo, you;
int head;

void build() {
    int n = (int)nums.size() - 1;
    vector<int> st(n + 1, 0);
    int top = 0;
    for (int i = 1; i <= n; i++) {       // i 是键值(1..n)，中序天然有序
        int pos = top;
        // 最小堆：父节点的插入时间 < 子节点
        while (pos > 0 && nums[st[pos]] > nums[i]) pos--;
        if (pos > 0) you[st[pos]] = i;   // i 成为 st[pos] 的右儿子
        if (pos < top) zuo[i] = st[pos + 1]; // 被 i 弹走的“尾巴”挂成 i 的左儿子
        st[++pos] = i;
        top = pos;                       // 别忘了回写！
    }
    head = st[1];                        // 栈底就是根
}

void dfs(int i, vector<int>& ans) {      // 前序遍历 = 该树的字典序最小生成序列
    if (i == 0) return;
    ans.push_back(i);                    // 输出键值本身
    dfs(zuo[i], ans);
    dfs(you[i], ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; 
    if (!(cin >> n)) return 0;
    nums.assign(n + 1, 0);
    zuo.assign(n + 1, 0);
    you.assign(n + 1, 0);
    for (int pos = 1; pos <= n; pos++) {
        int key; 
        cin >> key;
        nums[key] = pos;                 // priority = 插入时间（越小越优先）
    }
    build();
    vector<int> ans;
    ans.reserve(n);
    dfs(head, ans);
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
