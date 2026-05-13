#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

const int MAX_N = 20;        
const int INF = INT_MAX;
int dp[1 << MAX_N][MAX_N];
int graph[MAX_N][MAX_N];
int f(int status, int i, int n) {
    if (status == 0) return graph[i][0];  
    if (dp[status][i] != -1) return dp[status][i]; 

    int best = INF;
    for (int j = 0; j < n; j++) {
        if (status & (1 << j)) {  
            int candidate = graph[i][j] + f(status ^ (1 << j), j, n);
            if (candidate < best) {
                best = candidate;
            }
        }
    }
    dp[status][i] = best;
    return best;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    int maxState = 1 << n;
    for (int state = 0; state < maxState; state++) {
        for (int j = 0; j < n; j++) {
            dp[state][j] = -1;
        }
    }
    int initialState = (1 << n) - 2;
    cout << f(initialState, 0, n) << endl;

    return 0;
}
