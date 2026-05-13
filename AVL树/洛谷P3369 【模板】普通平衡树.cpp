#include<bits/stdc++.h>
using namespace std;

struct node {
    int size;
    int val;
    node* left;
    node* right;
    int count;
    int height;
};

// =================== 基础维护函数 ===================
int h(node* cur){ return cur ? cur->height : 0; }
int sz(node* cur){ return cur ? cur->size : 0; }

void up(node* cur) {
    cur->size = cur->count + sz(cur->left) + sz(cur->right);
    cur->height = max(h(cur->left), h(cur->right)) + 1;
}

// =================== 正确旋转实现 ===================
node* lxu(node* cur) { // 左旋
    node* r = cur->right;
    cur->right = r->left;
    r->left = cur;
    up(cur);
    up(r);
    return r;
}

node* rxu(node* cur) { // 右旋
    node* l = cur->left;
    cur->left = l->right;
    l->right = cur;
    up(cur);
    up(l);
    return l;
}

// =================== 平衡调整函数 ===================
node* mountain(node* cur) {
    if (!cur) return cur;
    int lh = h(cur->left), rh = h(cur->right);
    if (lh - rh > 1) {
        if (h(cur->left->left) < h(cur->left->right))
            cur->left = lxu(cur->left);
        return rxu(cur);
    }
    if (rh - lh > 1) {
        if (h(cur->right->right) < h(cur->right->left))
            cur->right = rxu(cur->right);
        return lxu(cur);
    }
    return cur;
}

// =================== 插入 ===================
node* add(int x, node* cur) {
    if (cur == nullptr) {
        cur = new node{x, x, nullptr, nullptr, 1, 1};
        cur->val = x;
        cur->size = 1;
        cur->count = 1;
        cur->height = 1;
        cur->left = cur->right = nullptr;
        return cur;
    }
    if (x == cur->val) cur->count++;
    else if (x < cur->val) cur->left = add(x, cur->left);
    else cur->right = add(x, cur->right);
    up(cur);
    return mountain(cur);
}

// =================== 删除 ===================
node* deletion(int target, node* cur) {
    if (cur == nullptr) return nullptr;
    if (target < cur->val) cur->left = deletion(target, cur->left);
    else if (target > cur->val) cur->right = deletion(target, cur->right);
    else {
        if (cur->count > 1) cur->count--;
        else {
            if (!cur->left || !cur->right) {
                node* tmp = cur->left ? cur->left : cur->right;
                delete cur;
                return tmp;
            } else {
                node* r = cur->right;
                while (r->left) r = r->left;
                cur->val = r->val;
                cur->count = r->count;
                r->count = 1;
                cur->right = deletion(cur->val, cur->right);
            }
        }
    }
    up(cur);
    return mountain(cur);
}

// =================== 查询函数 ===================

// 第3类：有多少个数比x小
int querymn(int target, node* cur) {
    if (!cur) return 0;
    if (target <= cur->val) return querymn(target, cur->left);
    return sz(cur->left) + cur->count + querymn(target, cur->right);
}

// 第4类：查询排名为x的值
int querypai(int target, node* cur) {
    if (!cur) return 0;
    int lsz = sz(cur->left);
    if (target <= lsz) return querypai(target, cur->left);
    if (target > lsz + cur->count) return querypai(target - lsz - cur->count, cur->right);
    return cur->val;
}

// 第5类：前驱
void querypre(int target, node* cur, int& ans) {
    if (!cur) return;
    if (cur->val < target) {
        ans = max(ans, cur->val);
        querypre(target, cur->right, ans);
    } else {
        querypre(target, cur->left, ans);
    }
}

// 第6类：后继
void queryback(int target, node* cur, int& ans) {
    if (!cur) return;
    if (cur->val > target) {
        ans = min(ans, cur->val);
        queryback(target, cur->left, ans);
    } else {
        queryback(target, cur->right, ans);
    }
}

// =================== 主程序 ===================
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    node* head = nullptr;
    int n;
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) head = add(x, head);
        else if (op == 2) head = deletion(x, head);
        else if (op == 3) cout << querymn(x, head) + 1 << '\n';
        else if (op == 4) cout << querypai(x, head) << '\n';
        else if (op == 5) {
            int ans = INT_MIN;
            querypre(x, head, ans);
            cout << ans << '\n';
        } else {
            int ans = INT_MAX;
            queryback(x, head, ans);
            cout << ans << '\n';
        }
    }
}
