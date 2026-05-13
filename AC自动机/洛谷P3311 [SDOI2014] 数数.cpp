#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 1500;
const int MOD = 1000000007;

int tree[maxn][10];
int alert[maxn] = {};
int fail[maxn];
int cnt = 1;

void f1(string& s) {
    int u = 0;
    for (auto& p : s) {
        int d = p - '0';
        if (tree[u][d] == 0) {
            tree[u][d] = cnt++;
        }
        u = tree[u][d];
    }
    alert[u] = true;
}

long long dfs(const string& s,
    vector<vector<vector<vector<int>>>>& dp,
    int i, int j, int free0, int cos) {
    if (alert[j]) return 0;
    if (i == (int)s.size()) return cos == 1 ? 1 : 0;
    int res = dp[i][j][free0][cos];
    if (res != -1) return res;
    res = 0;
    int cur = s[i] - '0';
    if (cos == 0) {
        if (free0 == 0) {
            // place leading zero
            res = (res + dfs(s, dp, i + 1, 0, 1, 0)) % MOD;
            // place digit < cur
            for (int z = 1; z < cur; ++z) {
                res = (res + dfs(s, dp, i + 1, tree[j][z], 1, 1)) % MOD;
            }
            // place digit == cur
            res = (res + dfs(s, dp, i + 1, tree[j][cur], 0, 1)) % MOD;
        }
        else {
            res = (res + dfs(s, dp, i + 1, 0, 1, 0)) % MOD;
            for (int z = 1; z <= 9; ++z) {
                res = (res + dfs(s, dp, i + 1, tree[j][z], 1, 1)) % MOD;
            }
        }
    }
    else {
        if (free0 == 0) {
            for (int z = 0; z < cur; ++z) {
                res = (res + dfs(s, dp, i + 1, tree[j][z], 1, 1)) % MOD;
            }
            res = (res + dfs(s, dp, i + 1, tree[j][cur], 0, 1)) % MOD;
        }
        else {
            for (int z = 0; z <= 9; ++z) {
                res = (res + dfs(s, dp, i + 1, tree[j][z], 1, 1)) % MOD;
            }
        }
    }
    dp[i][j][free0][cos] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s2;
        cin >> s2;
        f1(s2);
    }

    queue<int> f;
    for (int i = 0; i < 10; i++) {
        if (tree[0][i]) f.push(tree[0][i]);
    }
    while (!f.empty()) {
        int c = f.front(); f.pop();
        for (int i = 0; i < 10; i++) {
            if (tree[c][i] == 0) {
                tree[c][i] = tree[fail[c]][i];
            }
            else {
                fail[tree[c][i]] = tree[fail[c]][i];
                f.push(tree[c][i]);
            }
        }
        alert[c] |= alert[fail[c]];
    }

    int L = s.size(), V = cnt;
    vector<vector<vector<vector<int>>>>dp(s.size() + 1, vector<vector<vector<int>>>(cnt + 1, vector<vector<int>>(2, vector<int>(2, -1))));

    cout << dfs(s, dp, 0, 0, 0, 0) << "\n";
    return 0;
}
