#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 2e5 + 1;
int tree[maxn][26];
int fail[maxn];
int ed[maxn];
int cun[maxn];
int cnt = 1;
int times[maxn];
void qian(string& s, int cur) {
	int u = 0;
	for (int i = 0;i < s.size(); i++) {
		if (tree[u][s[i] - 'a'] == 0) {
			tree[u][s[i] - 'a'] = cnt++;
		}
		u = tree[u][s[i] - 'a'];
	}
	ed[cur] = u;
}
void f2(int i,vector<vector<int>>&graph) {
	for (auto& p : graph[i]) {
		f2(p, graph);
		cun[i] += cun[p];
	}
}
int  main() {
	int n;
	cin >> n;
	for (int i = 0;i < n;i++) {
		string s;
		cin >> s;
		qian(s, i);
	}
	queue<int>dui;
	for (int i = 0;i < 26;i++)if (tree[0][i] > 0)dui.push(tree[0][i]);
	while (!dui.empty()) {
		int head = dui.front();
		for (int i = 0;i < 26;i++) {
			if (tree[head][i] == 0) {
				tree[head][i] = tree[fail[head]][i];
			}
			else {
				fail[tree[head][i]] = tree[fail[head]][i];
				dui.push(tree[head][i]);
			}
			
		}
		dui.pop();
	}
	string s;
	cin >> s;
	int u = 0;
	for (auto& p : s) {
		u = tree[u][p - 'a'];
		cun[u]++;
	}
	vector<vector<int>>graph(maxn);
	for (int i = 0;i < cnt;i++) {
		int b = fail[i];
		if(b!=i)
		graph[b].push_back(i);
	}
	f2(0,graph);
	for (int i = 0;i < n;i++) {
		cout << cun[ed[i]] << endl;
	}
}

