#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<climits>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    long long sum = 0;
    vector<long long> weight(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> weight[i];
        sum += weight[i];
    }

    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({ b, c });
        graph[b].push_back({ a, c });
    }

    vector<long long> mx(n + 1, LLONG_MIN);
    vector<long long> sz(n + 1);
    stack<vector<int>> tmp;
    tmp.push({ 1, 0, 0 });

    while (!tmp.empty()) {
        int a = tmp.top()[0];
        int b = tmp.top()[1];
        int c = tmp.top()[2];
        tmp.pop();

        if (c == 0) {
            sz[a] = weight[a];
        }

        if (c == graph[a].size()) {
            for (auto& p : graph[a]) {
                if (p.first != b) {
                    sz[a] += sz[p.first];
                    mx[a] = max(mx[a], sz[p.first]);
                }
            }
            mx[a] = max(mx[a], sum - sz[a]);
            continue;
        }

        if (graph[a][c].first == b) {
            tmp.push({ a, b, c + 1 });
            continue;
        }

        tmp.push({ a, b, c + 1 });
        tmp.push({ graph[a][c].first, a, 0 });
    }

    long long best = LLONG_MAX;
    int root = 0;
    for (int i = 1; i <= n; i++) {
        if (mx[i] < best) {
            best = mx[i];
            root = i;
        }
    }

    vector<long long> path(n + 1, 0);
    queue<pair<int, int>> f;
    f.push({ root, root });

    while (!f.empty()) {
        auto [u, fa] = f.front();
        f.pop();
        for (auto& p : graph[u]) {
            int v = p.first, w = p.second;
            if (v != fa) {
                path[v] = path[u] + w;
                f.push({ v, u });
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += path[i] * weight[i];
    }

    cout << ans << '\n';
}
