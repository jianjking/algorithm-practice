#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
    int t;
    cin >> t;
    for (int t1 = 0;t1 < t;t1++) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>>tree(n + 1, vector<int>(2));
        for (int i = 1;i <= n;i++) {
            scanf("%d", &tree[i][0]);
        }
        for (int i = 1;i <= n;i++) {
            scanf("%d", &tree[i][1]);
        }
        vector<vector<int>>dp(n + 1, vector<int>(m + 1, 0));
        sort(tree.begin(), tree.end(), [](vector<int>a, vector<int>b) {
            return a[1] < b[1];}
            );
            for (int i = 1;i <= n;i++) {
                for (int j = 1;j <= m;j++) {
                    dp[i][j] = max(dp[i - 1][j], (j - 1) * tree[i][1] + tree[i][0] + dp[i - 1][j - 1]);
                }
            }
            cout << dp[n][m] << endl;
                
            }
    }