#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAXN = 100001;
const int base = 499;

long long pow_[MAXN];       // 存储base的幂次，避免重复计算
long long hashs[MAXN];      // 存储字符串s的前缀哈希值
long long hashp[MAXN];      // 存储字符串p的前缀哈希值

// 预处理哈希数组和幂次数组
void build(const string& s, const string& p) {
    pow_[0] = 1;
    for (int j = 1; j < MAXN; ++j) {
        pow_[j] = pow_[j - 1] * base;
    }
    // 计算s的哈希前缀
    hashs[0] = s[0] - 'a' + 1;
    for (int j = 1; j < s.size(); ++j) {
        hashs[j] = hashs[j - 1] * base + (s[j] - 'a' + 1);
    }
    // 计算p的哈希前缀
    hashp[0] = p[0] - 'a' + 1;
    for (int j = 1; j < p.size(); ++j) {
        hashp[j] = hashp[j - 1] * base + (p[j] - 'a' + 1);
    }
}

// 计算子串哈希值
long long getHash(long long hash[], int l, int r) {
    if (l == 0) return hash[r];
    return hash[r] - hash[l - 1] * pow_[r - l + 1];
}

// 判断s[l1...l1+len-1]和p[l2...l2+len-1]哈希是否相同
bool same(int l1, int l2, int len) {
    return getHash(hashs, l1, l1 + len - 1) == getHash(hashp, l2, l2 + len - 1);
}

// 检查s[l1..r1]和p[0..m-1]是否最多有k个不同字符
bool check(int l1, int r1, int m, int k) {
    int diff = 0;
    int l2 = 0;
    while (l1 <= r1 && diff <= k) {
        int l = 1, r = r1 - l1 + 1;
        int len = 0;
        // 二分查找最大匹配长度
        while (l <= r) {
            int mid = (l + r) / 2;
            if (same(l1, l2, mid)) {
                len = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        // 关键：如果匹配后仍有字符，说明该位置不同
        if (l1 + len <= r1) {
            diff++;
        }
        l1 += len + 1;
        l2 += len + 1;
    }
    return diff <= k;
}

int compute(const string& s, const string& p, int k) {
    int n = s.size(), m = p.size();
    if (n < m) return 0;
    build(s, p);
    int ans = 0;
    for (int i = 0; i <= n - m; ++i) {
        if (check(i, i + m - 1, m, k)) {
            ans++;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    cin.ignore(); // 忽略换行符
    while (n--) {
        string s, p;
        getline(cin, s);
        getline(cin, p);
        cout << compute(s, p, 3) << '\n';
    }
    return 0;
}