#include<iostream>
#include<vector>
using namespace std;
int main() {
	int n;
	cin >> n;
	int ans = 0;
	vector<bool>visit(n + 1);
	for (int i = 2;i*i <= n;i++) {
		for (int j = i * i;j <= n;j += i) {
			visit[j] = true;
		}
	}
	for (int i = 2;i <= n;i++) {
		if (!visit[i]) {
			cout << i << " ";
			ans++; }
	}
	cout << endl << ans;
	
}