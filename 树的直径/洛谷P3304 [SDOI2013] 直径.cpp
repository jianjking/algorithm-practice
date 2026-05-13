#include<iostream>
#include<vector>
using namespace std;
using ll = long long;

void dfs(ll son, ll father, ll v, vector<vector<pair<ll, ll>>>& graph, vector<ll>& dist, vector<ll>& last) {
	if (son == father) {
		dist[son] = 0;
	}
	else {
		dist[son] = dist[father] + v;
		last[son] = father;
	}
	for (auto& p : graph[son]) {
		if (p.first != father) {
			dfs(p.first, son, p.second, graph, dist, last);
		}
	}
}

ll f(ll son, ll father, vector<vector<pair<ll, ll>>>& graph, vector<bool>& vis) {
	ll mx = 0;
	for (auto& p : graph[son]) {
		if (p.first != father && !vis[p.first]) {
			mx = max(mx, p.second + f(p.first, son, graph, vis));
		}
	}
	return mx;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	ll n;
	cin >> n;

	vector<vector<pair<ll, ll>>> graph(n + 1);
	for (ll i = 0; i < n - 1; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({ b, c });
		graph[b].push_back({ a, c });
	}

	vector<ll> last(n + 1);
	vector<ll> dist(n + 1, 0);
	vector<bool> vis(n + 1, false);

	dfs(1, 1, 0, graph, dist, last);

	ll best = 0, start = 1;
	for (ll i = 1; i <= n; i++) {
		if (dist[i] > best) {
			best = dist[i];
			start = i;
		}
	}

	dist.assign(n + 1, 0);
	last.assign(n + 1, 0);
	dfs(start, start, 0, graph, dist, last);

	best = 0;
	ll end = start;
	for (ll i = 1; i <= n; i++) {
		if (dist[i] > best) {
			best = dist[i];
			end = i;
		}
	}

	vis[start] = true;
	for (ll i = end; i != start; i = last[i]) {
		vis[i] = true;
	}

	ll l = start, r = end;
	for (ll i = last[end]; i != start; i = last[i]) {
		ll tmp = f(i, i, graph, vis);
		if (tmp == dist[i] && l == start) {
			l = i;
		}
		if (tmp == best - dist[i]) {
			r = i;
		}
	}

	ll cnt = 0;
	for (ll i = r; i != l; i = last[i], cnt++) {}

	cout << best << '\n' << cnt << '\n';
}
