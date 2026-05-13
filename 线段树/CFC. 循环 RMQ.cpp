#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

vector<int> nums; // 原数组
vector<int> mn;   // 区间最小值
vector<int> add;  // 懒标记

void up(int sign) {
    mn[sign] = min(mn[sign * 2], mn[sign * 2 + 1]);
}

void addlazy(int k, int sign) {
    add[sign] += k;
    mn[sign] += k;
}

void down(int sign) {
    if (add[sign] != 0) {
        addlazy(add[sign], sign * 2);
        addlazy(add[sign], sign * 2 + 1);
        add[sign] = 0;
    }
}

void build(int l, int r, int sign) {
    if (l == r) {
        mn[sign] = nums[l - 1]; // 注意 nums 从 0 开始存
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, sign * 2);
    build(mid + 1, r, sign * 2 + 1);
    up(sign);
}

int query(int x, int y, int l, int r, int sign) {
    if (x <= l && y >= r) return mn[sign];
    down(sign);
    int mid = (l + r) / 2;
    int ans = INT_MAX;
    if (x <= mid) ans = min(ans, query(x, y, l, mid, sign * 2));
    if (y > mid) ans = min(ans, query(x, y, mid + 1, r, sign * 2 + 1));
    return ans;
}

void addtion(int x, int y, int l, int r, int k, int sign) {
    if (x <= l && y >= r) {
        addlazy(k, sign);
        return;
    }
    down(sign);
    int mid = (l + r) / 2;
    if (x <= mid) addtion(x, y, l, mid, k, sign * 2);
    if (y > mid) addtion(x, y, mid + 1, r, k, sign * 2 + 1);
    up(sign);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    nums.assign(n, 0);
    mn.assign(4 * n + 5, 0);
    add.assign(4 * n + 5, 0);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    build(1, n, 1);

    int m;
    cin >> m;
    cin.ignore(); // 去掉换行

    for (int i = 0; i < m; i++) {
        string s;
        getline(cin>>ws, s);
        stringstream ss(s);
        vector<int> aaa;
        int tmp;
        while (ss >> tmp) aaa.push_back(tmp);

        if (aaa.size() == 2) {
            // 查询
            if (aaa[1] < aaa[0]) {
                cout << min(query(aaa[0] + 1, n, 1, n, 1),
                    query(1, aaa[1] + 1, 1, n, 1)) << '\n';
            }
            else {
                cout << query(aaa[0] + 1, aaa[1] + 1, 1, n, 1) << '\n';
            }
        }
        else if (aaa.size() == 3) {
            // 修改
            if (aaa[1] < aaa[0]) {
                addtion(aaa[0] + 1, n, 1, n, aaa[2], 1);
                addtion(1, aaa[1] + 1, 1, n, aaa[2], 1);
            }
            else {
                addtion(aaa[0] + 1, aaa[1] + 1, 1, n, aaa[2], 1);
            }
        }
    }
}
