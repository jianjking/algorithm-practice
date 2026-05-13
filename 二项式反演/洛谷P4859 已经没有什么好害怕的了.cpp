#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000009;

int addmod(long long a){ a%=MOD; if(a<0) a+=MOD; return (int)a; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if(!(cin >> n >> k)) return 0;

    // wins - losses = k  => wins = (n+k)/2 必须是整数
    if ((n + k) & 1) { cout << 0 << '\n'; return 0; }
    int need = (n + k) / 2; // 需要恰好这么多“糖果赢”

    vector<int> tang(n+1), yao(n+1);
    for (int i = 1; i <= n; ++i) cin >> tang[i];
    for (int i = 1; i <= n; ++i) cin >> yao[i];
    sort(tang.begin()+1, tang.end());
    sort(yao.begin()+1, yao.end());

    // xiao[i] = 有多少药片 < tang[i]
    vector<int> xiao(n+1, 0);
    for (int i = 1, j = 1; i <= n; ++i){
        while (j <= n && yao[j] < tang[i]) ++j;
        xiao[i] = j - 1;
    }

    // dp[i][j]: 用前 i 个糖果，恰好选 j 次“糖果赢”的方案数（只给赢的匹配分配了具体药片）
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i){
        int up = min(i, xiao[i]);
        for (int j = 0; j <= up; ++j){
            // 当前糖果“输”
            dp[i][j] = dp[i-1][j];
            // 当前糖果“赢”：可用的小药片 = xiao[i] - (j-1)
            if (j > 0){
                long long ways = (long long)dp[i-1][j-1] * (xiao[i] - (j-1)) % MOD;
                dp[i][j] = addmod(dp[i][j] + ways);
            }
        }
    }

    // 预处理阶乘
    vector<int> fac(n+1,1);
    for (int i = 1; i <= n; ++i) fac[i] = (long long)fac[i-1] * i % MOD;

    // 组合数 C 用杨辉三角（n<=2000 足够快）
    vector<vector<int>> C(n+1, vector<int>(n+1, 0));
    for (int i = 0; i <= n; ++i){
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j){
            C[i][j] = addmod((long long)C[i-1][j] + C[i-1][j-1]);
        }
    }

    // g[i] = 把恰好 i 次“糖果赢”的那些赢对儿已经具体分配好后，剩下 (n-i)! 种随便配（先计“至少 i 个指定赢”的超集）
    vector<int> g(n+1, 0);
    for (int i = 0; i <= n; ++i){
        g[i] = (long long)dp[n][i] * fac[n - i] % MOD;
    }

    // 反演到“恰好 need 次赢”
    long long ans = 0;
    for (int i = need; i <= n; ++i){
        long long term = (long long)C[i][need] * g[i] % MOD;
        if ((i - need) & 1) term = MOD - term;  // (-1)^(i-need)
        ans += term;
        if (ans >= MOD) ans -= MOD;
    }
    cout << (int)ans << '\n';
    return 0;
}

